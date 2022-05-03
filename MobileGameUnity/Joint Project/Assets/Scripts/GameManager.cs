using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{

    public static GameManager instance;
    public int playerLives;
    public TextMeshProUGUI livesText;

	//public int difficulty;
	Scene m_Scene;
	public string sceneName;

	public bool nextLevel;
    public bool gameWon;

    private void Awake()
    {

        if (instance == null)
        {
            instance = this;
            DontDestroyOnLoad(gameObject);
        }

        else if (instance != this)
        {
            Destroy(gameObject);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        playerLives = 5;
        nextLevel = false;
        gameWon = false;
        livesText = GameObject.FindGameObjectWithTag("livestext").GetComponent<TextMeshProUGUI>();
    }

    // Update is called once per frame
    void Update()
    {
        livesText.text = "Lives: " + instance.playerLives.ToString();

		m_Scene = SceneManager.GetActiveScene();
		sceneName = m_Scene.name;
	}

    public void Level2()
    {
        SceneManager.LoadScene("Level2");
    }
}
