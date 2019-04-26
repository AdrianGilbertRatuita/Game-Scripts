using Assets.Scripts.Interfaces;
using Assets.Scripts.Objects.NPC.Enemies.Enemy;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.Managers
{
    public static class EnemyManager
    {

        public static IEnemy FindEnemyByName(string EnemyName)
        {

            switch(EnemyName)
            {

                case "Slime":
                    {

                        return new Slime();
                        break;
                    }
                default:
                    {

                        return null;
                        break;
                    }


            }

        }

    }
}
