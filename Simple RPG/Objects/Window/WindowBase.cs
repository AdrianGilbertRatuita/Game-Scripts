using UnityEngine;
using System.Collections.Generic;
using Assets.Scripts.Objects.Window;
using Assets.Scripts.Managers;

public class WindowBase : IWindow
{

    //
    private string _WindowName;
    private bool _IsActive;
    private bool _IsVisible;
    private GameObject _WindowContainer;
    private GameObject _WindowElements;
    private GameObject _CornerContainer;
    private GameObject _BarContainer;
    private GameObject _Content;
    private Vector2 _WindowSize;
    private Vector3 _WindowLocation;

    //
    public string WindowName { get { return _WindowName; } set { _WindowName = value; } }
    public bool IsActive { get { return _IsActive; } set { _IsActive = value; } }
    public bool IsVisible { get { return _IsVisible; } set { _IsVisible = value; } }
    public GameObject WindowContainer { get { return _WindowContainer; } set { _WindowContainer = value; } }
    public GameObject WindowElements { get { return _WindowElements; } set { _WindowElements = value; } }
    public GameObject CornerContainer { get { return _CornerContainer; } set { _CornerContainer = value; } }
    public GameObject BarContainer { get { return _BarContainer; } set { _BarContainer = value; } }
    public GameObject Content { get { return _Content; } set { _Content = value; } }
    public Vector2 WindowSize { get { return _WindowSize; } set { _WindowSize = value; } }
    public Vector3 WindowLocation { get { return _WindowLocation; } set { _WindowLocation = value; } }

    //
    public WindowBase()
    {

        Initialize();

    }
    public void Initialize()
    {

        if (WindowManager.Windows == null) { WindowManager.Windows = new List<IWindow>(); }

    }
    public void RefreshContent(GameObject NewContent)
    {

        Object.Destroy(Content);
        Content = NewContent;
        Content.name = "Content";
        Content.transform.position = WindowContainer.transform.position;
        Content.transform.parent = WindowContainer.transform;

    }
    public void CreateWindow(string _WindowName, GameObject PassedContent, Vector2 _WindowSize, Vector3 _NewWindowLocation, bool ShowNow, GameObject Player)
    {

        // Window Creation Flow
        /*

            -> Set Window Size
            -> Create Containers (Window, Elements, Corners, Bar)
            -> Parent Containers to Respective Objects
                - Window Container - Main Parent
                - (Window - Parent) Elements - Corners and Bars Parent
                - (Window - Parent) Content - Passed Content from Paramenters
            -> Instantiate and Configure Prefabs for Corners, Bars and Window Fill
            -> Set Window Location
            -> Check to Hide Window after Creation
            -> Add to Window List


        */

        //
        SetWindowSize(_WindowSize);

        //
        WindowContainer = new GameObject
        {
            name = _WindowName,
            tag = "Window"
        };
        WindowName = _WindowName;

        //
        WindowElements = new GameObject
        {
            name = "WindowElements",
        };
        WindowElements.transform.parent = WindowContainer.transform;

        //
        CornerContainer = new GameObject
        {
            name = "CornerContainer"
        };
        CornerContainer.transform.parent = WindowElements.transform;

        //
        BarContainer = new GameObject
        {
            name = "BarContainer"
        };
        BarContainer.transform.parent = WindowElements.transform;

        //
        RefreshContent(PassedContent);

        GameObject LeftBar;
        GameObject RightBar;
        GameObject UpperBar;
        GameObject LowerBar;
        GameObject UpperLeftCorner;
        GameObject UpperRightCorner;
        GameObject LowerLeftCorner;
        GameObject LowerRightCorner;
        GameObject WindowFill;

        //       
        UpperLeftCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/UpperLeftCorner")) as GameObject;
        UpperLeftCorner.name = "UpperLeftCorner";
        UpperLeftCorner.transform.position = new Vector3(WindowSize.x * -1, WindowSize.y * 1, 0);
        UpperLeftCorner.transform.parent = CornerContainer.transform;

        //       
        UpperRightCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/UpperRightCorner")) as GameObject;
        UpperRightCorner.name = "UpperRightCorner";
        UpperRightCorner.transform.position = new Vector3(WindowSize.x * 1, WindowSize.y * 1, 0);
        UpperRightCorner.transform.parent = CornerContainer.transform;

        //       
        LowerLeftCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LowerLeftCorner")) as GameObject;
        LowerLeftCorner.name = "LowerLeftCorner";
        LowerLeftCorner.transform.position = new Vector3(WindowSize.x * -1, WindowSize.y * -1, 0);
        LowerLeftCorner.transform.parent = CornerContainer.transform;

        //       
        LowerRightCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LowerRightCorner")) as GameObject;
        LowerRightCorner.name = "LowerRightCorner";
        LowerRightCorner.transform.position = new Vector3(WindowSize.x * 1, WindowSize.y * -1, 0);
        LowerRightCorner.transform.parent = CornerContainer.transform;

        //
        WindowFill = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Regular02")) as GameObject;
        WindowFill.name = "WindowFill";
        WindowFill.transform.position = new Vector3(0, 0, 0);
        WindowFill.transform.localScale = new Vector3((WindowSize.x * 2) + 0.7f, (WindowSize.y * 2) + 0.7f, 0);
        WindowFill.transform.parent = WindowElements.transform;

        //
        LeftBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LeftBar")) as GameObject;
        LeftBar.name = "LeftBar";
        LeftBar.transform.position = new Vector3(WindowSize.x * -1, 0, 0);
        LeftBar.transform.localScale = new Vector3(1, WindowSize.y * 2, 0);
        LeftBar.transform.parent = BarContainer.transform;

        //
        RightBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/RightBar")) as GameObject;
        RightBar.name = "RightBar";
        RightBar.transform.position = new Vector3(WindowSize.x * 1, 0, 0);
        RightBar.transform.localScale = new Vector3(1, WindowSize.y * 2, 0);
        RightBar.transform.parent = BarContainer.transform;

        //
        UpperBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/UpperBar")) as GameObject;
        UpperBar.name = "UpperBar";
        UpperBar.transform.position = new Vector3(0, WindowSize.y * 1, 0);
        UpperBar.transform.localScale = new Vector3(WindowSize.x * 2, 1, 0);
        UpperBar.transform.parent = BarContainer.transform;

        //
        LowerBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LowerBar")) as GameObject;
        LowerBar.name = "LowerBar";
        LowerBar.transform.position = new Vector3(0, WindowSize.y * -1, 0);
        LowerBar.transform.localScale = new Vector3(WindowSize.x * 2, 1, 0);
        LowerBar.transform.parent = BarContainer.transform;

        //
        this.WindowLocation = _NewWindowLocation;
        WindowContainer.transform.position = _NewWindowLocation;
        WindowContainer.transform.parent = Player.transform;

        //
        if (!ShowNow) { HideWindow(); } else { ActivateWindow(); }

        WindowManager.Windows.Add(this);

    }
    public void CreateWindow(string _WindowName, Vector2 _WindowSize, Vector3 _NewWindowLocation, bool ShowNow, GameObject Player)
    {

        // Window Creation Flow
        /*

            -> Set Window Size
            -> Create Containers (Window, Elements, Corners, Bar)
            -> Parent Containers to Respective Objects
                - Window Container - Main Parent
                - (Window - Parent) Elements - Corners and Bars Parent
                - (Window - Parent) Content - Passed Content from Paramenters
            -> Instantiate and Configure Prefabs for Corners, Bars and Window Fill
            -> Set Window Location
            -> Check to Hide Window after Creation
            -> Add to Window List


        */

        //
        SetWindowSize(_WindowSize);

        //
        WindowContainer = new GameObject
        {
            name = _WindowName,
            tag = "Window"
        };
        WindowName = _WindowName;

        //
        WindowElements = new GameObject
        {
            name = "WindowElements",
        };
        WindowElements.transform.parent = WindowContainer.transform;

        //
        CornerContainer = new GameObject
        {
            name = "CornerContainer"
        };
        CornerContainer.transform.parent = WindowElements.transform;

        //
        BarContainer = new GameObject
        {
            name = "BarContainer"
        };
        BarContainer.transform.parent = WindowElements.transform;

        GameObject LeftBar;
        GameObject RightBar;
        GameObject UpperBar;
        GameObject LowerBar;
        GameObject UpperLeftCorner;
        GameObject UpperRightCorner;
        GameObject LowerLeftCorner;
        GameObject LowerRightCorner;
        GameObject WindowFill;

        //       
        UpperLeftCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/UpperLeftCorner")) as GameObject;
        UpperLeftCorner.name = "UpperLeftCorner";
        UpperLeftCorner.transform.position = new Vector3(WindowSize.x * -1, WindowSize.y * 1, 0);
        UpperLeftCorner.transform.parent = CornerContainer.transform;

        //       
        UpperRightCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/UpperRightCorner")) as GameObject;
        UpperRightCorner.name = "UpperRightCorner";
        UpperRightCorner.transform.position = new Vector3(WindowSize.x * 1, WindowSize.y * 1, 0);
        UpperRightCorner.transform.parent = CornerContainer.transform;

        //       
        LowerLeftCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LowerLeftCorner")) as GameObject;
        LowerLeftCorner.name = "LowerLeftCorner";
        LowerLeftCorner.transform.position = new Vector3(WindowSize.x * -1, WindowSize.y * -1, 0);
        LowerLeftCorner.transform.parent = CornerContainer.transform;

        //       
        LowerRightCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LowerRightCorner")) as GameObject;
        LowerRightCorner.name = "LowerRightCorner";
        LowerRightCorner.transform.position = new Vector3(WindowSize.x * 1, WindowSize.y * -1, 0);
        LowerRightCorner.transform.parent = CornerContainer.transform;

        //
        WindowFill = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Regular02")) as GameObject;
        WindowFill.name = "WindowFill";
        WindowFill.transform.position = new Vector3(0, 0, 0);
        WindowFill.transform.localScale = new Vector3((WindowSize.x * 2) + 0.7f, (WindowSize.y * 2) + 0.7f, 0);
        WindowFill.transform.parent = WindowElements.transform;

        //
        LeftBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LeftBar")) as GameObject;
        LeftBar.name = "LeftBar";
        LeftBar.transform.position = new Vector3(WindowSize.x * -1, 0, 0);
        LeftBar.transform.localScale = new Vector3(1, WindowSize.y * 2, 0);
        LeftBar.transform.parent = BarContainer.transform;

        //
        RightBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/RightBar")) as GameObject;
        RightBar.name = "RightBar";
        RightBar.transform.position = new Vector3(WindowSize.x * 1, 0, 0);
        RightBar.transform.localScale = new Vector3(1, WindowSize.y * 2, 0);
        RightBar.transform.parent = BarContainer.transform;

        //
        UpperBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/UpperBar")) as GameObject;
        UpperBar.name = "UpperBar";
        UpperBar.transform.position = new Vector3(0, WindowSize.y * 1, 0);
        UpperBar.transform.localScale = new Vector3(WindowSize.x * 2, 1, 0);
        UpperBar.transform.parent = BarContainer.transform;

        //
        LowerBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LowerBar")) as GameObject;
        LowerBar.name = "LowerBar";
        LowerBar.transform.position = new Vector3(0, WindowSize.y * -1, 0);
        LowerBar.transform.localScale = new Vector3(WindowSize.x * 2, 1, 0);
        LowerBar.transform.parent = BarContainer.transform;

        //
        this.WindowLocation = _NewWindowLocation;
        WindowContainer.transform.position = _NewWindowLocation;
        WindowContainer.transform.parent = Player.transform;

        //
        if (!ShowNow) { HideWindow(); } else { ShowWindow(); }

        WindowManager.Windows.Add(this);

    }
    public void CreateWindow(string _WindowName, Vector2 _WindowSize, bool ShowNow)
    {

        // Window Creation Flow
        /*

            -> Set Window Size
            -> Create Containers (Window, Elements, Corners, Bar)
            -> Parent Containers to Respective Objects
                - Window Container - Main Parent
                - (Window - Parent) Elements - Corners and Bars Parent
                - (Window - Parent) Content - Passed Content from Paramenters
            -> Instantiate and Configure Prefabs for Corners, Bars and Window Fill
            -> Set Window Location
            -> Check to Hide Window after Creation
            -> Add to Window List


        */

        //
        SetWindowSize(_WindowSize);

        //
        WindowContainer = new GameObject
        {
            name = _WindowName,
            tag = "Window"
        };
        WindowName = _WindowName;

        //
        WindowElements = new GameObject
        {
            name = "WindowElements",
        };
        WindowElements.transform.parent = WindowContainer.transform;

        //
        CornerContainer = new GameObject
        {
            name = "CornerContainer"
        };
        CornerContainer.transform.parent = WindowElements.transform;

        //
        BarContainer = new GameObject
        {
            name = "BarContainer"
        };
        BarContainer.transform.parent = WindowElements.transform;

        GameObject LeftBar;
        GameObject RightBar;
        GameObject UpperBar;
        GameObject LowerBar;
        GameObject UpperLeftCorner;
        GameObject UpperRightCorner;
        GameObject LowerLeftCorner;
        GameObject LowerRightCorner;
        GameObject WindowFill;

        //       
        UpperLeftCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/UpperLeftCorner")) as GameObject;
        UpperLeftCorner.name = "UpperLeftCorner";
        UpperLeftCorner.transform.position = new Vector3(WindowSize.x * -1, WindowSize.y * 1, 0);
        UpperLeftCorner.transform.parent = CornerContainer.transform;

        //       
        UpperRightCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/UpperRightCorner")) as GameObject;
        UpperRightCorner.name = "UpperRightCorner";
        UpperRightCorner.transform.position = new Vector3(WindowSize.x * 1, WindowSize.y * 1, 0);
        UpperRightCorner.transform.parent = CornerContainer.transform;

        //       
        LowerLeftCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LowerLeftCorner")) as GameObject;
        LowerLeftCorner.name = "LowerLeftCorner";
        LowerLeftCorner.transform.position = new Vector3(WindowSize.x * -1, WindowSize.y * -1, 0);
        LowerLeftCorner.transform.parent = CornerContainer.transform;

        //       
        LowerRightCorner = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LowerRightCorner")) as GameObject;
        LowerRightCorner.name = "LowerRightCorner";
        LowerRightCorner.transform.position = new Vector3(WindowSize.x * 1, WindowSize.y * -1, 0);
        LowerRightCorner.transform.parent = CornerContainer.transform;

        //
        WindowFill = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Regular02")) as GameObject;
        WindowFill.name = "WindowFill";
        WindowFill.transform.position = new Vector3(0, 0, 0);
        WindowFill.transform.localScale = new Vector3((WindowSize.x * 2) + 0.7f, (WindowSize.y * 2) + 0.7f, 0);
        WindowFill.transform.parent = WindowElements.transform;

        //
        LeftBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LeftBar")) as GameObject;
        LeftBar.name = "LeftBar";
        LeftBar.transform.position = new Vector3(WindowSize.x * -1, 0, 0);
        LeftBar.transform.localScale = new Vector3(1, WindowSize.y * 2, 0);
        LeftBar.transform.parent = BarContainer.transform;

        //
        RightBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/RightBar")) as GameObject;
        RightBar.name = "RightBar";
        RightBar.transform.position = new Vector3(WindowSize.x * 1, 0, 0);
        RightBar.transform.localScale = new Vector3(1, WindowSize.y * 2, 0);
        RightBar.transform.parent = BarContainer.transform;

        //
        UpperBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/UpperBar")) as GameObject;
        UpperBar.name = "UpperBar";
        UpperBar.transform.position = new Vector3(0, WindowSize.y * 1, 0);
        UpperBar.transform.localScale = new Vector3(WindowSize.x * 2, 1, 0);
        UpperBar.transform.parent = BarContainer.transform;

        //
        LowerBar = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/LowerBar")) as GameObject;
        LowerBar.name = "LowerBar";
        LowerBar.transform.position = new Vector3(0, WindowSize.y * -1, 0);
        LowerBar.transform.localScale = new Vector3(WindowSize.x * 2, 1, 0);
        LowerBar.transform.parent = BarContainer.transform;

        //
        this.WindowLocation = Vector3.zero;
        WindowContainer.transform.position = Vector3.zero;

        //
        if (!ShowNow) { HideWindow(); } else { ShowWindow(); }

        WindowManager.Windows.Add(this);

    }
    public void HideWindow()
    {

        this.WindowContainer.transform.position = Vector3.one * -1000;
        this.IsVisible = false;
        this.IsActive = false;

    }
    public void ActivateWindow()
    {

        WindowManager.DeactivateWindows();
        IsActive = true;

    }
    public void ShowWindow()
    {
      
        IsVisible = true;
        ActivateWindow();
        WindowContainer.transform.position = GameObject.FindGameObjectWithTag("Player").transform.position;
        WindowContainer.transform.parent = GameObject.FindGameObjectWithTag("Player").transform;
        WindowContainer.transform.position = Vector3.zero;

    }
    public void ShowWindow(Vector3 NewLocation)
    {
     
        IsVisible = true;
        ActivateWindow();
        WindowContainer.transform.position = GameObject.FindGameObjectWithTag("Player").transform.position;
        WindowContainer.transform.parent = GameObject.FindGameObjectWithTag("Player").transform;
        WindowContainer.transform.position += NewLocation;
    }
    public bool ReturnHandler()
    {
        
        if (Input.GetKeyDown(KeyCode.Return) && IsActive && IsVisible)
        {

            return true;

        }

        return false;

    }
    private void ResetWindowSize()
    {

        WindowSize = new Vector2(2, 2);

    }
    private void SetWindowSize(Vector2 _WindowSize)
    {

        WindowSize = _WindowSize;

    }
    public void CorrectPosition()
    {

        WindowContainer.transform.position = WindowLocation;

    }
    public void CorrectPositionRelativeToPlayer()
    {

        if (WindowContainer.transform.parent != GameObject.FindGameObjectWithTag("Playyer").transform)
        {

            WindowContainer.transform.parent = GameObject.FindGameObjectWithTag("Playyer").transform;
            WindowContainer.transform.position = WindowLocation;

        }


    }

}


