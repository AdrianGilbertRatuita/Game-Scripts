
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Assets.Scripts.Interfaces;

namespace Assets.Scripts.Objects.Quest
{
    public abstract class QuestBase : IQuest
    {

        private string _Title;
        private string _Detail;
        private int _GoldReward;
        private int _ExpReward;
        private bool _Complete;

        public string Title { get { return _Title; } set { _Title = value; } }
        public string Details { get { return _Detail; } set { _Detail = value; } }
        public int GoldReward { get { return _GoldReward; } set { _GoldReward = value; } }
        public int ExpReward { get { return _ExpReward; } set { _ExpReward = value; } }
        public bool Complete { get { return _Complete; } set { _Complete = value; } }

        public QuestBase()
        {

            Title = "Quest Name";
            Details = "Quest Description";
            GoldReward = 0;
            ExpReward = 0;
            Complete = false;

        }

        public QuestBase(string T, string D, int G, int E)
        {

            Title = T;
            Details = D;
            GoldReward = G;
            ExpReward = E;
            Complete = false;

        }

        public string TriggerComplete()
        {
            Complete = true;
            return "Quest Complete!";
        }

    }

}
