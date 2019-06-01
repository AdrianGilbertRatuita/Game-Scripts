using UnityEngine;
using System.Collections;

namespace VividVision.BarnyardBounce
{
	public class Sheep : Animal
	{

        [SerializeField]
        private bool coolingDown = false;

        private float cooldownTime = 0;

        [SerializeField]
        private float doubleJumpCooldown = 5;

        public float jumpCost = 0.25f;

        private float originalJumpHeight;

        [SerializeField]
        private float sheepModifiedJumpHeight;

        // Use this for initialization
        void Start()
		{

			SetupReferences();

            originalJumpHeight = this.jumpHeight;

		}

		// Update is called once per frame
		void FixedUpdate()
		{


            // Check if player can use skills
            CheckSkillInput();

        }

        protected override void CheckSkillInput()
        {

            // Determine if this is the current player
            if (this.thisManager.CurrentPlayer == this.thisPlayerSelect)
            {

                // Make sure skill can be used
                // Determine if double jump is not cooling down
                // Determine if player energy is greater than energy cost
                // Determine if player is not doing Golden Egg Minigame
                if (canUseSkill 
                    && In.PrimaryDown
                    && !coolingDown
                    && jumpControl.Energy - jumpCost > jumpCost
                    && islandJumpControl.GameState != IslandJumpControl.GameStates.Measuring
					&& jumpControl.ChickenState == JumpingChickenControl.ChickenStates.Jumping
                   )
                {

                    // Set cooldown time to 0
                    cooldownTime = 0;

                    // Set cooldown to true
                    coolingDown = true;

                    // Execute Skill now
                    ExecuteSkill();

                }
                // Otherwise recover energy
                else if (jumpControl.Energy != jumpControl.EnergyMax)
                {

                    RecoverEnergy();

                }

                // If skill is not in use or player is not pressing primary down
                if (!canUseSkill || !In.PrimaryDown || coolingDown)
                {

                    this.jumpHeight = sheepModifiedJumpHeight;

                }

                // 
                if (coolingDown)
                {

                    cooldownTime += Time.deltaTime;
                   
                    if (cooldownTime > doubleJumpCooldown)
                    {

                        coolingDown = false;

                    }

                }

                // Ensure energy is at the correct values
                EnergyCheck();

            }

        }

        protected override void ExecuteSkill()
		{

            // Modify current sheep jump
            this.jumpHeight = sheepModifiedJumpHeight;

            // Subtract fixed jump cost to current energy
            jumpControl.Energy -= jumpCost;

			// Do another jump
			jumpControl.DoubleJump();
            //jumpControl.Jump();

            // If energy is less than or equal to 0, prevent the usage of skills
            if (jumpControl.Energy <= 0) canUseSkill = false;

        }

	}

}


