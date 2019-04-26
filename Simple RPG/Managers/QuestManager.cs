using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Assets.Scripts.Interfaces;

namespace Assets.Scripts.Managers
{
    public class QuestManager
    {

        private List<IQuest> _Quests;
        public List<IQuest> Quests { get { return _Quests; } set { _Quests = value; } }

    }
}
