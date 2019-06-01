using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class RaceTrackNode : MonoBehaviour
{

    // Race track number in list
    public int RaceTrackNumber;

    // Race track next node
    public RaceTrackNode NextNode;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    // Debug UI Drawer for connection
    private void OnDrawGizmos()
    {

        Gizmos.color = Color.red;

        if (NextNode)
        {

            Gizmos.DrawLine(this.transform.position, NextNode.transform.position);


        }

    }

}



