using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class grapplerTiles : MonoBehaviour
{
    public bool hook;
    // Start is called before the first frame update
    void Start()
    {
        hook = false;
    }

    // Update is called once per frame
    void Update()
    {
     
    }
    void OnMouseOver()
    {
        //If your mouse hovers over the GameObject with the script attached, output this message
        //Debug.Log("mouse is on : " + gameObject.name);
        hook = true;
    }

    void OnMouseExit()
    {
        //The mouse is no longer hovering over the GameObject so output this message each frame
        //Debug.Log("Mouse is no longer on GameObject.");
        hook = false;
    }
}
