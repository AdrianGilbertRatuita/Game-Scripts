using Assets.Scripts;
using Assets.Scripts.Interfaces;
using Assets.Scripts.Managers;
using Assets.Scripts.Objects.NPC.Enemies.Enemy;
using Assets.Scripts.States;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyData : MonoBehaviour
{

    public string TheEnemy;
    public IEnemy ThisEnemy;
    private EnemyAI ThisAI;

    public string NAME;
    public int HP;
    public int ATTACK;
    public int LEVEL;
    public int GOLD;
    public int EXP;
    public string EnemyMoveState;
    public string EnemyState;


    // Use this for initialization
    void Start ()
    {

        Initialize();

	}
	
    public void Initialize()
    {

        ThisEnemy = EnemyManager.FindEnemyByName(TheEnemy);
        ThisAI = this.gameObject.GetComponent<EnemyAI>();
        NAME = ThisEnemy.EntityName;
        HP = ThisEnemy.HP;
        ATTACK = ThisEnemy.Attack;
        LEVEL = ThisEnemy.Level;
        GOLD = ThisEnemy.GoldReward;
        EXP = ThisEnemy.ExpReward;
        EnemyMoveState = ThisEnemy.EMoveState.ToString();
        EnemyState = ThisEnemy.EState.ToString();

    }

	// Update is called once per frame
	void Update ()
    {

        CheckAlive();
        FeedData();

	}
    
    private void CheckAlive()
    {

        if (this.ThisEnemy.HP <= 0)
        {

            this.ThisEnemy.EMoveState = MovementState.DYING;

        }

    }

    private void FeedData()
    {

        ThisAI.ReceiveData(ThisEnemy);

    }

    public void DamageEnemy(int PlayerAttack)
    {

        this.ThisEnemy.HP -= PlayerAttack;

    }

}
