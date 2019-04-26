using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Timer : MonoBehaviour
{

    int Counter;

    void Start ()
    {


    }
    
    public void Initialize()
    {

        Counter = 0;

    }

    void Update ()
    {

        if (Input.GetKeyDown(KeyCode.A))
        {

            Debug.Log("Count");
            Counter++;
            StartCoroutine(Count());

        }
        
    }

    private IEnumerator Count()
    {

        
        yield return new WaitForSeconds(5);
        Debug.Log(Counter);

        
    }





}
