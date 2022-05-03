using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public enum States
{
    Idle = 0,
    Running = 1,
    Jumping = 2,
    Falling = 3,
    Sliding = 4,
    Dead = 5,
    Hurt = 6,
	Climbing = 7,
	Attack = 8
}


public class PlayerController : MonoBehaviour
{
    public Rigidbody2D rb;
    public float horizontalSpeed = 3.0f;
    public float jumpVerticalSpeed = 5.0f;
    Vector2 savedlocalScale;
    public BoxCollider2D boxCollider;
    public LayerMask groundLayer;
    float horizontalInput;
	float vertIput;
	public Animator anim;
	public States state;
	public GameObject tilemap;
	public cameraShake cameraScript;

	public bool ladderCollision;
	public bool NextLevelReady;
	public bool grounded;
	private float timeLeft = 0.5f;
	private float timeLeftAttackAnim = 0.3f;
	private bool attackPressed = false;
	public GameObject nextLevelButton;
	public GameObject interactText;
	public GameObject billBoardText;
	public GameObject villageText;
	public Vector2 playerPos;
	public Vector2 playerPosLevelTwo;
	public Vector2 playerPosFromLoadLevelTwo;

	public MobileInputController controllerScript;
	public Vector2 playerPosFromLoad = new Vector2(0.0f,0.0f);
	public bool loaded = false;

	// Start is called before the first frame update
	void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        savedlocalScale = transform.localScale;
        anim = GetComponent<Animator>();
		nextLevelButton.SetActive(false);
		interactText.SetActive(false);
		billBoardText.SetActive(false);
		villageText.SetActive(false);
		loaded = false;
	}

	// Update is called once per frame
	void Update()
	{
		if (NextLevelReady == true)
		{
			nextLevelButton.SetActive(true);
		}

		if (ladderCollision == true)
		{
			state = States.Climbing;
		}

		grounded = IsGrounded();

		horizontalInput = controllerScript.Horizontal;
		vertIput = controllerScript.Vertical;

		if (horizontalInput > 0.001f)
		{
			transform.localScale = new Vector2(savedlocalScale.x, savedlocalScale.y);
		}
		else if (horizontalInput < -0.001f)
		{
			transform.localScale = new Vector2(-savedlocalScale.x, savedlocalScale.y);
		}


		// animation updates 

		if (state == States.Idle)
		{

			if (IsGrounded())
			{
				//if (state == States.Climbing)
				//{
				//	rb.velocity = new Vector2(horizontalInput * horizontalSpeed, jumpVerticalSpeed);
				//}

				if (vertIput >= 0.5f)
				{
					rb.velocity = new Vector2(0.0f, jumpVerticalSpeed);
					state = States.Jumping;
				}

				if (horizontalInput > 0.001f)
				{
					state = States.Running;
				}
				else if (horizontalInput < -0.001f)
				{
					state = States.Running;
				}




			}
			if (!IsGrounded())
			{

				state = States.Falling;

			}

		}






		if (state == States.Climbing)
		{
			rb.velocity = new Vector2(horizontalInput * horizontalSpeed, jumpVerticalSpeed);

			if (ladderCollision == false)
			{
				state = States.Falling;

			}
		}

		if (state == States.Running)
		{
			if (horizontalInput == 0)
			{
				state = States.Idle;
			}
			if (IsGrounded())
			{

				if (vertIput >= 0.5f)
				{
					state = States.Jumping;
					rb.velocity = new Vector2(0.0f, jumpVerticalSpeed);
				}


			}

		}



		else if (state == States.Jumping)
		{

			if (rb.velocity.y <= 0.0f)
			{
				state = States.Falling;

			}
		}

		else if (state == States.Sliding)
		{

			if (Input.GetKey(KeyCode.LeftShift) == false)
			{
				state = States.Idle;
			}
			//If moving and left shift is not pressed then run

			//it no input idle

		}

		else if (state == States.Falling)
		{
			if (IsGrounded())
			{
				state = States.Idle;

			}
			//If moving and left shift is not pressed then run

			//it no input idle

		}

		else if (state == States.Dead)
		{

		}
		else if (state == States.Hurt)
		{


			timeLeft -= Time.deltaTime;
			if (timeLeft < 0)
			{
				state = States.Idle;
				timeLeft = 0.5f;
			}
		}

		else if (state == States.Attack)
		{

			timeLeftAttackAnim -= Time.deltaTime;
			if (timeLeftAttackAnim < 0)
			{
				state = States.Idle;
				timeLeftAttackAnim = 0.3f;
			}

		}

		rb.velocity = new Vector2(horizontalInput * horizontalSpeed, rb.velocity.y);
		anim.SetInteger("State", (int)state);



		if (gameObject.GetComponent<Grappler>().mouseClicDownForGrapler)
		{
			horizontalSpeed = 10;
		}

		else
		{
			horizontalSpeed = 3;
		}


		playerPos = transform.position;
		playerPosLevelTwo = transform.position;

		if (loaded)
		{
			transform.position = playerPosFromLoad;
			loaded = false;
		}


		if (transform.position.y < -20)
		{
			transform.position = new Vector2(-31.2f,2);
		}

	}

	public void attack()
	{
		state = States.Attack;
		attackPressed = true;

		if (state == States.Idle)
		{
			if (IsGrounded())
			{
					state = States.Attack;
					attackPressed = true;
			}
		}
		if (state == States.Running)
		{
			state = States.Attack;
			attackPressed = true;
		}
		else if (state == States.Jumping)
		{
			state = States.Attack;
			attackPressed = true;
		}
	}

	private bool IsGrounded()
    {
        RaycastHit2D raycastHit = Physics2D.BoxCast(boxCollider.bounds.center, boxCollider.bounds.size, 0, Vector2.down, 0.1f, groundLayer);
        return raycastHit.collider != null;
    }

	private void OnTriggerEnter2D(Collider2D collision)
	{

		if (collision.gameObject.tag == "GoblinEnemy")
		{
			state = States.Hurt;
			GameManager.instance.playerLives--;

		}
		if (collision.gameObject.tag == "bomb")
		{
			state = States.Hurt;

		}

		if (collision.gameObject.tag == "Ladder")
		{
			ladderCollision = true;
		}

		if (collision.gameObject.tag == "NextSign")
		{
			NextLevelReady = true;
		}

	}



	private void OnTriggerStay2D(Collider2D collision)
	{
		if (collision.gameObject.tag == "Letter")
		{
			//Debug.Log("noMessage!");
			interactText.SetActive(true);
			if (Input.GetKey(KeyCode.E))
			{
				billBoardText.SetActive(true);
				interactText.SetActive(false);
				Debug.Log("Message!");
			}

		}

		if (collision.gameObject.tag == "Billboard")
		{
			//Debug.Log("noMessage!");
			interactText.SetActive(true);
		}


		if (collision.gameObject.tag == "VillageSign")
		{
			villageText.SetActive(true);
		}

	}

	public void showMessage()
	{
		billBoardText.SetActive(true);
		interactText.SetActive(false);
		Debug.Log("Message!");
	}

	private void OnTriggerExit2D(Collider2D collision)
    {
		if (collision.gameObject.tag == "Ladder")
		{
			ladderCollision = false;
		}


		if (collision.gameObject.tag == "Billboard")
		{
			interactText.SetActive(false);
			billBoardText.SetActive(false);
		}

		if (collision.gameObject.tag == "Letter")
		{
			interactText.SetActive(false);
			billBoardText.SetActive(false);
		}

		if (collision.gameObject.tag == "VillageSign")
		{
			villageText.SetActive(false);
		}
	}


	private void OnCollisionEnter2D(Collision2D collision)
	{
		if (collision.gameObject.tag == "bomb")
		{
			state = States.Hurt;
			GameManager.instance.playerLives--;

		}
	}

	public void moveRight()
	{
		transform.position += Vector3.right * 15.0f * Time.deltaTime;
	}

	public void moveLeft()
	{
		transform.position += Vector3.right * -15.0f * Time.deltaTime;
	}


}
