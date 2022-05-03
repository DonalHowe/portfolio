using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bombManager : MonoBehaviour
{
    Rigidbody2D rb;
    float speed;
    Vector2 m_velocity;
    public GameObject m_particle;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        speed = -2;
        rb.velocity = new Vector2(0, speed);
       // rb.rotation = Random.Range(-90, 90);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Ground")
        {
            Instantiate(m_particle,transform);
            Destroy(gameObject, 2.0f);

        }
    }
    private void FixedUpdate()
    {
      
    }
}
