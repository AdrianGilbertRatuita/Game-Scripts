
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Assets.Scripts.States;
using Assets.Scripts.Objects.Enemies;

namespace Assets.Scripts.Objects.NPC.Enemies.Enemy
{
    public class EmptyEnemy : EnemyBase
    {

        public EmptyEnemy()
        {

            this.EntityName = "Empty";
            this.Attack = 0;
            this.ExpReward = 0;
            this.HP = 0;
            this.Level = 0;

        }

    }
}
