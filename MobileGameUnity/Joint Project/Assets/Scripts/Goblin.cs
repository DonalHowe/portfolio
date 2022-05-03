using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Goblin : MonoBehaviour
{
	public GameObject goblino;
	public Rigidbody2D rb;
	public float speed = 5;
	private float targetTime = 2.0f;
	private bool goingRight = true;
	public GameObject explosivePrefab;

	// Start is called before the first frame update
	void Start()
	{
	}

	// Update is called once per frame
	void Update()
	{
		rb.velocity = new Vector2(speed, 0);


	}

	private void FixedUpdate()
	{
		targetTime -= Time.deltaTime;

		if (targetTime <= 0.0f && goingRight)
		{
			speed = -5;
			targetTime = 2.0f;
			goingRight = false;
			goblino.transform.localScale = (new Vector3(-3f, goblino.transform.localScale.y, goblino.transform.localScale.z));
		}

		if (targetTime <= 0.0f && !goingRight)
		{
			speed = 5;
			targetTime = 2.0f;
			goingRight = true;
			goblino.transform.localScale = (new Vector3(3f, goblino.transform.localScale.y, goblino.transform.localScale.z));

		}

	}



	private void OnTriggerStay2D(Collider2D collision)
	{

		if (collision.gameObject.tag == "hitZone" && Input.GetMouseButtonDown(0))
		{
			for (var i = 0; i < 50; i++)
			{
				Instantiate(explosivePrefab, gameObject.transform.position, Quaternion.identity);
			}
			Destroy(goblino);
		}

	}
}