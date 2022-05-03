using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using UnityEngine.SceneManagement;


[Serializable]
class SaveData
{
	public int savedLives;
	public float savedPosX;
	public float savedPosY;

	public int savedLivesTwo;
	public float savedPosXTwo;
	public float savedPosYTwo;

	public string level;


}

public class Save : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }


	public void SaveGame()
	{
		if (GameObject.FindWithTag("gameManager").GetComponent<GameManager>().sceneName == "Level1")
		{
			BinaryFormatter bf = new BinaryFormatter();
			FileStream file = File.Create(Application.persistentDataPath + "/SaveData.txt");
			SaveData data = new SaveData();
			data.level = GameObject.FindWithTag("gameManager").GetComponent<GameManager>().sceneName;
			data.savedLives = GameObject.FindWithTag("gameManager").GetComponent<GameManager>().playerLives;
			data.savedPosX = GameObject.FindWithTag("Player").GetComponent<PlayerController>().playerPos.x;
			data.savedPosY = GameObject.FindWithTag("Player").GetComponent<PlayerController>().playerPos.y;
			bf.Serialize(file, data);
			file.Close();
			Debug.Log("Game data saved LEVEL 1!");
			Debug.Log(data.level);
		}

		if (GameObject.FindWithTag("gameManager").GetComponent<GameManager>().sceneName == "Level2")
		{
			BinaryFormatter bf = new BinaryFormatter();
			FileStream file = File.Create(Application.persistentDataPath + "/SaveData2.txt");
			SaveData data = new SaveData();
			data.level = GameObject.FindWithTag("gameManager").GetComponent<GameManager>().sceneName;
			data.savedLivesTwo = GameObject.FindWithTag("gameManager").GetComponent<GameManager>().playerLives;
			data.savedPosXTwo = GameObject.FindWithTag("Player").GetComponent<PlayerController>().playerPosLevelTwo.x;
			data.savedPosYTwo = GameObject.FindWithTag("Player").GetComponent<PlayerController>().playerPosLevelTwo.y;
			bf.Serialize(file, data);
			file.Close();
			Debug.Log("Game data saved LEVEL 2!");
			Debug.Log(data.level);
		}

	}


	public void LoadGame()
	{
		if (GameObject.FindWithTag("gameManager").GetComponent<GameManager>().sceneName == "Level1")
		{
			if (File.Exists((Application.persistentDataPath + "/SaveData.txt")))
			{
				BinaryFormatter bf = new BinaryFormatter();
				FileStream file = File.Open(Application.persistentDataPath + "/SaveData.txt", FileMode.Open);

				SaveData data = (SaveData)bf.Deserialize(file);
				file.Close();
				//GameObject.FindWithTag("gameManager").GetComponent<GameManager>().sceneName = data.level;
				//SceneManager.LoadScene(data.level);

				GameObject.FindWithTag("gameManager").GetComponent<GameManager>().playerLives = data.savedLives;
				GameObject.FindWithTag("Player").GetComponent<PlayerController>().playerPosFromLoad.x = data.savedPosX;
				GameObject.FindWithTag("Player").GetComponent<PlayerController>().playerPosFromLoad.y = data.savedPosY;
				GameObject.FindWithTag("Player").GetComponent<PlayerController>().loaded = true;
				Debug.Log("Game data loaded LEVEL 1!");
				Debug.Log(data.level);

			}
		}

		if (GameObject.FindWithTag("gameManager").GetComponent<GameManager>().sceneName == "Level2")
		{
			if (File.Exists((Application.persistentDataPath + "/SaveData2.txt")))
			{
				BinaryFormatter bf = new BinaryFormatter();
				FileStream file = File.Open(Application.persistentDataPath + "/SaveData2.txt", FileMode.Open);

				SaveData data = (SaveData)bf.Deserialize(file);
				file.Close();
				//GameObject.FindWithTag("gameManager").GetComponent<GameManager>().sceneName = data.level;
				//SceneManager.LoadScene(data.level);

				GameObject.FindWithTag("gameManager").GetComponent<GameManager>().playerLives = data.savedLivesTwo;
				GameObject.FindWithTag("Player").GetComponent<PlayerController>().playerPosFromLoad.x = data.savedPosXTwo;
				GameObject.FindWithTag("Player").GetComponent<PlayerController>().playerPosFromLoad.y = data.savedPosYTwo;
				GameObject.FindWithTag("Player").GetComponent<PlayerController>().loaded = true;
				Debug.Log("Game data loaded level 2!");
				Debug.Log(data.level);

			}
		}
	}



}
