using UnityEngine;
using System.Collections;

namespace VividVision.BarnyardBounce
{
	public class Animal : MonoBehaviour
	{
		public float jumpHeight = 1;
		public float weight = 1;
		public float moveSpeed = 1;
		public bool StartsActive = false;
        public bool canUseSkill = true;
        public float energRecoverySkillEnableThreshold = 0.5f;
		public JumpingChickenControl jumpControl;
		public IslandJumpControl islandJumpControl;
        public PlayerSelectManager thisManager;
        public PlayerSelect thisPlayerSelect;

		//** -- Audio Clips 
		public AudioClip lifeLostClip;
		public AudioClip itemCollectedClip;
		public AudioClip[] levelUpClips;

		// Use this for initialization
		void Start()
		{



		}

		protected void SetupReferences()
		{

            thisManager = GameObject.FindObjectOfType<PlayerSelectManager>();
            thisPlayerSelect = this.gameObject.GetComponentInChildren<PlayerSelect>();
			jumpControl = this.gameObject.GetComponent<JumpingChickenControl>();
			islandJumpControl = GameObject.Find("ChickyJumpSceneStuff").GetComponent<IslandJumpControl>();

		}

		// Update is called once per frame
		void Update()
		{

            if (!canUseSkill)
            {

                if (jumpControl.Energy >= energRecoverySkillEnableThreshold)
                {

                    canUseSkill = true;

                }

            }

		}

		// Moves animal to starting pawn point
		public void startingSpawnPoint(Transform location)
		{

			this.gameObject.transform.position = location.position;
			this.gameObject.transform.rotation = location.rotation;
			//load our respawnpoint from our scene  once the character is loaded
			jumpControl = this.gameObject.GetComponent<JumpingChickenControl>();
			jumpControl.RespawnPoint = GameObject.Find("RespawnPoint").transform;

		}

        // function to call for skill input
        protected virtual void CheckSkillInput()
        {

            // do something

        }

        // execute skkil
        protected virtual void ExecuteSkill()
		{ 
			
			// do something
			
		}

		// Recover energy function, can be overwritten for different recovery implementations
		protected virtual void RecoverEnergy()
		{

            jumpControl.Energy += jumpControl.EnergyRechargeRate * Time.deltaTime;

        }

        // Make sure energy is at correct values
        protected void EnergyCheck()
        {

            if (jumpControl.Energy < 0) // Make sure Energy doesn't go negative
            {

                jumpControl.Energy = 0;

            }

            if (jumpControl.Energy > jumpControl.EnergyMax) // Make sure Energy doesn't go beyond max value
            {

                jumpControl.Energy = jumpControl.EnergyMax;

            }

            if (!canUseSkill)
            {

                if (jumpControl.Energy >= energRecoverySkillEnableThreshold) canUseSkill = true;

            }

        }

	}
}

