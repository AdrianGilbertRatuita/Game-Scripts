using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Assets.Scripts.States;

public class WeaponAttack : MonoBehaviour
{

    private EnemyData ChangeEnemyData;
    private PlayerControl ThisPlayer;
    private MovementState PlayerAttacking;

	// Use this for initialization
	void Start ()
    {

        ThisPlayer = GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerControl>();


	}
	
	// Update is called once per frame
	void Update ()
    {

        PlayerAttacking = ThisPlayer.ThisPlayer.MovementStatus;

	}

    private void OnTriggerEnter2D(Collider2D collision)
    {
        

        if (collision.gameObject.tag == "Enemy" && PlayerAttacking == MovementState.ATTACKING)
        {

            collision.GetComponent<EnemyData>().HP -= ThisPlayer.ATTACK;

        }


    }

    private void OnTriggerStay2D(Collider2D collision)
    {

        if (collision.gameObject.tag == "Enemy" && PlayerAttacking == MovementState.ATTACKING)
        {

            collision.GetComponent<EnemyData>().DamageEnemy((int)(ThisPlayer.ATTACK * 0.80f));

        }

    }


}