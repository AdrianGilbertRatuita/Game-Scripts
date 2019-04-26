using Assets.Scripts.Managers;
using Assets.Scripts.Objects.Player;
using Assets.Scripts.Objects.Window;
using Assets.Scripts.States;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Menu : MonoBehaviour
{

    public string[] Items;
    private int Selected;
    private GameObject PlayerObject;
    private PlayerControl Player;
    private SelectionWindow WindowSelector;
    private MessageWindow NewMessage;
    private string SceneName;

    // Use this for initialization
    void Start ()
    {

        Initialize();

    }

    void Initialize()
    {

        Selected = 0;
        PlayerObject = GameObject.FindGameObjectWithTag("Player");
        Player = PlayerObject.GetComponent<PlayerControl>();
        WindowSelector = new SelectionWindow(PlayerObject, new Vector3(3, 2), new Vector3(5, 3));
        NewMessage = new MessageWindow(PlayerObject);
        Items = new string[] { "Save", "Load", "Exit" };

    }
	
	// Update is called once per frame
	void Update ()
    {

        if (WindowSelector.ReadThrough() &&
            WindowSelector.ThisWindow.IsActive &&
            WindowSelector.ThisWindow.IsVisible &&
            Selected == 0)
        { Selected = WindowSelector.Read(Player);}
        else if (Selected > 0 )
        {

            switch (Selected)
            {

                case 1:
                    {

                        NewMessage.NewMessage("Saving Data...", Player, false);
                        Player.ThisPlayer.SceneName = SceneManager.GetActiveScene().name;
                        Player.ThisPlayer.SavedLocation = PlayerObject.transform.position;
                        DataManager.SaveData(Player.ThisPlayer);
                        StartCoroutine(WaitIllusion(1, 3.0f));
                        break;
                    }
                case 2:
                    {
                        NewMessage.NewMessage("Loading Data...", Player, false);
                        StartCoroutine(WaitIllusion(2, 5.0f));
                        break;
                    }
                case 3:
                    {
                        NewMessage.NewMessage("Exiting Game", Player, false);
                        StartCoroutine(WaitIllusion(3, 3.0f));
                        break;
                    }

            }
            Selected = 0;

        }

        if (NewMessage.ReadThrough() &&
        NewMessage.ThisWindow.IsActive &&
        NewMessage.ThisWindow.IsVisible)
        { NewMessage.Read(Player); }

        InputBasedOnPlayerStatus();

        if (!WindowSelector.ReadThrough())
        {

            WindowSelector.InputisHere = false;

        }


    }

    private void InputBasedOnPlayerStatus()
    {

        if (Player.ThisPlayer.MovementStatus != MovementState.INTERACTING &&
            Player.ThisPlayer.MovementStatus != MovementState.DYING)
        {

            if (Input.GetKeyDown(KeyCode.Escape) && !WindowSelector.ReadThrough() && !WindowManager.AnyWindowActive() && !WindowSelector.InputisHere)
            {

                WindowSelector.NewSelection(Items, Player, PlayerObject, false);

            }

        }


    }

    IEnumerator WaitIllusion(int Action, float Duration)
    {

        Player.DoShomething();
        yield return new WaitForSeconds(Duration);

        switch (Action)
        {
            case 1:
                {

                    NewMessage.NewMessage("Save Complete!", Player, true);
                    break;
                }
            case 2:
                {

                    NewMessage.HideWindow();
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


        //
        

    }

}

