using Assets.Scripts.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.Objects.Item
{
    public abstract class ItemBase : IItem
    {

        private string _Name;
        private bool _IsKeyItem;

        public string Name { get { return _Name; } private set { _Name = value; } }
        public bool IsKeyItem { get { return _IsKeyItem; } private set { _IsKeyItem = value; } }


    }
}
