using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.Interfaces
{
    public interface IQuest
    {

        string Title { get; }
        string Details { get; }
        int GoldReward { get; }
        int ExpReward { get; }
        bool Complete { get; }
        string TriggerComplete();

    }

}
