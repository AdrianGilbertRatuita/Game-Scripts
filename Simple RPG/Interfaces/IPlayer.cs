using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.Interfaces
{
    public interface IPlayer : IEntity
    {

        int Gold { get; }
        int MaxHP { get; }
        int Experience { get; }

    }
}
