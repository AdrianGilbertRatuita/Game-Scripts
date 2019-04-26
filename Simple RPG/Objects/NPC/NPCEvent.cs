using Assets.Scripts.Objects.Window;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NPCEvent : MonoBehaviour
{

    public string Message;
    private GameObject Messenger;
    // Use this for initialization
    void Start ()
    {

        Initialize();

	}

    public void Initialize()
    {

        Messenger = GameObject.Find("Messenger");

    }

    // Update is called once per frame
    void Update ()
    {


	}

    private void OnTriggerStay2D(Collider2D collision)
    {

        if (collision.gameObject.tag == "PlayerWeapon")
        {

            Debug.Log("Here");
            Messenger.GetComponent<Messenger>().Message = Message;
            Messenger.GetComponent<Messenger>().Here = true;


        }


    }

    private void OnTriggerExit2D(Collider2D collision)
    {

        if (collision.gameObject.tag == "PlayerWeapon")
        {

            Messenger.GetComponent<Messenger>().Here = false;


        }


    }

}
