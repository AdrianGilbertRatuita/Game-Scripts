using Assets.Scripts.Managers;
using Assets.Scripts.Objects.Window;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GOMessage : MonoBehaviour {

    public string[] Items;
    private int Selected;
    private GameObject PlayerObject;
    private PlayerControl Player;
    private SelectionWindow WindowSelector;
    private MessageWindow NewMessage;
    private string SceneName;

    // Use this for initialization
    void Start()
    {

        Initialize();

    }

    void Initialize()
    {

        Selected = 0;
        PlayerObject = GameObject.FindGameObjectWithTag("Player");
        Player = PlayerObject.GetComponent<PlayerControl>();
        WindowSelector = new SelectionWindow(PlayerObject, new Vector3(4, 2));
        NewMessage = new MessageWindow(PlayerObject);
        
        NoWindow = false;
        Items = new string[] { "Load Save File", "Exit" };

    }

    private bool NoWindow;

    // Update is called once per frame
    void Update()
    {

        //Debug.Log(CheckIfDead());
        if (CheckIfDead() && !NoWindow)
        {

            WindowSelector.NewSelection(Items, false);
            NoWindow = true;

        }
        else if (CheckIfDead())
        {

            GameOver();

        }
        

    }

    bool CheckIfDead()
    {

        if (Player.ThisPlayer.MovementStatus == Assets.Scripts.States.MovementState.DYING)
        {

            return true;

        }
        return false;
    }

    public void GameOver()
    {

        if (WindowSelector.ReadThrough() &&
        WindowSelector.ThisWindow.IsActive &&
        WindowSelector.ThisWindow.IsVisible &&
        Selected == 0)
        { Selected = WindowSelector.Read(Player); }
        else if (Selected > 0)
        {

            switch (Selected)
            {

                case 1:
                    {

                        NewMessage.NewMessage("Loading Data...", Player, false);
                        Player.ThisPlayer.SceneName = SceneManager.GetActiveScene().name;
                        Player.ThisPlayer.SavedLocation = PlayerObject.transform.position;
                        NewMessage.HideWindow();
                        WindowSelector.HideWindow();
                        SceneManager.LoadScene(Player.ThisPlayer.SceneName);
                        break;
                    }
                case 2:
                    {
                        NewMessage.NewMessage("Exiting Game", Player, false);
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

    IEnumerator LoadLevelIllussion()
    {

        Player.DoShomething();
        yield return new WaitForSeconds(1);
        NewMessage.HideWindow();
        WindowSelector.HideWindow();

        //
        SceneManager.LoadScene(Player.ThisPlayer.SceneName);

    }
}
