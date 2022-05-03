using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RegisterGMLoad : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        GetComponent<Button>().onClick.AddListener(GameManager.instance.gameObject.GetComponent<Save>().LoadGame);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
