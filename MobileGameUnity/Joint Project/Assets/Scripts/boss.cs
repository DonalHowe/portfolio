using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class boss : MonoBehaviour
{
    public GameObject bomb;
    int throwBombCount;
    bool createdBomb;
    
 
    // Start is called before the first frame update
    void Start()
    {
        throwBombCount = 0;
        createdBomb = false;
    }
    private void Update()
    {
        throwBombCount++;
        if(throwBombCount==500)
        {
          //  if(createdBomb==false)
            //{
                Instantiate(bomb, transform);
                createdBomb = true;
           /// }
           
        }
        else if(throwBombCount>501)
        {
            throwBombCount = 0;
            
           
        }
    }

}
