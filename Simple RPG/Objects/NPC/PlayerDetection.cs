using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerDetection : MonoBehaviour {

    public bool PlayerSee;
    private GameObject Player;

	// Use this for initialization
	void Start ()
    {

        PlayerSee = false;


	}
	
	// Update is called once per frame
	void Update ()
    {
		
	}

    public GameObject ReturnPlayer()
    {

        return Player;

    }

    private void OnTriggerEnter2D(Collider2D other)
    {

        if (other.gameObject.tag == "Player")
        {

            PlayerSee = true;
            Player = other.gameObject;

        }

    }

    private void OnTriggerStay2D(Collider2D other)
    {

        if (other.gameObject.tag == "Player")
        {

            PlayerSee = true;
            Player = other.gameObject;

        }

    }

    private void OnTriggerExit2D(Collider2D other)
    {

        if (other.gameObject.tag == "Player")
        {

            PlayerSee = false;
            Player = null;

        }

    }


}
