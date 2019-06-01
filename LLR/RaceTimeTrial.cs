using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityStandardAssets.Vehicles.Car;
public class RaceTimeTrial : MonoBehaviour
{

    // Starting time for all racers
    // in Minutes
    [SerializeField]
    private Vector3 startTime = new Vector3(0, 2, 0);

    // Has the race started
    public bool raceStarted = false;

    // List of all racers in the field
    [SerializeField]
    private List<Racer> racers;

    // A list of all possible track nodes
    [SerializeField]
    private List<RaceTrackNode> trackNodes;

    // All checkpoints, do operations with checkpoints if necessary
    [SerializeField]
    private List<Checkpoint> checkPoints;

    // Where do all the checkpoint starts
    [SerializeField]
    private RaceTrackNode startNode;

    // A sorted/ordered list of all possible tracks
    // MAY NEED TO CHANGE THIS FOR DYNAMIC ROAD TRACKS AND FORKS
    private SortedList<int, RaceTrackNode> orderedTracks;

    // Start is called before the first frame update
    void Start()
    {

        SetupReferences();
        SetupTracksAndNodes();
        SetupRace();

    }

    // Get references to all exisiting game objects
    private void SetupReferences()
    {

        trackNodes = new List<RaceTrackNode>(GameObject.FindObjectsOfType<RaceTrackNode>());

        orderedTracks = new SortedList<int, RaceTrackNode>();

        checkPoints = new List<Checkpoint>(GameObject.FindObjectsOfType<Checkpoint>());

        racers = new List<Racer>(GameObject.FindObjectsOfType<Racer>());

    }

    // Setup nodes and tracks
    private void SetupTracksAndNodes()
    {

        for (int i = 0; i < trackNodes.Count; i++)
        {

            orderedTracks.Add(trackNodes[i].RaceTrackNumber, trackNodes[i]);

        }

        for (int i = 0; i < trackNodes.Count - 1; i++)
        {

            if (i < orderedTracks.Count + 1)
            {

                orderedTracks[i].NextNode = orderedTracks[i + 1];

            }

        }

        orderedTracks[orderedTracks.Count - 1].NextNode = orderedTracks[0];

    }

    // Setup racers and checkpoints
    private void SetupRace()
    {

        float hoursInSeconds = startTime.x * 3600;
        float minutesInSeconds = startTime.y * 60;
        float seconds = startTime.z;

        foreach (Racer racer in racers)
        {

            racer.gameObject.GetComponent<CarUserControl>().canMove = true;
            racer.thisRacerCurrentTime = hoursInSeconds + minutesInSeconds + seconds;

        }

        if (!raceStarted)
        {

            // Pre-race Logic Here


        }

    }


    // Update is called once per frame
    void Update()
    {

        if (raceStarted)
        {

            Countdown();

        }

    }

    // Determine if racer no longer has time
    private void Countdown()
    {

        foreach (Racer racer in racers)
        {

            if (racer.thisRacerCurrentTime <= 0)
            {

                racer.gameObject.GetComponent<CarUserControl>().canMove = false;

            }

        }

    }

    // Move Checkpoint to new location based on new interval
    public void MoveCheckpoint(Checkpoint checkpointToMove)
    {

        int nextNode = checkpointToMove.currentNode.RaceTrackNumber + checkpointToMove.currentInterval;

        if (nextNode > orderedTracks.Count)
        {

            int max = (orderedTracks.Count - 1) - nextNode;
            checkpointToMove.ChangeCurrentNode(orderedTracks[max]);

        }
        else
        {

            checkpointToMove.ChangeCurrentNode(orderedTracks[nextNode]);

        }

    }

    public RaceTrackNode GetStartNode()
    {

        return startNode;

    }

}
