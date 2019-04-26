using Assets.Scripts.Managers;
using Assets.Scripts.Objects.Player;
using Assets.Scripts.Objects.Window;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class OakGuy : MonoBehaviour
{

    private bool ShowOakDialogue;
    public string PlayerName;
    private string Message;
    private GameObject PlayerObject;
    private PlayerControl Player;
    private MessageWindow MessageOut;

    // Use this for initialization
    void Start()
    {

        Initialize();

    }

    public void Initialize()
    {

        PlayerObject = GameObject.FindGameObjectWithTag("Player");
        Player = GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerControl>();
        MessageOut = new MessageWindow(WindowLocation.BOTTOM, PlayerObject);
        PlayerObject.transform.position = Vector3.zero;
        ShowOakDialogue = false;
        Message = "Hello I'm Hero Oak.//////Welcome to the Wonderful world of Adrian's Finals RPG Game.Thank you for///playing and I hope you///give him a good grade.///Controls are ASWD, Attack with Left Mouse Button /or Left Control. Have Fun";
    }

    // Update is called once per frame
    void Update()
    {

        if (MessageOut.ReadThrough() &&
            MessageOut.ThisWindow.IsActive &&
            MessageOut.ThisWindow.IsVisible)
        { MessageOut.Read(Player); }   

        if (!MessageOut.ReadThrough() && ShowOakDialogue)
        {

            GamePlayer NewPlayer;
            string Input;
            Input = GameObject.Find("PlayerName").GetComponent<Text>().text;
            NewPlayer = new GamePlayer(Input);
            DataManager.SaveData(NewPlayer);
            SceneManager.LoadScene(Player.ThisPlayer.SceneName);

        }

    }

    public void ShowDialogue()
    {

        ShowOakDialogue = true;
        GameObject.Find("OakGuy").transform.position = Vector3.zero;
        GameObject.Find("PlayerInput").transform.position = new Vector3(-2000, 0, 0);
        PlayerObject.transform.position = Vector3.zero;
        MessageOut.NewMessage(Message, Player, true);

    }

    public void ShowAgain()
    {


        ShowOakDialogue = true;

    }

    public void ShowInput()
    {



    }

}
