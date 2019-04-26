using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestDetection : MonoBehaviour
{

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {

            Debug.Log("Entering");

        }
       

    }

    private void OnCollisionStay2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            
            Debug.Log("Staying");

        }
        

    }

    private void OnCollisionExit2D(Collision2D collision)
    {

        if (collision.gameObject.tag == "Player")
        {

            Debug.Log("Exiting");

        }
        

    }

}
