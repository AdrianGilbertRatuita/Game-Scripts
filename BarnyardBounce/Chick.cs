using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace VividVision.BarnyardBounce
{

	public class Chick : Animal
	{

        // Energy Threshhold to allow flying again when energy is depleted
        public float flyAgainThreshold = 0.5f;

        // Flag to check if chick can fly up
        private bool canFlyUp;

		// Use this for initialization
		void Start()
		{

            SetupReferences();
            canFlyUp = true;

		}

		// Update is called once per frame
		void FixedUpdate()
		{

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

                    // Make sure to check if current state is FlyingUp
                    if (jumpControl.ChickenState == JumpingChickenControl.ChickenStates.FlyingUp)
                    {

                        jumpControl.StopFlying();

                    }

                }

                // Ensure energy is at the correct values
                EnergyCheck();

            }

        }

        protected override void ExecuteSkill()
        {

            // Lose energy over time
            jumpControl.Energy -= jumpControl.EnergyLossRate * Time.fixedDeltaTime;

            // Start flying up
            jumpControl.FlyUp();

            // If energy is less than or equal to 0, prevent the usage of skills
            if (jumpControl.Energy <= 0) canUseSkill = false;


        }
    }

}
