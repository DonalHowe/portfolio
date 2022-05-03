using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class registerInteract : MonoBehaviour
{
    void Start()
    {
        GetComponent<Button>().onClick.AddListener(GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerController>().showMessage);
    }
}
