using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.Scripts.Objects.Window
{
    public interface IWindow
    {

        string WindowName { get; set; }
        bool IsActive { get; set; }
        bool IsVisible { get; set; }
        GameObject WindowContainer { get; set; }
        GameObject WindowElements { get; set; }
        GameObject CornerContainer { get; set; }
        GameObject BarContainer { get; set; }
        GameObject Content { get; set; }
        Vector2 WindowSize { get; set; }
        Vector3 WindowLocation { get; set; }

    }

}
