using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.Objects.Quest
{
    public class DummyQuest : QuestBase
    {

        public DummyQuest(string T, string D, int G, int E) :base(T, D, G, E)
        {

            this.Title = T;
            this.Details = D;
            this.GoldReward = G;
            this.ExpReward = E;


        }


    }

}
