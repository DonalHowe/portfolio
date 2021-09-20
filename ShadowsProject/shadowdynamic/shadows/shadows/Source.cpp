#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <vector>
#include "Trigonometry.hpp"
#include "VectorAlgebra2D.h"
#include "ParticleSystem.h"

using namespace std;

inline float Det2D(sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3)
{
	return +p1.x * (p2.y - p3.y)
		+ p2.x * (p3.y - p1.y)
		+ p3.x * (p1.y - p2.y);
}

void CheckTriWinding(sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3, bool allowReversed)
{
	float detTri = Det2D(p1, p2, p3);
	if (detTri < 0.0)
	{
		if (allowReversed)
		{
			sf::Vector2f a = p3;
			p3 = p2;
			p2 = a;
		}
		else throw std::runtime_error("triangle has wrong winding direction");
	}
}

bool BoundaryCollideChk(sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3, float eps)
{
	return Det2D(p1, p2, p3) < eps;
}

bool BoundaryDoesntCollideChk(sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3, float eps)
{
	return Det2D(p1, p2, p3) <= eps;
}

bool TriTri2D(sf::Vector2f* t1,
	sf::Vector2f* t2,
	float eps = 0.0, bool allowReversed = true, bool onBoundary = true)
{
	//Trangles must be expressed anti-clockwise
	CheckTriWinding(t1[0], t1[1], t1[2], allowReversed);
	CheckTriWinding(t2[0], t2[1], t2[2], allowReversed);

	bool (*chkEdge)(sf::Vector2f&, sf::Vector2f&, sf::Vector2f&, float) = NULL;
	if (onBoundary) //Points on the boundary are considered as colliding
		chkEdge = BoundaryCollideChk;
	else //Points on the boundary are not considered as colliding
		chkEdge = BoundaryDoesntCollideChk;

	//For edge E of trangle 1,
	for (int i = 0; i < 3; i++)
	{
		int j = (i + 1) % 3;

		//Check all points of trangle 2 lay on the external side of the edge E. If
		//they do, the triangles do not collide.
		if (chkEdge(t1[i], t1[j], t2[0], eps) &&
			chkEdge(t1[i], t1[j], t2[1], eps) &&
			chkEdge(t1[i], t1[j], t2[2], eps))
			return false;
	}

	//For edge E of trangle 2,
	for (int i = 0; i < 3; i++)
	{
		int j = (i + 1) % 3;

		//Check all points of trangle 1 lay on the external side of the edge E. If
		//they do, the triangles do not collide.
		if (chkEdge(t2[i], t2[j], t1[0], eps) &&
			chkEdge(t2[i], t2[j], t1[1], eps) &&
			chkEdge(t2[i], t2[j], t1[2], eps))
			return false;
	}

	//The triangles collide
	return true;
}



class Edge {
public:
	sf::Vector2f start;
	sf::Vector2f end;
};


float lineSlope(sf::Vector2f a, sf::Vector2f b) {

	if (a.x - b.x == 0.0f)
		return NAN;
	else
		return (a.y - b.y) / (a.x - b.x);
}


sf::Vector2f GetIntersectionPoint(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2) {
	sf::Vector2f point;

	float slopeA = lineSlope(a1, a2), slopeB = lineSlope(b1, b2);

	if (slopeA == slopeB) {
		point.x = NAN;
		point.y = NAN;
	}
	else if (isnan(slopeA) && !isnan(slopeB)) {
		point.x = a1.x;
		point.y = (a1.x - b1.x) * slopeB + b1.y;
	}
	else if (isnan(slopeB) && !isnan(slopeA)) {
		point.x = b1.x;
		point.y = (b1.x - a1.x) * slopeA + a1.y;
	}
	else {
		point.x = (slopeA * a1.x - slopeB * b1.x + b1.y - a1.y) / (slopeA - slopeB);
		point.y = slopeB * (point.x - b1.x) + b1.y;
	}
	if (point.x <= std::max(b1.x, b2.x) && point.x >= std::min(b1.x, b2.x) &&
		point.y <= std::max(b1.y, b2.y) && point.y >= std::min(b1.y, b2.y) &&
		point.x <= std::max(a1.x, a2.x) && point.x >= std::min(a1.x, a2.x) &&
		point.y <= std::max(a1.y, a2.y) && point.y >= std::min(a1.y, a2.y))
	{

	}
	else {
		point.x = NAN;
		point.y = NAN;
	}
	return point;
}
class VisibilityPoint
{
public:
	float angle;
	sf::Vector2f point;
};
bool VisPointCompare(const VisibilityPoint& lhs, const VisibilityPoint& rhs)
{
	return lhs.angle < rhs.angle;
}

bool FindClosestPoint(vector<Edge>& edges, sf::Vector2f lightPos, sf::Vector2f ray, VisibilityPoint& closest)
{
	bool bValid = false;
	float minDistance = INFINITY;
	closest.point = { INFINITY , INFINITY };
	closest.angle = 0;

	for (auto& edge : edges)
	{

		sf::Vector2f intersectionPt = GetIntersectionPoint(lightPos, ray + lightPos, edge.start, edge.end);
		if (!isnan(intersectionPt.x))
		{
			if (intersectionPt == lightPos)
			{
				continue;
			}
			bValid = true;
			float dist = thor::length(intersectionPt - lightPos);

			if (dist < minDistance)
			{
				minDistance = dist;

				closest.point = intersectionPt;


				closest.angle = thor::polarAngle(intersectionPt - lightPos);

			}

		}

	}
	if (bValid)
	{


		return true;
	}
	return false;
}

void CreateLightPolygon(sf::Vector2f light, std::vector<Edge> edges, float maxRaylength, vector<VisibilityPoint>& vecVisibilityPolygonPoints)
{
	vecVisibilityPolygonPoints.clear();

	for (int edgeIndex = 0; edgeIndex < edges.size(); edgeIndex++)
	{
		Edge edge = edges[edgeIndex];
		sf::Vector2f edgeVertices[2];
		edgeVertices[0] = edge.start;
		edgeVertices[1] = edge.end;

		for (int i = 0; i < 2; i++)
		{
			sf::Vector2f curVertex = edgeVertices[i];
			sf::Vector2f ray;
			VisibilityPoint closestPoint;
			float baseAngle;
			float ang = 0;

			ray = curVertex - light;


			baseAngle = thor::polarAngle(ray);

			thor::setLength(ray, maxRaylength);

			if (FindClosestPoint(edges, light, ray, closestPoint))
			{
				vecVisibilityPolygonPoints.push_back(closestPoint);
			}

			ang = baseAngle - 0.0001f;
			thor::setPolarAngle(ray, ang);

			thor::setLength(ray, maxRaylength);


			if (FindClosestPoint(edges, light, ray, closestPoint))
			{
				vecVisibilityPolygonPoints.push_back(closestPoint);
			}


			ang = baseAngle + 0.0001f;
			thor::setPolarAngle(ray, ang);

			thor::setLength(ray, maxRaylength);


			if (FindClosestPoint(edges, light, ray, closestPoint))
			{
				vecVisibilityPolygonPoints.push_back(closestPoint);
			}

		}

	}
	sort(vecVisibilityPolygonPoints.begin(), vecVisibilityPolygonPoints.end(), &VisPointCompare);
}

class  player
{
public:
	 player();
	 sf::CircleShape m_myPlayer;
	 const int RADIUS = 15;
	 const sf::Vector2f Start_pos{ 500,500 };
	~ player();
	void movement();

private:

};

 player:: player()
{
}

 player::~ player()
{
}
 void player::movement()
 {
	 m_myPlayer.setRadius(RADIUS);
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	 {
		 m_myPlayer.move(3, 0);
	 }
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	 {
		 m_myPlayer.move(-3, 0);
	 }
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	 {
		 m_myPlayer.move(0, -3);
	 }
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	 {
		 m_myPlayer.move(0, 3);
	 }
 }
int main()
{


	std::vector<Edge> edges;

	sf::RenderWindow window(sf::VideoMode(800, 600), "simple light and shadows");

	srand(time(NULL));
	ParticleSystem theParticle;
	player myPlayer;
	sf::VertexArray northPatroller(sf::Quads, 4);
	sf::VertexArray leftPatroller(sf::Quads, 4);
	sf::VertexArray quad(sf::Quads, 4);
	sf::VertexArray target(sf::Quads, 4);
	sf::VertexArray border(sf::Quads, 4);
	sf::VertexArray quad1(sf::Quads, 4);
	sf::VertexArray quad2(sf::Quads, 4);
	sf::VertexArray quad3(sf::Quads, 4);
	sf::Vector2f light = { 100,100 };
	sf::CircleShape lightShape(3);
	lightShape.setOrigin(5, 5);
	lightShape.setPosition(0, 0);
	lightShape.setFillColor(sf::Color::White);
	bool movesouthup = true;
	bool moveNoirthRight = true;
	int score = 0;
	sf::Text scoreText;
	sf::Text winText;
	sf::Font scoreFont;
	sf::Vector2f playerPos;
	if (!scoreFont.loadFromFile("./BebasNeue.otf"))
	{
		
	}
	scoreText.setFont(scoreFont);
	scoreText.setPosition(200, 10);
	winText.setFont(scoreFont);
	winText.setPosition(200, 110);
	sf::Vector2f pos{ 250,300 };
	sf::CircleShape prizeOne;
	northPatroller[0].position = sf::Vector2f(10, 10);
	northPatroller[1].position = sf::Vector2f(40, 10);
	northPatroller[2].position = sf::Vector2f(40, 40);
	northPatroller[3].position = sf::Vector2f(10, 40);

	northPatroller[0].color = sf::Color::Magenta;
	northPatroller[1].color = sf::Color::Magenta;
	northPatroller[2].color = sf::Color::Magenta;
	northPatroller[3].color = sf::Color::Magenta;

	leftPatroller[0].position = sf::Vector2f(10, 10);
	leftPatroller[1].position = sf::Vector2f(40, 10);
	leftPatroller[2].position = sf::Vector2f(40, 40);
	leftPatroller[3].position = sf::Vector2f(10, 40);

	leftPatroller[0].color = sf::Color::Magenta;
	leftPatroller[1].color = sf::Color::Magenta;
	leftPatroller[2].color = sf::Color::Magenta;
	leftPatroller[3].color = sf::Color::Magenta;

	target[0].position = sf::Vector2f(600, 550);
	target[1].position = sf::Vector2f(630, 550);
	target[2].position = sf::Vector2f(630, 570);
	target[3].position = sf::Vector2f(600, 5700);
	target[0].color = sf::Color::Magenta;
	target[1].color = sf::Color::Magenta;
	target[2].color = sf::Color::Magenta;
	target[3].color = sf::Color::Magenta;


	border[0].position = sf::Vector2f(10, 10);
	border[1].position = sf::Vector2f(790, 10);
	border[2].position = sf::Vector2f(790, 590);
	border[3].position = sf::Vector2f(10, 590);
	border[0].color = sf::Color::Red;
	border[1].color = sf::Color::Red;
	border[2].color = sf::Color::Red;
	border[3].color = sf::Color::Red;

	quad[0].position = sf::Vector2f(300.f, 300);
	quad[1].position = sf::Vector2f(500.f, 300.f);
	quad[2].position = sf::Vector2f(500.f, 400.f);
	quad[3].position = sf::Vector2f(300.f, 400.f);
	quad[0].color = sf::Color::Red;
	quad[1].color = sf::Color::Red;
	quad[2].color = sf::Color::Red;
	quad[3].color = sf::Color::Red;

	quad1[0].position = sf::Vector2f(100, 180);
	quad1[1].position = sf::Vector2f(300.f, 180.f);
	quad1[2].position = sf::Vector2f(300.f, 220.f);
	quad1[3].position = sf::Vector2f(100.f, 220.f);
	quad1[0].color = sf::Color::Red;
	quad1[1].color = sf::Color::Red;
	quad1[2].color = sf::Color::Red;
	quad1[3].color = sf::Color::Red;

	quad2[0].position = sf::Vector2f(80, 50);
	quad2[1].position = sf::Vector2f(100.f, 100.f);
	quad2[2].position = sf::Vector2f(100.f, 300.f);
	quad2[3].position = sf::Vector2f(80.f, 300.f);
	quad2[0].color = sf::Color::Red;
	quad2[1].color = sf::Color::Red;
	quad2[2].color = sf::Color::Red;
	quad2[3].color = sf::Color::Red;

	quad3[0].position = sf::Vector2f(100, 180);
	quad3[1].position = sf::Vector2f(300.f, 180.f);
	quad3[2].position = sf::Vector2f(300.f, 220.f);
	quad3[3].position = sf::Vector2f(100.f, 220.f);
	quad3[0].color = sf::Color::Red;
	quad3[1].color = sf::Color::Red;
	quad3[2].color = sf::Color::Red;
	quad3[3].color = sf::Color::Red;

	edges.push_back(Edge{ quad1[0].position, quad1[1].position });
	edges.push_back(Edge{ quad1[1].position, quad1[2].position });
	edges.push_back(Edge{ quad1[2].position, quad1[3].position });
	edges.push_back(Edge{ quad1[3].position, quad1[0].position });
	edges.push_back(Edge{ quad[0].position, quad[1].position });
	edges.push_back(Edge{ quad[1].position, quad[2].position });
	edges.push_back(Edge{ quad[2].position, quad[3].position });
	edges.push_back(Edge{ quad[3].position, quad[0].position });

	edges.push_back(Edge{ border[0].position, border[1].position });
	edges.push_back(Edge{ border[1].position, border[2].position });
	edges.push_back(Edge{ border[2].position, border[3].position });
	edges.push_back(Edge{ border[3].position, border[0].position });

	prizeOne.setFillColor(sf::Color::Black);
	prizeOne.setRadius(15);
	prizeOne.setPosition(250, 250);


	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	myPlayer.m_myPlayer.setPosition(myPlayer.Start_pos);
	sf::Clock clock;
	clock.restart();

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		timeSinceLastUpdate += clock.restart();


		if (timeSinceLastUpdate > timePerFrame)
		{
			//sf::Vector2i position = sf::Mouse::getPosition(window);
			
		
			lightShape.setPosition(northPatroller[3].position.x, northPatroller[3].position.y);
			
			std::vector <sf::VertexArray> triangles;
			myPlayer.movement();
			window.clear(sf::Color::Blue);
			std::vector<VisibilityPoint> vecVisibilityPolygonPoints;

			CreateLightPolygon(lightShape.getPosition(), edges, 1500, vecVisibilityPolygonPoints);
		

			for (int visPointIndex = 0; visPointIndex < vecVisibilityPolygonPoints.size() - 1; visPointIndex++)
			{
				sf::VertexArray tri(sf::Triangles, 3);

				tri[0].position = lightShape.getPosition();;
				tri[1].position = vecVisibilityPolygonPoints[visPointIndex].point;
				tri[2].position = vecVisibilityPolygonPoints[visPointIndex + 1].point;

				tri[0].color = sf::Color::Green;
				tri[1].color = sf::Color::Green;
				tri[2].color = sf::Color::Green;

				triangles.push_back(tri);

			}

			if (northPatroller[1].position.x < 800&& moveNoirthRight==true)
			{
				northPatroller[0].position.x += 1.2;
				northPatroller[1].position.x += 1.2;
				northPatroller[2].position.x += 1.2;
				northPatroller[3].position.x += 1.2;
				
			}
			else
			{
				moveNoirthRight = false;
			}
			if (northPatroller[1].position.x >= 0 && moveNoirthRight == false)
			{
				northPatroller[0].position.x -= 1.2;
				northPatroller[1].position.x -= 1.2;
				northPatroller[2].position.x -= 1.2;
				northPatroller[3].position.x -= 1.2;

			}
			else
			{
				moveNoirthRight = true;
			}

			if (leftPatroller[1].position.y < 600 && movesouthup == true)
			{
				leftPatroller[0].position.y += 1.2;
				leftPatroller[1].position.y += 1.2;
				leftPatroller[2].position.y += 1.2;
				leftPatroller[3].position.y += 1.2;

			}
			else
			{
				movesouthup = false;
			}

			if (leftPatroller[1].position.y >= 10 && movesouthup == false)
			{
				leftPatroller[0].position.y -= 1.2;
				leftPatroller[1].position.y -= 1.2;
				leftPatroller[2].position.y -= 1.2;
				leftPatroller[3].position.y -= 1.2;

			}
			else
			{
				movesouthup = true;
			}
			sf::VertexArray tri(sf::Triangles, 3);
			if (myPlayer.m_myPlayer.getGlobalBounds().intersects(prizeOne.getGlobalBounds())) {
				prizeOne.setPosition(2000, 2000);
				score += 1;
			}

			scoreText.setString("your score is :" + std::to_string(score));
			winText.setString("congrats you have won the game");

			tri[0].position = lightShape.getPosition();;
			tri[1].position = vecVisibilityPolygonPoints[vecVisibilityPolygonPoints.size() - 1].point;
			tri[2].position = vecVisibilityPolygonPoints[0].point;

			tri[0].color = sf::Color::Green;
			tri[1].color = sf::Color::Green;
			tri[2].color = sf::Color::Green;

			triangles.push_back(tri);
			

			target[0].position = sf::Vector2f(600, 550);
			target[1].position = sf::Vector2f(630, 550);
			target[2].position = sf::Vector2f(630, 570);

			sf::Vector2f targetTri[] = { sf::Vector2f(600,550),sf::Vector2f(630,550),sf::Vector2f(630,570) };
			playerPos=myPlayer.m_myPlayer.getPosition();
			for (auto& tr : triangles)
			{
				sf::Vector2f t1[3];
				t1[0].x = tr[0].position.x;
				t1[0].y = tr[0].position.y;
				t1[1].x = tr[1].position.x;
				t1[1].y = tr[1].position.y;
				t1[2].x = tr[2].position.x;
				t1[2].y = tr[2].position.y;
				if (TriTri2D(t1, targetTri))
				{
					std::cout << "intersection" << endl;

				}
				

			}



			if (score < 1)
			{
				for (auto& tr : triangles)
				{
					window.draw(tr);
				}
				window.draw(lightShape);
				window.draw(quad);
				window.draw(quad1);
				window.draw(quad2);
				window.draw(quad3);
				window.draw(target);
				window.draw(myPlayer.m_myPlayer);
				window.draw(northPatroller);
				window.draw(leftPatroller);
				window.draw(prizeOne);
				window.draw(scoreText);
				for (auto& vp : vecVisibilityPolygonPoints)
				{
					lightShape.setPosition(vp.point);

					window.draw(lightShape);
					
				}


			}
			else
			{
				window.draw(winText);
			
			}
			
			
		
			


			window.display();


			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}

