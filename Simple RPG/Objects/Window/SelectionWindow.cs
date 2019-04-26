using Assets.Scripts.Managers;
using System.Collections.Generic;
using UnityEngine;

namespace Assets.Scripts.Objects.Window
{

    public class SelectionWindow
    {
        //
        public bool InputisHere;
        public bool NonEscapable;
        //
        private float TopPadding;
        private int _SelectionIndex;

        //
        private bool _Reading;
        private string[] _SelectionString;
        private WindowBase _ThisWindow;
        private GameObject _Content;
        private GameObject _SelectionPrompt;
        private List<GameObject> _Selections;
        private Vector2 _SelectionSize;
        private Vector3 _SelectionLocation;

        //
        public int SelectionIndex { get { return _SelectionIndex; } private set { _SelectionIndex = value; } }
        public bool Reading { get { return _Reading; } private set { _Reading = value; } }
        public string[] SelectionString { get { return _SelectionString; } private set { _SelectionString = value; } }
        public WindowBase ThisWindow { get { return _ThisWindow; } private set { _ThisWindow = value; } }
        public GameObject SelectionPrompt { get { return _SelectionPrompt; } private set { _SelectionPrompt = value; } }
        public GameObject Content { get { return _Content; } private set { _Content = value; } }
        public List<GameObject> Selections { get { return _Selections; } private set { _Selections = value; } }
        public Vector2 SelectionSize { get { return _SelectionSize; } private set { _SelectionSize = value; } }
        public Vector3 SelectionLocation { get { return _SelectionLocation; } private set { _SelectionLocation = value; } }
        //
        public SelectionWindow(GameObject ThisPlayer, Vector2 Size, Vector3 Location)
        {

            SelectionSize = Size;
            NonEscapable = false;
            TopPadding = -0.50f;           
            ThisWindow = new WindowBase();
            Selections = new List<GameObject>();
            SelectionLocation = Location;
            CreateWindow(ThisPlayer);
            
        }
        public SelectionWindow(GameObject ThisPlayer, Vector2 Size)
        {

            SelectionSize = Size;
            NonEscapable = false;
            TopPadding = -0.50f;
            ThisWindow = new WindowBase();
            Selections = new List<GameObject>();
            SelectionLocation = Vector3.zero;
            CreateWindow(ThisPlayer);

        }
        public SelectionWindow(Vector2 Size)
        {

            SelectionSize = Size;
            NonEscapable = false;
            TopPadding = -0.50f;
            ThisWindow = new WindowBase();
            Selections = new List<GameObject>();
            SelectionLocation = Vector3.zero;
            CreateWindow();

        }
        public void ClearContent()
        {

            if (Content != null) { Object.Destroy(Content); }
            Content = new GameObject { name = "Content" };
            Content.transform.position = ThisWindow.WindowContainer.transform.position;
            Content.transform.parent = ThisWindow.WindowContainer.transform;

        }
        public void ShowWindow() { ThisWindow.ShowWindow(SelectionLocation); }
        public void HideWindow()
        {
            Reading = false;
            ThisWindow.HideWindow();
        }
        public void NewSelection(string[] Items, PlayerControl Player, GameObject ThisPlayer, bool Escapable)
        {

            NonEscapable = Escapable;
            Object.Destroy(ThisWindow.WindowContainer);
            CreateWindow(ThisPlayer);
            SelectionIndex = 1;
            Selections.Clear();
            SelectionString = Items;
            Player.DoShomething();
            Reading = true;
            ClearContent();
            CreateItems();
            RefreshWindow();        
            ShowWindow();

        }
        public void NewSelection(string[] Items, bool Escapable)
        {

            NonEscapable = Escapable;
            Object.Destroy(ThisWindow.WindowContainer);
            CreateWindow();
            SelectionIndex = 1;
            Selections.Clear();
            SelectionString = Items;
            Reading = true;
            ClearContent();
            CreateItems();
            RefreshWindow();
            ShowWindow();

        }
        public bool ReadThrough()
        {

            if (Reading)
            {

                return true;

            }

            return false;

        }
        public int Read()
        {

            InputisHere = true;
            if (ThisWindow.ReturnHandler() && Reading)
            {

                Reading = false;
                ClearContent();
                HideWindow();
                return SelectionIndex;

            }
            else if (Input.GetKeyDown(KeyCode.Escape) && InputisHere && !NonEscapable)
            {

                Reading = false;
                ClearContent();
                HideWindow();
                return 0;

            }
            else
            {

                if (Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.UpArrow))
                {

                    if (SelectionIndex - 1 >= 1) { SelectionIndex--; SelectionPrompt.transform.position += new Vector3(0, 1, 0); }
                    else if (SelectionIndex - 1 < 1) { SelectionIndex = Selections.Count; SelectionPrompt.transform.position += new Vector3(0, (Selections.Count * -1) + 1, 0); }

                }

                if (Input.GetKeyDown(KeyCode.S) || Input.GetKeyDown(KeyCode.DownArrow))
                {

                    if (SelectionIndex + 1 <= Selections.Count) { SelectionIndex++; SelectionPrompt.transform.position += new Vector3(0, -1, 0); }
                    else if (SelectionIndex + 1 > Selections.Count) { SelectionIndex = 1; SelectionPrompt.transform.position += new Vector3(0, (Selections.Count * 1) - 1, 0); }

                }

            }

            return 0;

        }
        public int Read(PlayerControl Player)
        {

            InputisHere = true;
            if (ThisWindow.ReturnHandler() && Reading)
            {

                Reading = false;
                ClearContent();
                HideWindow();
                Player.NotDoShomething();
                return SelectionIndex;

            }
            else if (Input.GetKeyDown(KeyCode.Escape) && InputisHere && !NonEscapable)
            {

                Reading = false;
                ClearContent();
                HideWindow();
                Player.NotDoShomething();
                return 0;

            }
            else
            {
                Player.DoShomething();
                if (Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.UpArrow))
                {

                    if (SelectionIndex - 1 >= 1) { SelectionIndex--; SelectionPrompt.transform.position += new Vector3(0, 1, 0); }
                    else if (SelectionIndex - 1 < 1) { SelectionIndex = Selections.Count; SelectionPrompt.transform.position += new Vector3(0, (Selections.Count * -1) + 1, 0); }

                }

                if (Input.GetKeyDown(KeyCode.S) || Input.GetKeyDown(KeyCode.DownArrow))
                {

                    if (SelectionIndex + 1 <= Selections.Count) { SelectionIndex++; SelectionPrompt.transform.position += new Vector3(0, -1, 0); }
                    else if (SelectionIndex + 1 > Selections.Count) { SelectionIndex = 1; SelectionPrompt.transform.position += new Vector3(0, (Selections.Count * 1) - 1, 0); }

                }

            }

            return 0;

        }
        public int ReadNoEscape()
        {

            if (ThisWindow.ReturnHandler() && Reading)
            {

                Reading = false;
                ClearContent();
                HideWindow();
                return SelectionIndex;

            }
            else
            {

                if (Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.UpArrow))
                {

                    if (SelectionIndex - 1 >= 1) { SelectionIndex--; SelectionPrompt.transform.position += new Vector3(0, 1, 0); }
                    else if (SelectionIndex - 1 < 1) { SelectionIndex = Selections.Count; SelectionPrompt.transform.position += new Vector3(0, (Selections.Count * -1) + 1, 0); }

                }

                if (Input.GetKeyDown(KeyCode.S) || Input.GetKeyDown(KeyCode.DownArrow))
                {

                    if (SelectionIndex + 1 <= Selections.Count) { SelectionIndex++; SelectionPrompt.transform.position += new Vector3(0, -1, 0); }
                    else if (SelectionIndex + 1 > Selections.Count) { SelectionIndex = 1; SelectionPrompt.transform.position += new Vector3(0, (Selections.Count * 1) - 1, 0); }

                }

            }

            return 0;

        }
        public void RefreshWindow()
        {

            ThisWindow.RefreshContent(Content);

        }
        public void CreateWindow(GameObject ThisPlayer)
        {

            ThisWindow.CreateWindow("Selection", SelectionSize, SelectionLocation, false, ThisPlayer);

            Content = new GameObject();
            Content.name = "Content";
            Content.transform.position = ThisWindow.WindowContainer.transform.position;
            Content.transform.parent = ThisWindow.WindowContainer.transform;          

            SelectionPrompt = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/SelectorCursor")) as GameObject;
            SelectionPrompt.name = "SelectionCursor";
            SelectionPrompt.transform.position = ThisWindow.WindowContainer.transform.position;
            SelectionPrompt.transform.position += new Vector3(((ThisWindow.WindowSize.x * -1) + 1 * 0.40f), (ThisWindow.WindowSize.y) + TopPadding);
            SelectionPrompt.transform.parent = ThisWindow.WindowContainer.transform;

            GameObject SelectionBack;

            for (int i = 0; i < (ThisWindow.WindowSize.x * 2) - 1; i++)
            {
                SelectionBack = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/SelectionBack")) as GameObject;
                SelectionBack.name = "SelectionBack";
                SelectionBack.transform.position = SelectionPrompt.transform.position;
                SelectionBack.transform.position += new Vector3(i + 0.80f, 0, 0);
                SelectionBack.transform.parent = SelectionPrompt.transform;

            }
            
        }
        public void CreateWindow()
        {

            ThisWindow.CreateWindow("Selection", SelectionSize, false);

            Content = new GameObject();
            Content.name = "Content";
            Content.transform.position = ThisWindow.WindowContainer.transform.position;
            Content.transform.parent = ThisWindow.WindowContainer.transform;

            SelectionPrompt = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/SelectorCursor")) as GameObject;
            SelectionPrompt.name = "SelectionCursor";
            SelectionPrompt.transform.position = ThisWindow.WindowContainer.transform.position;
            SelectionPrompt.transform.position += new Vector3(((ThisWindow.WindowSize.x * -1) + 1 * 0.40f), (ThisWindow.WindowSize.y) + TopPadding);
            SelectionPrompt.transform.parent = ThisWindow.WindowContainer.transform;

            GameObject SelectionBack;

            for (int i = 0; i < (ThisWindow.WindowSize.x * 2) - 1; i++)
            {
                SelectionBack = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/SelectionBack")) as GameObject;
                SelectionBack.name = "SelectionBack";
                SelectionBack.transform.position = SelectionPrompt.transform.position;
                SelectionBack.transform.position += new Vector3(i + 0.80f, 0, 0);
                SelectionBack.transform.parent = SelectionPrompt.transform;

            }

        }
        public void CreateItems()
        {

            GameObject NewItem;
            GameObject ItemCharacters;

            for (int i = 0; i < SelectionString.Length; i++)
            {

                NewItem = new GameObject();
                NewItem.name = SelectionString[i];
                for (int j = 0; j < SelectionString[i].Length; j++)
                {

                    ItemCharacters = WindowManager.Letter(SelectionString[i][j]);
                    ItemCharacters.name = SelectionString[i][j].ToString();
                    ItemCharacters.transform.position += new Vector3(((ThisWindow.WindowSize.x * -1) + j * 0.40f) + 1, (ThisWindow.WindowSize.y - i) + TopPadding);
                    ItemCharacters.transform.parent = NewItem.transform;

                }
                NewItem.transform.position = Content.transform.position;
                NewItem.transform.parent = Content.transform;
                Selections.Add(NewItem);

            }

        }

    }

}
