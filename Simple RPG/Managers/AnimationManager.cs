using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.Scripts.Managers
{
    public static class AnimationManager
    {

        public static bool AnimationCheck(string Animation, Animator ThisAnimator)
        {

            if (ThisAnimator.GetCurrentAnimatorStateInfo(0).IsName(Animation))
            {

                return true;

            }

            return false;
        }

    }
}
