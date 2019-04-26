using Assets.Scripts.Objects.Window;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Messenger : MonoBehaviour
{

    public bool Here;
    public string Message;
    private GameObject PlayerObject;
    private PlayerControl Player;
    private MessageWindow MessageOut;

    // Use this for initialization
    void Start ()
    {

        Initialize();       

	}
	
    public void Initialize()
    {

        PlayerObject = GameObject.FindGameObjectWithTag("Player");
        Player = GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerControl>();
        MessageOut = new MessageWindow(WindowLocation.BOTTOM, PlayerObject);
        Here = false;

    }

	// Update is called once per frame
	void Update ()
    {

        if (MessageOut.ReadThrough() &&
            MessageOut.ThisWindow.IsActive &&
            MessageOut.ThisWindow.IsVisible)
        { MessageOut.Read(Player); }
        else if (Input.GetKeyDown(KeyCode.Return) && Here && Player.ThisPlayer.MovementStatus != Assets.Scripts.States.MovementState.INTERACTING)
        {

            MessageOut.NewMessage(Message, Player, true);

        }

    }   


}
