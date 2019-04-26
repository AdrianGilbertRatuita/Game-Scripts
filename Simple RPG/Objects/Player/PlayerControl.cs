using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Assets.Scripts.States;
using Assets.Scripts.Objects.Player;
using Assets.Scripts;
using Assets.Scripts.Interfaces;
using Assets.Scripts.Managers;

public class PlayerControl : MonoBehaviour, IAnimatedEntity
{

    //
    private float BaseSpeed;
    public float MoveSpeed;
    public Vector3 Direction;

    // VERY PUBLIC PLAYER DATA
    public GamePlayer ThisPlayer;
    public DirectionState PlayerDirection;
    public MovementState PlayerMovement;

    public string NAME;
    public int HP;
    public int ATTACK;
    public int LEVEL;
    public int GOLD;
    public int EXP;

    //[ShowOnly] public string NAME;
    //[ShowOnly] public int HP;
    //[ShowOnly] public int ATTACK;
    //[ShowOnly] public int LEVEL;
    //[ShowOnly] public int GOLD;
    //[ShowOnly] public int EXP;

    //
    private Vector3 NewPosition;
    private Rigidbody RB3D;
    private Rigidbody2D RB2D;
    private GamePlayer GamePlayer;
    private DirectionalInput Controls;
    private Animator ThisAnimator;
    private GameObject Weapon;

    void Start ()
    {

        Initialize();

	}
    // Standard Update
	void Update () { }
    private void FixedUpdate()
    {

        // Update Data
        this.ThisPlayer = this.GamePlayer;

        //
        NAME = this.GamePlayer.EntityName;
        HP = this.GamePlayer.HP;
        ATTACK = this.GamePlayer.Attack;
        LEVEL = this.GamePlayer.Level;
        GOLD = this.GamePlayer.Gold;
        EXP = this.GamePlayer.Experience;

        // Update
        PublicUpdate();

        //
        Direction.Normalize();

        // Update Position based on Rigidbody Attached
        if (RB2D != null) { Input2D(); }
        else if (RB3D != null) { Input3D(); }

    }
    void Input2D()
    {
     
        NewPosition = this.transform.position;
        NewPosition += Direction * MoveSpeed * Time.fixedDeltaTime;
        this.RB2D.MovePosition(NewPosition);

    }
    void Input3D()
    {

        NewPosition = this.transform.position;
        NewPosition += Direction * MoveSpeed * Time.fixedDeltaTime;
        this.RB3D.MovePosition(NewPosition);

    }
    public void CreateCharacter()
    {

        this.GamePlayer = new GamePlayer();      

    }
    public void Initialize()
    {

        // Store Default Speed
        this.BaseSpeed = MoveSpeed;
        CanAttackAgain = true;
        PreventDamage = false;

        // Instantiate New Objects
        if (this.GamePlayer == null) { GamePlayer = DataManager.LoadData(); this.transform.position = GamePlayer.SavedLocation; }
        Controls = new DirectionalInput();

        this.ThisAnimator = this.GetComponent<Animator>();
        this.Weapon = GameObject.FindGameObjectWithTag("PlayerWeapon");

        // Try to get Rigidbody (2D/3D)
        RB2D = this.GetComponent<Rigidbody2D>();
        RB3D = this.GetComponent<Rigidbody>();

    }

    #region DEBUGGING
    #if DEBUG
    bool Debugging;

    public void DebugLog()
    {

        if (Input.GetKey(KeyCode.LeftControl) && Input.GetKey(KeyCode.L))
        {

            if (Debugging) { Debugging = false; }
            else { Debugging = true; }

        }

        if (Debugging)
        {

            string RigidBodyCheck;
            RigidBodyCheck = string.Empty;

            if (RB2D != null) { RigidBodyCheck = "RB2D"; } else if (RB3D != null) { RigidBodyCheck = "RB3D"; }

            Debug.Log("─────────────────────────────────────────────────────────");
            Debug.Log("PLAYER DEBUG");
            Debug.Log("> GAMEOBJECT DATA <");
            Debug.Log("PLAYER STATE:" + GamePlayer.MovementStatus.ToString());
            Debug.Log("PLAYER DIRECTION:" + this.Direction.ToString());
            Debug.Log("PLAYER RIGIDBODY STATUS: " + RigidBodyCheck);
            Debug.Log("> PLAYER DATA <");
            Debug.Log("PLAYERHP: " + GamePlayer.HP.ToString());
            Debug.Log("PLAYERMAXHP: " + GamePlayer.MaxHP.ToString());
            Debug.Log("PLAYERLEVEL: " + GamePlayer.Level.ToString());
            Debug.Log("PLAYERNAME: " + GamePlayer.EntityName.ToString());
            Debug.Log("PLAYEREXP: " + GamePlayer.Experience.ToString());
            Debug.Log("PLAYERGOLD: " + GamePlayer.Experience.ToString());
            Debug.Log("─────────────────────────────────────────────────────────");

        }

    }

    #endif
    #endregion 

    public void DoShomething() { this.GamePlayer.MovementStatus = MovementState.INTERACTING; }
    public void NotDoShomething() { this.GamePlayer.MovementStatus = MovementState.IDLE; }
    public bool PreventKeyHold(KeyCode Key)
    {

        if (Input.GetKey(Key))
        {

            return true;

        }

        return false;
    }
    public bool AnimationCheck(string Animation)
    {

        if (ThisAnimator.GetCurrentAnimatorStateInfo(0).IsName(Animation))
        {

            return true;

        }

        return false;
    }

    public void OrientToDirection(DirectionState NewDiriction)
    {

        this.GamePlayer.CurrentDirection = NewDiriction;

    }

    // Local Input Handler
    public void GiveMoney(int Gold)
    {

        this.GamePlayer.Gold += Gold;

    }
    public void InputHandler()
    {

        // Directional Commands
        if (Input.GetKeyDown(KeyCode.W) ||
            Input.GetKeyDown(KeyCode.S) ||
            Input.GetKeyDown(KeyCode.A) ||
            Input.GetKeyDown(KeyCode.D) )
        {
     
            this.GamePlayer.MovementStatus = MovementState.WALKING;

        }

        this.Direction += Controls.InputDirection();

        // Normalize Direction
        this.Direction.Normalize();
        
        if (Input.GetMouseButtonDown(0) || Input.GetKeyDown(KeyCode.LeftControl) && this.GamePlayer.MovementStatus != MovementState.ATTACKING && CanAttackAgain)
        {

            this.MoveSpeed = 0;
            this.GamePlayer.MovementStatus = MovementState.ATTACKING;

        }

        // Run Command
        if (Input.GetKey(KeyCode.LeftShift))
        {

            this.MoveSpeed = this.BaseSpeed * 2;
            this.GamePlayer.MovementStatus = MovementState.RUNNING;

        }

        // Idle State
        if (!Input.anyKey)
        {

            this.Direction = Vector3.zero;
            this.GamePlayer.MovementStatus = MovementState.IDLE;

        }

        this.GamePlayer.CurrentDirection = Controls.NewPlayerDirection;
        
    }
    public void Action_BasedOnState()
    {

        switch (GamePlayer.MovementStatus)
        {

            case MovementState.IDLE:
                {

                    this.MoveSpeed = 0;
                    break;

                }
            case MovementState.WALKING:
                {

                    this.MoveSpeed = BaseSpeed;
                    break;

                }
            case MovementState.ATTACKING:
                {

                    
                    break;

                }
            case MovementState.INTERACTING:
                {

                    this.MoveSpeed = 0;
                    this.Direction = Vector3.zero;
                    break;

                }
            case MovementState.DYING:
                {
                    if (!ThisAnimator.IsInTransition(0) && !AnimationCheck("Dying"))
                    {
                        ThisAnimator.CrossFade("Dying", 0.25f);
                    }                   
                    break;

                }

        }

    }
    public void Animation_BasedOnMoveState()
    {
        switch (GamePlayer.CurrentDirection)
        {

            case DirectionState.UP:
                {

                    Weapon.transform.rotation = Quaternion.Euler(0, 0, 180);
                    if (GamePlayer.MovementStatus == MovementState.IDLE && !ThisAnimator.IsInTransition(0) && !AnimationCheck("IdleUp") && !AnimationCheck("AttackUp")) { ThisAnimator.CrossFade("IdleUp", 0.05f); }
                    else if (GamePlayer.MovementStatus == MovementState.WALKING && !ThisAnimator.IsInTransition(0)) { ThisAnimator.Play("WalkUp"); }
                    else if (GamePlayer.MovementStatus == MovementState.RUNNING && !ThisAnimator.IsInTransition(0)) { ThisAnimator.Play("WalkUp"); }
                    else if (GamePlayer.MovementStatus == MovementState.ATTACKING && !ThisAnimator.IsInTransition(0) && CanAttackAgain) { ThisAnimator.CrossFade("AttackUp", 0.25f); }
                    break;
                }
            case DirectionState.DOWN:
                {
                    Weapon.transform.rotation = Quaternion.Euler(0, 0, 0);
                    if (GamePlayer.MovementStatus == MovementState.IDLE && !ThisAnimator.IsInTransition(0) && !AnimationCheck("IdleDown") && !AnimationCheck("AttackDown")) { ThisAnimator.CrossFade("IdleDown", 0.05f); }
                    else if (GamePlayer.MovementStatus == MovementState.WALKING && !ThisAnimator.IsInTransition(0)) { ThisAnimator.CrossFade("WalkDown", 0.05f); }
                    else if (GamePlayer.MovementStatus == MovementState.RUNNING && !ThisAnimator.IsInTransition(0)) { ThisAnimator.CrossFade("WalkDown", 0.05f); }
                    else if (GamePlayer.MovementStatus == MovementState.ATTACKING && !ThisAnimator.IsInTransition(0) && CanAttackAgain) { ThisAnimator.CrossFade("AttackDown", 0.25f); }
                    break;
                }
            case DirectionState.LEFT:
                {
                    Weapon.transform.rotation = Quaternion.Euler(0, 0, -90);
                    if (GamePlayer.MovementStatus == MovementState.IDLE && !ThisAnimator.IsInTransition(0) && !AnimationCheck("IdleLeft") && !AnimationCheck("AttackLeft")) { ThisAnimator.CrossFade("IdleLeft", 0.05f); }
                    else if (GamePlayer.MovementStatus == MovementState.WALKING && !ThisAnimator.IsInTransition(0)) { ThisAnimator.CrossFade("WalkLeft", 0.05f); }
                    else if (GamePlayer.MovementStatus == MovementState.RUNNING && !ThisAnimator.IsInTransition(0)) { ThisAnimator.CrossFade("WalkLeft", 0.05f); }
                    else if (GamePlayer.MovementStatus == MovementState.ATTACKING && !ThisAnimator.IsInTransition(0) && CanAttackAgain) { ThisAnimator.CrossFade("AttackLeft", 0.25f); }
                    break;
                }
            case DirectionState.RIGHT:
                {
                    Weapon.transform.rotation = Quaternion.Euler(0, 0, 90);
                    if (GamePlayer.MovementStatus == MovementState.IDLE && !ThisAnimator.IsInTransition(0) && !AnimationCheck("IdleRight") && !AnimationCheck("AttackRight")) { ThisAnimator.CrossFade("IdleRight", 0.05f); }
                    else if (GamePlayer.MovementStatus == MovementState.WALKING && !ThisAnimator.IsInTransition(0)) { ThisAnimator.CrossFade("WalkRight", 0.05f); }
                    else if (GamePlayer.MovementStatus == MovementState.RUNNING && !ThisAnimator.IsInTransition(0)) { ThisAnimator.CrossFade("WalkRight", 0.05f); }
                    else if (GamePlayer.MovementStatus == MovementState.ATTACKING && !ThisAnimator.IsInTransition(0) && CanAttackAgain) { ThisAnimator.CrossFade("AttackRight", 0.25f); }
                    break;

                }
        }
    }
    public void PublicUpdate()
    {

        if (CanAttackAgain &&
            this.GamePlayer.MovementStatus != MovementState.INTERACTING && 
            this.GamePlayer.MovementStatus != MovementState.ATTACKED && 
            this.GamePlayer.MovementStatus != MovementState.DYING)
        {

            InputHandler();
            Animation_BasedOnMoveState();

        }

        //
        Action_BasedOnState();
        PlayerMovement = GamePlayer.MovementStatus;
        PlayerDirection = GamePlayer.CurrentDirection;

    }

    private bool PreventDamage;
    private bool CanAttackAgain;

    private void OnCollisionStay2D(Collision2D collision)
    {

        if (collision.gameObject.tag == "Enemy" && !PreventDamage && collision.gameObject.GetComponent<EnemyData>().ThisEnemy.EState == CharacterLivingState.ALIVE)
        {


            if (this.GamePlayer.HP <= 0) { this.GamePlayer.MovementStatus = MovementState.DYING; }
            else
            {
                PreventDamage = true;
                this.GamePlayer.HP -= collision.gameObject.GetComponent<EnemyData>().ATTACK;
            }

        }
        else
        {

            if (!BeReAttacked)
            {
                BeReAttacked = true;
                StartCoroutine(CanBeAttacked(0.50f));

            }

        }

    }
    private bool BeReAttacked;
    private IEnumerator CanBeAttacked(float Seconds)
    {

        BeReAttacked = true;
        yield return new WaitForSeconds(Seconds);
        PreventDamage = false;
        BeReAttacked = false;

    }

}


