using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cameraShake : MonoBehaviour
{
	private Vector3 playerPos = new Vector3(0, 0, 0);
	void Start()
	{
		playerPos = GameObject.FindWithTag("Player").transform.position;
	}
	void Update()
	{
		playerPos = GameObject.FindWithTag("Player").transform.position;
	}

	public IEnumerator Shake(float duration, float magnitude)
	{
		Vector3 originalPos = new Vector3(0f, 0.2f, -3.33f);
		float elapsedTime = 0.0f;
		Debug.Log("SHAKE SHAKE SHAKE SHAKE SHAKE SHAKE SHAKE");

		while (elapsedTime < duration)
		{
			
			float xOffset = Random.Range(playerPos.x - 0.1f, playerPos.x + 0.1f) * magnitude;
			float yOffset = Random.Range(playerPos.y - 0.1f, playerPos.y + 0.1f) * magnitude;

			gameObject.transform.position = new Vector3(xOffset, yOffset, -3.33f);
			elapsedTime += Time.deltaTime;
			//wait one frame
			yield return null;


		}
		gameObject.transform.localPosition = originalPos;
	}


}

