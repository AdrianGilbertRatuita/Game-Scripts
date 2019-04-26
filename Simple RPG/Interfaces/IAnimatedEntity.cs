using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.Interfaces
{
    public interface IAnimatedEntity
    {

        void Initialize();
        void Action_BasedOnState();
        void Animation_BasedOnMoveState();
        void PublicUpdate();

    }
}
