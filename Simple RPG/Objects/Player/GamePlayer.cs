
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Assets.Scripts.Interfaces;
using Assets.Scripts.States;
using UnityEngine;

namespace Assets.Scripts.Objects.Player
{
    public class GamePlayer : IPlayer
    {

        private int _Gold;
        private int _MaxHP;
        private string _EntityName;
        private int _HP;
        private int _Level;
        private int _Attack;
        private int _Exp;
        private string _SceneName;
        private Vector3 _SavedLocation;
        private MovementState _MovementStatus;
        private DirectionState _CurrentDirection;
        private CharacterLivingState _PlayerLivingStatus;
        private List<IQuest> _CurrentQuests;

        //
        public int Gold { get { return _Gold; } set { _Gold = value; } }
        public int HP { get { return _HP; } set { _HP = value; } }
        public int MaxHP { get { return _MaxHP; } set { _MaxHP = value; } }
        public string EntityName { get { return _EntityName; } set { _EntityName = value; } }
        public int Level { get { return _Level; } set { _Level = value; } }
        public int Attack { get { return _Attack; } set { _Attack = value; } }
        public int Experience { get { return _Exp; } set { _Exp = value; } }
        public string SceneName { get { return _SceneName; } set { _SceneName = value; } }
        public Vector3 SavedLocation { get { return _SavedLocation; } set { _SavedLocation = value; } }
        public MovementState MovementStatus { get { return _MovementStatus; } set { _MovementStatus = value; } }
        public DirectionState CurrentDirection { get { return _CurrentDirection; } set { _CurrentDirection = value; } }
        private CharacterLivingState PlayerLivingStatus { get { return _PlayerLivingStatus; } set { _PlayerLivingStatus = value; } }
        public List<IQuest> CurrentQuests { get { return _CurrentQuests; } set { _CurrentQuests = value; } }

        public GamePlayer()
        {

            Gold = 0;
            HP = 10;
            MaxHP = 10;
            EntityName = "Player";
            Level = 1;
            Attack = 5;
            Experience = 0;
            MovementStatus = MovementState.IDLE;
            CurrentDirection = DirectionState.DOWN;
            PlayerLivingStatus = CharacterLivingState.ALIVE;
            SceneName = "Game";
            SavedLocation = new Vector3(0, 0);
            CurrentQuests = new List<IQuest>();

        }
        public GamePlayer(string DName)
        {

            Gold = 0;
            HP = 10;
            MaxHP = 10;
            EntityName = DName;
            Level = 1;
            Attack = 5;
            Experience = 0;
            MovementStatus = MovementState.IDLE;
            CurrentDirection = DirectionState.DOWN;
            PlayerLivingStatus = CharacterLivingState.ALIVE;
            SceneName = "Game";
            SavedLocation = new Vector3(0, 0);
            CurrentQuests = new List<IQuest>();

        }
        public GamePlayer(int DGold, int DHP, int DMaxHP, string DName, int DLevel, int DAttack, int DExperience, List<IQuest> DQuests)
        {

            Gold = DGold;
            HP = DHP;
            MaxHP = DMaxHP;
            EntityName = DName;
            Level = DLevel;
            Attack = DAttack;
            Experience = DExperience;
            MovementStatus = MovementState.IDLE;
            CurrentDirection = DirectionState.DOWN;
            PlayerLivingStatus = CharacterLivingState.ALIVE;
            CurrentQuests = DQuests;

        }

    }

    [Serializable]
    public class PlayerData
    {

        public int GOLD;
        public int HP;
        public int MAXHP;
        public int ATTACK;
        public int LEVEL;
        public int EXPERIENCE;
        public string NAME;
        public string SCENENAME;
        public float XLocation;
        public float YLocation;
        public float ZLocation;
        public MovementState MOVE;
        public DirectionState DIR;
        public List<IQuest> QUEST;

        public PlayerData(GamePlayer SavePlayer)
        {

            GOLD = SavePlayer.Gold;
            HP = SavePlayer.HP;
            MAXHP = SavePlayer.MaxHP;
            ATTACK = SavePlayer.Attack;
            LEVEL = SavePlayer.Level;
            EXPERIENCE = SavePlayer.Experience;
            NAME = SavePlayer.EntityName;
            SCENENAME = SavePlayer.SceneName;
            XLocation = SavePlayer.SavedLocation.x;
            YLocation = SavePlayer.SavedLocation.y;
            ZLocation = SavePlayer.SavedLocation.z;
            MOVE = MovementState.IDLE;
            DIR = DirectionState.DOWN;
            QUEST = new List<IQuest>();

        }
        public GamePlayer GetPlayerData()
        {

            GamePlayer LoadedPlayerData;
            LoadedPlayerData = new GamePlayer();
            LoadedPlayerData.Gold = this.GOLD;
            LoadedPlayerData.HP = this.HP;
            LoadedPlayerData.MaxHP = this.MAXHP;
            LoadedPlayerData.Attack = this.ATTACK;
            LoadedPlayerData.Level = this.LEVEL;
            LoadedPlayerData.Experience = this.EXPERIENCE;
            LoadedPlayerData.EntityName = this.NAME;
            LoadedPlayerData.SceneName = this.SCENENAME;
            LoadedPlayerData.SavedLocation = new Vector3(XLocation, YLocation, ZLocation);
            LoadedPlayerData.MovementStatus = MovementState.IDLE;
            LoadedPlayerData.CurrentDirection = DirectionState.DOWN;
            LoadedPlayerData.CurrentQuests = new List<IQuest>();

            return LoadedPlayerData;

        }

    }

}
