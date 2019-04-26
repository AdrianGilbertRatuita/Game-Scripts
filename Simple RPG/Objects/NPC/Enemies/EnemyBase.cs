using Assets.Scripts.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Assets.Scripts.States;

namespace Assets.Scripts.Objects.Enemies
{
    public class EnemyBase : IEnemy
    {
        // 
        private int _ExpReward;
        private string _EntityName;
        private int _HP;
        private int _Level;
        private int _Attack;
        private int _GoldReward;
        private CharacterLivingState _EState;
        private MovementState _EMoveState;

        //
        public string EntityName { get { return _EntityName; } set { _EntityName = value; } }
        public int HP { get { return _HP; } set { _HP = value; } }
        public int Level { get { return _Level; } set { _Level = value; } }
        public int Attack { get { return _Attack; } set { _Attack = value; } }
        public int ExpReward { get { return _ExpReward; } set { _ExpReward = value; } }
        public int GoldReward { get { return _GoldReward; } set { _GoldReward = value; } }
        public CharacterLivingState EState { get { return _EState; } set { _EState = value; } }
        public MovementState EMoveState { get { return _EMoveState; } set { _EMoveState = value; } }

    }
}
