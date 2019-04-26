using Assets.Scripts;
using Assets.Scripts.States;
using Assets.Scripts.Interfaces;
using Assets.Scripts.Objects.NPC.Enemies.Enemy;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Assets.Scripts.Managers;

public class EnemyAI : MonoBehaviour, IAnimatedEntity
{

    private PlayerControl ThisPlayer;
    private PlayerDetection ThisDetector;
    private Animator ThisAnimator;
    private IEnemy ThisEnemy;

    // Use this for initialization
    void Start ()
    {

        Initialize();

	}
	
	// Update is called once per frame
	void Update ()
    {

        PublicUpdate();

	}

    public void Initialize()
    {

        ThisPlayer = GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerControl>();
        ThisAnimator = this.gameObject.GetComponent<Animator>();
        ThisDetector = this.GetComponentInChildren<PlayerDetection>();
        ThisEnemy = new EmptyEnemy();

    }

    public void PublicUpdate()
    {

        if (ThisDetector.PlayerSee && 
            ThisPlayer.ThisPlayer.MovementStatus != MovementState.INTERACTING &&
            ThisPlayer.ThisPlayer.MovementStatus != MovementState.DYING)
        {

            this.transform.position = Vector3.Lerp(this.transform.position, ThisDetector.ReturnPlayer().transform.position, 0.025f);

        }

        if (ThisEnemy.EState == CharacterLivingState.ALIVE)
        {

            Animation_BasedOnMoveState();
            Action_BasedOnState();

        }
        if (AnimationManager.AnimationCheck("Dead", ThisAnimator))
        {

            Destroy(this.gameObject);

        }

    }

    public void Animation_BasedOnMoveState()
    {

        switch(ThisEnemy.EMoveState)
        {

            case MovementState.IDLE:
                {

                    if (!AnimationManager.AnimationCheck("Idle", ThisAnimator) && !ThisAnimator.IsInTransition(0))
                    {

                        ThisAnimator.CrossFade("Idle", 0.25f);

                    }
                    
                    break;
                }
            case MovementState.DYING:
                {

                    this.GetComponent<BoxCollider2D>().enabled = false;
                    if (!AnimationManager.AnimationCheck("Dying", ThisAnimator) && !ThisAnimator.IsInTransition(0))
                    {

                        if (!AnimationManager.AnimationCheck("Dead", ThisAnimator))
                        {

                            ThisPlayer.GiveMoney(ThisEnemy.GoldReward);
                            ThisAnimator.CrossFade("Dying", 0.25f);

                        }                    

                    }
                    
                    break;
                }

        }

    }

    public void Action_BasedOnState()
    {


        switch(ThisEnemy.EState)
        {

            case CharacterLivingState.ALIVE:
                {


                    break;
                }
            case CharacterLivingState.DEAD:
                {


                    break;
                }

        }

    }

    public void ReceiveData(IEnemy Data)
    {

        ThisEnemy = Data;

    }

}
