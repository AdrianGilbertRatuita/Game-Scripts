using Assets.Scripts.States;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.Interfaces
{
    public interface IEnemy : IEntity
    {

        int ExpReward { get; }
        int GoldReward { get; }
        CharacterLivingState EState { get; set; }
        MovementState EMoveState { get; set; }

    }
}
