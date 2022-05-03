using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class registerGM : MonoBehaviour
{
    void Start()
    {
        GetComponent<Button>().onClick.AddListener(GameManager.instance.gameObject.GetComponent<Save>().SaveGame);
    }

}
