using UnityEngine;
using System.Collections;

namespace VividVision.BarnyardBounce
{
	public class Cow : Animal
	{

        [SerializeField]
        private bool coolingDown = false;

        private float cooldownTime = 0;

        [SerializeField]
        private float doubleJumpCooldown = 5;

        // Energy cost for each moo
        public float mooCost = 0.25f;

        // Reflect and save original jump height
        private float originalJumpHeight;

        // Max height for moo
        [SerializeField]
        private float modifiedJumpHeight = 7;

        // Moo Sound
        public AudioClip mooSound;

        // Use this for initialization
        void Start()
		{

            originalJumpHeight = jumpHeight;

            SetupReferences();

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
                    && In.PrimaryDown
                    && !coolingDown
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
                if (!canUseSkill || !In.PrimaryDown)
                {

                    //
                    jumpHeight = originalJumpHeight;

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

            // switch current jumpHeight to maxJumpHeight
            jumpHeight = modifiedJumpHeight;

            //// jump up with new maxJumpHeight
            //jumpControl.Jump();
            jumpControl.DoubleJump();

            // if sound is not null Play
            if (mooSound) AudioManager.PlaySound(mooSound, this.transform.position);

            // Subtract fixed moo cost to current energy
            jumpControl.Energy -= mooCost;

            // If energy is less than or equal to 0, prevent the usage of skills
            if (jumpControl.Energy <= 0) canUseSkill = false;


        }

    }

}
