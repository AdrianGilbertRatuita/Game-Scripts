using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Checkpoint : MonoBehaviour
{


    // Is the checkpoint in use
    public bool isActive = true;

    //==============================================================================================================

    // Checkpoint Interval Properties

    // Current interval increase
    private int _currentInterval;
    public int currentInterval { get { return _currentInterval; } protected set { _currentInterval = value; } }

    // How much should the current interval increase
    [SerializeField]
    private int intervalIncrease;

    //==============================================================================================================

    // Checkpoint Time Gain Properties

    // How much time should be added to player current time - this is the Base and original time
    [SerializeField]
    private float timeIncrease;

    // We don't want players to not gain any time at all, this is the minimum possible time gained when reaching a checkpoint
    [SerializeField]
    private float minimumTimeGained;

    // How much time can be lost from until the player reaches this checkpoint
    [SerializeField]
    private float timeLoss;

    //Time before time loss starts subtracting from currentTimeIncrease
    [SerializeField]
    private float timeBeforeLossStarts;

    // Time that can be added to player current time subtracted by time loss delta, in Seconds
    private float _currentTimeIncrease;
    public float currentTimeIncrease { get { return _currentTimeIncrease; } protected set { _currentTimeIncrease = value; } }

    // Timer before loss starts
    private float _currentTimerBeforeLoss;
    public float currentTimerBeforeLoss { get { return _currentTimerBeforeLoss; } protected set { _currentTimerBeforeLoss = value; } }

    //==============================================================================================================

    // The Current Node this Checkpoint is assigned to
    private RaceTrackNode _currentNode;
    public RaceTrackNode currentNode { get { return _currentNode; } protected set { _currentNode = value; } }

    // Reference to owner - this prevents other users from triggering this checkpoint
    [SerializeField]
    private GameObject _checkpointOwner;
    //public GameObject checkpointOwner { get { return _checkpointOwner; } protected set { _checkpointOwner = value; } }

    // Reference to Game Manager
    private RaceTimeTrial raceManager;

    //==============================================================================================================

    // Start is called before the first frame update
    void Start()
    {

        SetupReferences();

    }

    private void SetupReferences()
    {

        raceManager = GameObject.FindObjectOfType<RaceTimeTrial>();
        _currentNode = raceManager.GetStartNode();

    }

    // Update is called once per frame
    void FixedUpdate()
    {

        UpdatePositionRelativeToNode();
        CheckpointTimerCountdown();

    }

    private void UpdatePositionRelativeToNode()
    {

        // Inherit parent node position
        this.transform.position = _currentNode.transform.position;

        // Inherit parent node rotation
        this.transform.rotation = _currentNode.transform.rotation;

    }

    private void CheckpointTimerCountdown()
    {

        // If current timer before loss is finished counting down
        if (currentTimerBeforeLoss <= 0)
        {

            // While current time increase is greater than minimum time gained
            if (currentTimeIncrease > minimumTimeGained)
            {

                currentTimeIncrease -= timeLoss * Time.deltaTime;

            }
            // Otherwise keep current Time Increase to the minimum time gained
            else
            {

                currentTimeIncrease = minimumTimeGained;

            }

        }
        else
        {

            currentTimerBeforeLoss -= Time.deltaTime;

        }


    }

    // Change checkpoint current node
    public void ChangeCurrentNode(RaceTrackNode newNode)
    {

        this._currentNode = newNode;

    }

    private void OnTriggerEnter(Collider other)
    {

        // Declare a temp gameobject
        GameObject OtherObject = null;

        if (other.GetComponentInParent<Racer>().gameObject && isActive)
        {

            // If other is a gameobject that exists assign it to OtherObject
            OtherObject = other.GetComponentInParent<Racer>().gameObject;

            // If the OtherObject is the owner
            if (OtherObject == _checkpointOwner)
            {

                // Get a temporary reference to player racer
                Racer thisRacer = OtherObject.GetComponent<Racer>();

                // Increase total checkpoints passed by 1
                // Increase remaining time by currentTimeIncrease
                thisRacer.checkpointTotal++;
                thisRacer.thisRacerCurrentTime += currentTimeIncrease;

                // Increase current interval
                currentInterval += intervalIncrease;

                // Reset time increase
                currentTimeIncrease = timeIncrease;

                // Reset timer before loss
                currentTimerBeforeLoss = timeBeforeLossStarts;

                // Move checkpoint to next interval node
                raceManager.MoveCheckpoint(this);

            }

        }

    }

}
