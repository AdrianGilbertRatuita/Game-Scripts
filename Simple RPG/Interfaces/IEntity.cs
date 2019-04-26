using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.Interfaces
{
    public interface IEntity
    {

        string EntityName { get; set; }
        int HP { get; set; }
        int Level { get; set; }
        int Attack { get; set; }

    }
}
