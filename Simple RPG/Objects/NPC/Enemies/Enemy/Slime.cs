using Assets.Scripts.Objects.Enemies;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.Objects.NPC.Enemies.Enemy
{
    public class Slime : EnemyBase
    {
        public Slime()
        {

            this.EntityName = "Slime";
            this.Attack = 1;
            this.ExpReward = 3;
            this.GoldReward = 1;
            this.HP = 5;
            this.Level = 1;

        }

    }

}
