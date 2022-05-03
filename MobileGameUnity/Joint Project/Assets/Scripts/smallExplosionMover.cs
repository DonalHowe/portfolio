using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class smallExplosionMover : MonoBehaviour
{
    public bool exploded = false;
    // Start is called before the first frame update
    void Start()
    {
        exploded = true;

        //StartCoroutine(Shake(0.8f, 0.5f));
        float spreadX = Random.Range(-5.0f, 5.0f);
        float spreadY = Random.Range(-0.5f, 5.5f);
        GetComponent<Rigidbody2D>().velocity = new Vector2(spreadX, spreadY);
        Destroy(gameObject, 3.0f);
        //Destroy(gameObject, timeLeft);

    }

    // Update is called once per frame
    void Update()
    {

    }

    public IEnumerator Shake(float duration, float magnitude)
    {
        Vector3 originalPos = new Vector3(0, 0, -75);
        float elapsedTime = 0.0f;

        while (elapsedTime < duration)
        {
            float xOffset = Random.Range(-0.5f, 0.5f) * magnitude;
            float yOffset = Random.Range(-0.5f, 0.5f) * magnitude;

            GameObject.FindWithTag("camera").transform.position = new Vector3(xOffset, yOffset, originalPos.z);
            elapsedTime += Time.deltaTime;
            //wait one frame
            yield return null;


        }
        GameObject.FindWithTag("camera").transform.position = originalPos;
    }


}
