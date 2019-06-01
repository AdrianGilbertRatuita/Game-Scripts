using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace VividVision.BarnyardBounce
{

	public class Chicken : Animal
	{

        // Holder for original fall speed
        private float originalFallSpeed;

        // Value for modified fall speed
        public float chickenModifiedFallSpeed;

        // Use this for initialization
        void Start()
		{

            // Setup animal references to Island and Jump Controls
			SetupReferences();

            // Grab original fall speed
            originalFallSpeed = jumpControl.FallSpeed;

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
                // Determine if Primary button is held
                // Determine if player is not doing Golden Egg Minigame
                // Determine if player is not falling down
                if (canUseSkill
                    && In.Primary
                    && jumpControl.Energy != 0
                    && islandJumpControl.GameState != IslandJumpControl.GameStates.Measuring
                    )
                {

                    //
                    ExecuteSkill();

                }
                // Otherwise recover energy
                else if (jumpControl.Energy != jumpControl.EnergyMax)
                {

                    RecoverEnergy();

                }

                // If skill is not in use or player is not pressing primary down
                if (!canUseSkill || !In.Primary)
                {

                    jumpControl.FallSpeed = originalFallSpeed;

                }

                // Ensure energy is at the correct values
                EnergyCheck();

            }

        }

        protected override void ExecuteSkill()
		{

            // Modify fall speed 
            jumpControl.FallSpeed = chickenModifiedFallSpeed;

            if (jumpControl.ChickenState == JumpingChickenControl.ChickenStates.Airborne)
            {

                // Lose energy over time
                jumpControl.Energy -= jumpControl.EnergyLossRate * Time.fixedDeltaTime;

                // If energy is less than or equal to 0, prevent the usage of skills
                if (jumpControl.Energy <= 0) canUseSkill = false;

            }

        }

	}

}
