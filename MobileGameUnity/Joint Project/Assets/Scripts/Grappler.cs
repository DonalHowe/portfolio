using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Grappler : MonoBehaviour
{
    // Start is called before the first frame update
    public Camera mainCamera;
    public LineRenderer line;
    public DistanceJoint2D distanceJoint;
    public grapplerTiles grapplerTiles;
    public GameObject tiles;
    public bool mouseClicDownForGrapler = false;
	private ParticleSystem ps;
	public GameObject psBody;
	int toch = 0;

	// Start is called before the first frame update
	void Start()
    {
        distanceJoint.enabled = false;
        grapplerTiles = tiles.GetComponent<grapplerTiles>();
		ps = GameObject.Find("hookParicle").GetComponent<ParticleSystem>();
	}

    // Update is called once per frame
    void Update()
    {
        if (grapplerTiles.hook)
        {
            //if (Input.GetTouch(toch).phase == TouchPhase.Began)
            if (Input.touchCount > 1)
            {
                if (Input.GetTouch(1).phase == TouchPhase.Began)
                {
                    mouseClicDownForGrapler = true;
                    Vector2 mousePos = (Vector2)mainCamera.ScreenToWorldPoint(Input.GetTouch(1).position);
                    line.SetPosition(0, new Vector3(mousePos.x, mousePos.y, -0.1f));
                    line.SetPosition(1, transform.position);
                    distanceJoint.connectedAnchor = mousePos;
                    distanceJoint.enabled = true;
                    line.enabled = true;
                    line.SetWidth(0.05F, 0.05F);
                    psBody.transform.position = new Vector3(mousePos.x, mousePos.y, -0.1f);
                    ps.Play();


                }
            }
		}

        //if (Input.GetTouch(toch).phase == TouchPhase.Ended)
        if (Input.touchCount > 1)
        {
            if (Input.GetTouch(1).phase == TouchPhase.Ended)
            {
                mouseClicDownForGrapler = false;
                distanceJoint.enabled = false;
                line.enabled = false;
            }
        }

        if (distanceJoint.enabled)
        {
            line.SetPosition(1, transform.position);
        }
    }
}
