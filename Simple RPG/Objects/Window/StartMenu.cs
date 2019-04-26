using Assets.Scripts.Managers;
using Assets.Scripts.Objects.Player;
using Assets.Scripts.Objects.Window;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class StartMenu : MonoBehaviour
{
    public static bool Started;
    public string[] Items;
    private int Selected;
    private GameObject PlayerObject;
    private PlayerControl Player;
    private MessageWindow NewMessage;
    private SelectionWindow WindowSelector;

    // Use this for initialization
    void Start ()
    {

        Initialize();

    }

    public void Initialize()
    {
        
        Selected = 0;
        PlayerObject = GameObject.FindGameObjectWithTag("Player");
        Player = PlayerObject.GetComponent<PlayerControl>();
        WindowSelector = new SelectionWindow(PlayerObject, new Vector3(3, 2));
        NewMessage = new MessageWindow(PlayerObject);
        Items = new string[] { "New Game", "Load Save", "Exit" };
        if (!Started)
        {
            Started = true;
            StartCoroutine(Wait());

        }
        PlayerObject.transform.position = Vector3.zero;

    }

    IEnumerator Wait()
    {

        yield return new WaitForSeconds(0.025f);
        WindowSelector.NewSelection(Items, Player, PlayerObject, false);

    }
	
	// Update is called once per frame
	void Update ()
    {

        if (WindowSelector.ReadThrough() &&
            WindowSelector.ThisWindow.IsActive &&
            WindowSelector.ThisWindow.IsVisible &&
            Selected == 0)
        { Selected = WindowSelector.Read(Player); }
        else if (Selected > 0)
        {

            switch(Selected)
            {
                case 1:
                    {

                        GameObject.Find("PlayerInput").transform.position = Vector3.zero;
                        break;
                    }
                case 2:
                    {

                        WindowSelector.HideWindow();
                        SceneManager.LoadScene(Player.ThisPlayer.SceneName);
                        break;
                    }
                case 3:
                    {

#if UNITY_EDITOR
                        UnityEditor.EditorApplication.isPlaying = false;
#else
                                 Application.Quit();
#endif
                        break;
                    }


            }
            Selected = 0;

        }

        if (NewMessage.ReadThrough() &&
        NewMessage.ThisWindow.IsActive &&
        NewMessage.ThisWindow.IsVisible)
        { NewMessage.Read(Player); }

        if (!WindowSelector.ReadThrough())
        {

            WindowSelector.InputisHere = false;

        }

    }

    public void GoToStart()
    {

        GamePlayer NewPlayer;
        string Input;
        Input = GameObject.Find("PlayerName").GetComponent<Text>().text;
        NewPlayer = new GamePlayer(Input);
        DataManager.SaveData(NewPlayer);
        SceneManager.LoadScene(Player.ThisPlayer.SceneName);

    }

}
