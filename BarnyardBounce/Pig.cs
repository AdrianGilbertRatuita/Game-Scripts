using UnityEngine;
using System.Collections;

namespace VividVision.BarnyardBounce
{
	public class Pig : Animal
	{

		// What is the maxscale to grow into
		public float maxScale = 3;

		// Minimum scale based on the starting scale of the character
		private float minScale;

		// Use this for initialization
		void Start()
		{

			SetupReferences();

			// The assumption that the xyz scale will be uniform and will be the same throughout the game
			minScale = jumpControl.gameObject.transform.localScale.x;

		}

		// Update is called once per frame
		void FixedUpdate()
		{

            CheckSkillInput();
			RecoverEnergy();

		}

        protected override void CheckSkillInput()
        {

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

                    // Scale pig down
                    Vector3 currentScale = jumpControl.gameObject.transform.localScale;

                    this.gameObject.transform.localScale = Vector3.Lerp(currentScale, new Vector3(minScale, minScale, minScale), 0.01f);

                }

                // Ensure energy is at the correct values
                EnergyCheck();

            }

        }

        protected override void ExecuteSkill()
		{

            // Lose energy over time
            jumpControl.Energy -= 1.0f * jumpControl.EnergyLossRate;

            // Scale pig up
            Vector3 currentScale = jumpControl.gameObject.transform.localScale;

            // Change scale now
            this.gameObject.transform.localScale = Vector3.Lerp(currentScale, new Vector3(maxScale, maxScale, maxScale), 0.01f);

            // If energy is less than or equal to 0, prevent the usage of skills
            if (jumpControl.Energy <= 0) canUseSkill = false;

        }

	}

}
