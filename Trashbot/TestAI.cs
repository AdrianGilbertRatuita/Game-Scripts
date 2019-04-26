using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using Assets.Adrian.Scripts;


public class TestAI : MonoBehaviour
{

    // Cop Flag
    public bool Cop;
    // Death Flag
    public bool Dying;
    // Manipulation Flag
    public bool Manipulated;
    // Current AI State
    public AIStates ThisAIState;
    // Flee Travel Speed;
    public float FleeSpeed;
    // Random Travel Speed
    public float RandomTravelSpeed;
    // Max Possible distance to randomly travel to
    public float RandomTravelDistance;
    // Distance from player before Fleeing
    public float FleeRange;
    // Max Possible distance this will flee towards to
    public float FleeDistance;
    // Distance from player to stop moving and attack
    public float AttackRange;
    // Direction relative to Player
    public Vector3 RelativePlayerDirection;
    // Direction Opposite to Player
    public Vector3 DirectionOppositePlayer;
    // Random Direction relative to NPCs
    public Vector3 RandomDirection;
    // Object's Starting Point
    public Vector3 InitialPoint;


    // Objects to spawn upon death
    public GameObject[] BodyChunks;
    

    // Remaining Distance to Target Point
    [SerializeField]
    private float RemainingDistance;
    // Current Distance from Player
    [SerializeField]
    private float PlayerDistance;
    // Reference to Player
    [SerializeField]
    private GameObject PlayerReference;
    // Reference to own NavMeshAgent component
    [SerializeField]
    private NavMeshAgent ThisNavAgent;


    //Animator reference
    [SerializeField]
    private Animator anim;




	// Use this for initialization
	void Start ()
    {

        // Get Starting Position
        InitialPoint = this.transform.position;
        // Set Dying to false
        Dying = false;
        // Set Manipulated to false
        Manipulated = false;
        // Set Default state to IDLE
        ThisAIState = AIStates.IDLE;
        // Get NavMeshAgent component
        ThisNavAgent = this.GetComponent<NavMeshAgent>();
        // Get reference to Player
        PlayerReference = GameObject.FindGameObjectWithTag("Player");
        // First Random Position
        ThisNavAgent.destination = NewRandomPosition();

        anim = GetComponentInChildren<Animator>();


    }
	
	// Update is called once per frame
	void Update ()
    {

        if (!Dying && !Manipulated)
        {

            // Update AI State
            UpdateState();
            // Update Current Direction Vectors
            UpdateDirections();
            // Act based on Current State
            EnactStates();

        }
        else if (Manipulated)
        {

            // Manipulation Logic here

        }
        //else if (Dying)
        //{

        //    // Death Logic here

        //}

    }

    public void Death()
    {
        Dying = true;

        foreach (GameObject g in BodyChunks)
        {
            g.transform.localScale = transform.localScale;
            Instantiate(g, transform.position, transform.rotation);

        }

        Destroy(gameObject);

    }

    private void UpdateState()
    {

        //anim.SetBool("Flee", false);
        //anim.SetBool("Idle", false);
        //anim.SetBool("Attack", false);

        if (PlayerDistance <= FleeRange && !Cop)
        {

            ThisAIState = AIStates.FLEE;
            ThisNavAgent.speed = FleeSpeed;
            //anim.SetBool("Flee", true);

        }
        else if (PlayerDistance <= FleeRange && Cop)
        {

            ThisAIState = AIStates.ATTACK;
            ThisNavAgent.speed = FleeSpeed;
            //anim.SetBool("Attack", true);
           

        }
        else
        {

            ThisAIState = AIStates.IDLE;
            ThisNavAgent.speed = RandomTravelSpeed;
            //anim.SetBool("Idle", true);

        }

    }

    private void UpdateDirections()
    {

        //
        RelativePlayerDirection = Vector3.zero;
        RelativePlayerDirection.x = this.transform.position.x - PlayerReference.transform.position.x;
        RelativePlayerDirection.z = this.transform.position.z - PlayerReference.transform.position.z;
        RelativePlayerDirection.Normalize();

        //
        RemainingDistance = ThisNavAgent.remainingDistance;

        //
        PlayerDistance = Vector3.Distance(this.transform.position, PlayerReference.transform.position);

        //
        DirectionOppositePlayer = RelativePlayerDirection * -1.0f;
        DirectionOppositePlayer.Normalize();

    }

    private void EnactStates()
    {

        //
        ThisNavAgent.isStopped = false;

        switch(ThisAIState)
        {

            case AIStates.IDLE:
                {
                    
                    // Random Chance to attempt to go back to Initial Point
                    if (Random.Range(0, 20) == 1 && ThisNavAgent.pathStatus == NavMeshPathStatus.PathComplete && ThisNavAgent.remainingDistance <= 1)
                    {

                        ThisNavAgent.destination = InitialPoint;

                    }
                    else
                    {

                        if (ThisNavAgent.pathStatus == NavMeshPathStatus.PathComplete && ThisNavAgent.remainingDistance <= 1)
                        {

                            ThisNavAgent.destination = NewRandomPosition();

                        }

                    }

                    break;
                }
            case AIStates.FLEE:
                {

                    if (ThisNavAgent.pathStatus == NavMeshPathStatus.PathComplete && ThisNavAgent.remainingDistance <= 1 && PlayerDistance <= FleeRange)
                    {

                        ThisNavAgent.destination = NewFleePosition();

                    }
                    if (ThisNavAgent.pathStatus == NavMeshPathStatus.PathInvalid)
                    {

                        ThisNavAgent.destination = NewFleePosition();

                    }
                    if (ThisNavAgent.pathStatus == NavMeshPathStatus.PathPartial)
                    {

                        ThisNavAgent.destination = NewFleePosition();

                    }
                    // Random Chance to go to a Control Point and Reset Travel Path
                    if (Random.Range(0, 20) == 1 && ThisNavAgent.pathStatus == NavMeshPathStatus.PathComplete && ThisNavAgent.remainingDistance <= 1)
                    {

                        if (GameObject.Find("ControlPoint") != null)
                        {

                            ThisNavAgent.destination = GameObject.Find("ControlPoint").transform.position;

                        }

                    }
                    break;
                }
            case AIStates.ATTACK:
                {

                    if (PlayerDistance <= AttackRange)
                    {

                        ThisNavAgent.isStopped = true;
                        ////anim.SetFloat("Speed", 0);
                    }

                    if (ThisNavAgent.pathStatus == NavMeshPathStatus.PathComplete && ThisNavAgent.remainingDistance <= 0 && PlayerDistance >= AttackRange)
                    {

                        ThisNavAgent.destination = NewAttackPosition();
                        //anim.SetFloat("Speed", 1);

                    }
                    else
                    {

                        // Put Attack Logic Here

                    }
                    
                    break;
                }

        }

    }

    private Vector3 NewFleePosition()
    {

        Vector3 AdjustedFleePosition;
        AdjustedFleePosition = Vector3.zero;
        AdjustedFleePosition.x = this.transform.position.x + (FleeDistance * RelativePlayerDirection.x) + Random.Range(-5.0f, 5.0f);
        AdjustedFleePosition.z = this.transform.position.z + (FleeDistance * RelativePlayerDirection.z) + Random.Range(-5.0f, 5.0f);

        return AdjustedFleePosition;

    }

    private Vector3 NewRandomPosition()
    {

        RandomDirection = Vector3.zero;
        RandomDirection.x = this.transform.position.x + Random.Range(RandomTravelDistance * -1.0f, RandomTravelDistance);
        RandomDirection.z = this.transform.position.z + Random.Range(RandomTravelDistance * -1.0f, RandomTravelDistance);

        return RandomDirection;

    }

    private Vector3 NewAttackPosition()
    {

        Vector3 AdjustedAttackPosition;
        AdjustedAttackPosition = Vector3.zero;
        AdjustedAttackPosition.x = this.transform.position.x + (AttackRange * DirectionOppositePlayer.x) + Random.Range(-5.0f, 5.0f);
        AdjustedAttackPosition.z = this.transform.position.z + (AttackRange * DirectionOppositePlayer.z) + Random.Range(-5.0f, 5.0f);

        return AdjustedAttackPosition;

    }

    private void OnDrawGizmos()
    {

        // Draw a Ray pointing to player
        Gizmos.color = Color.red;
        Gizmos.DrawRay(this.transform.position, RelativePlayerDirection * 5);

        // Draw a Ray opposite to player
        Gizmos.color = Color.blue;
        Gizmos.DrawRay(this.transform.position, DirectionOppositePlayer * 5);
    
        Vector3 CorrectedRandomDirection;
        CorrectedRandomDirection = Vector3.zero;
        CorrectedRandomDirection.x = RandomDirection.x - this.transform.position.x;
        CorrectedRandomDirection.z = RandomDirection.z - this.transform.position.z;

        // Draw a Ray pointing to a random direction
        Gizmos.color = Color.green;
        Gizmos.DrawRay(this.transform.position, CorrectedRandomDirection);

    }

}
