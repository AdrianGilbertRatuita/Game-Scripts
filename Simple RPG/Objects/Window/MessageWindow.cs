
using Assets.Scripts.Managers;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Assets.Scripts.Objects.Window
{
    public class MessageWindow
    {
        //
        private bool CanEscape;
        private int LineCount;
        private int RemainingCharactersCount;
        private int MaxCharacterPerLine;
        //
        private Vector3 CurrentLocation;
        private bool _Reading;
        private string _Message;
        private WindowBase _ThisWindow;
        private GameObject _NextPrompt;
        private GameObject _Content;
        private List<GameObject> _MessageString;
        private WindowLocation _WindowLocation;

        //
        public bool Reading { get { return _Reading; } set { _Reading = value; } }
        public string Message { get { return _Message; } set { _Message = value; } }
        public WindowBase ThisWindow { get { return _ThisWindow; } private set { _ThisWindow = value; } }
        public GameObject NextPrompt { get { return _NextPrompt; } private set { _NextPrompt = value; } }
        public GameObject Content { get { return _Content; } set { _Content = value; } }
        public List<GameObject> MessageString { get { return _MessageString; } set { _MessageString = value; } }
        public WindowLocation WindowLocation { get { return _WindowLocation; } set { _WindowLocation = value; } }

        //
        public MessageWindow()
        {

            //
            ThisWindow = new WindowBase();
            MessageString = new List<GameObject>();
            CurrentLocation = Vector3.zero;
            WindowLocation = WindowLocation.BOTTOM;

            //
            CreateWindow();
            SetMaxLineSize();
            ClearContent();

        }
        public MessageWindow(GameObject Player)
        {

            //
            ThisWindow = new WindowBase();
            MessageString = new List<GameObject>();
            CurrentLocation = Vector3.zero;
            WindowLocation = WindowLocation.BOTTOM;

            //
            CreateWindow(Player);
            SetMaxLineSize();
            ClearContent();

        }
        public MessageWindow(WindowLocation NewLocation, GameObject Player)
        {

            //
            ThisWindow = new WindowBase();
            MessageString = new List<GameObject>();
            CurrentLocation = Vector3.zero;
            WindowLocation = NewLocation;
            //
            CreateWindow(Player);
            SetMaxLineSize();
            ClearContent();

        }
        public void NewMessage(string NewMessage, bool Escapable)
        {

            CanEscape = Escapable;
            Reading = true;
            Message = NewMessage;
            ClearMessage();
            SetTotalCharacters();
            CountTotalLines();
            RefreshWindow();
            ShowWindow();
            ClearContent();
            CreateCharacters();

        }
        public void NewMessage(string NewMessage, PlayerControl Player, bool Escapable)
        {

            CanEscape = Escapable;
            Player.DoShomething();
            Reading = true;
            Message = NewMessage;
            ClearMessage();
            SetTotalCharacters();
            CountTotalLines();
            RefreshWindow();
            ShowWindow();
            ClearContent();
            CreateCharacters();

        }
        public void ShowWindow() { ThisWindow.ShowWindow(CurrentLocation); }
        public void HideWindow()
        {
            Reading = false;
            ThisWindow.HideWindow();
        }
        public void ClearContent()
        {

            if (Content != null) { Object.Destroy(Content); }
            Content = new GameObject { name = "Content" };
            Content.transform.position = ThisWindow.WindowContainer.transform.position;
            Content.transform.parent = ThisWindow.WindowContainer.transform;

        }
        public void ClearMessage()
        {

            MessageString.Clear();

        }
        public void RefreshWindow()
        {

            ThisWindow.RefreshContent(Content);

        }
        public void CreateWindow()
        {

            switch (WindowLocation)
            {

                case WindowLocation.BOTTOM:
                    {
                        CurrentLocation = new Vector3(0, -3);
                        break;
                    }
                case WindowLocation.TOP:
                    {

                        CurrentLocation = new Vector3(0, 3);
                        break;
                    }
                case WindowLocation.CENTER:
                    {

                        CurrentLocation = Vector3.zero;
                        break;
                    }
                default:
                    {

                        CurrentLocation = new Vector3(0, 3);
                        WindowLocation = WindowLocation.BOTTOM;
                        break;

                    }

            }

            //
            ThisWindow.CreateWindow("Message", new Vector2(5, 1), false);

            //
            NextPrompt = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/NextCursor")) as GameObject;
            NextPrompt.name = "NextCursor";
            NextPrompt.transform.position = ThisWindow.WindowContainer.transform.position;
            NextPrompt.transform.position += new Vector3(0, ThisWindow.WindowSize.y - 2.5f, 0);
            NextPrompt.transform.parent = ThisWindow.WindowContainer.transform;

        }
        public void CreateWindow(GameObject Player)
        {

            switch (WindowLocation)
            {

                case WindowLocation.BOTTOM:
                    {
                        CurrentLocation = new Vector3(0, -3);
                        break;
                    }
                case WindowLocation.TOP:
                    {

                        CurrentLocation = new Vector3(0, 3);
                        break;
                    }
                case WindowLocation.CENTER:
                    {

                        CurrentLocation = Vector3.zero;
                        break;
                    }
                default:
                    {

                        CurrentLocation = new Vector3(0, 3);
                        WindowLocation = WindowLocation.BOTTOM;
                        break;

                    }

            }

            //
            ThisWindow.CreateWindow("Message", new Vector2(5, 1), CurrentLocation, false, Player);

            //
            NextPrompt = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/NextCursor")) as GameObject;
            NextPrompt.name = "NextCursor";
            NextPrompt.transform.position = ThisWindow.WindowContainer.transform.position;
            NextPrompt.transform.position += new Vector3(0, ThisWindow.WindowSize.y - 2.5f, 0);
            NextPrompt.transform.parent = ThisWindow.WindowContainer.transform;

        }
        public void Read()
        {

            if (ThisWindow.ReturnHandler() && Reading && CanEscape)
            {

                if (RemainingCharactersCount == 0)
                {

                    Message = string.Empty;
                    Reading = false;
                    ClearMessage();
                    ClearContent();
                    HideWindow();

                }
                else if (RemainingCharactersCount > 0)
                {

                    ClearMessage();
                    ClearContent();
                    CreateCharacters();

                }

            }

        }
        public void Read(PlayerControl Player)
        {
     
            if (ThisWindow.ReturnHandler() && Reading && CanEscape)
            {

                if (RemainingCharactersCount == 0)
                {
                    
                    Message = string.Empty;
                    Reading = false;
                    ClearMessage();
                    ClearContent();
                    HideWindow();
                    Player.NotDoShomething();

                }
                else if (RemainingCharactersCount > 0)
                {

                    ClearMessage();
                    ClearContent();
                    CreateCharacters();

                }

            }

        }
        public bool ReadThrough()
        {

            if (Reading)
            {

                return true;

            }

            return false;

        }
        private void SetMaxLineSize()
        {

            MaxCharacterPerLine = (int)Mathf.Pow(ThisWindow.WindowSize.x, 2);

        }
        private void SetTotalCharacters()
        {

            RemainingCharactersCount = Message.Length;

        }
        private void CountTotalLines()
        {

            LineCount = (int)(Message.Length / Mathf.Pow(ThisWindow.WindowSize.x, 2));
            if (Message.Length % Mathf.Pow(ThisWindow.WindowSize.x, 2) > 0)
            {

                LineCount++;

            }

        }
        public void CreateCharacters()
        {

            int Counter;
            int FullWindow;
            int CurrentLine;
            int CurrentIndex;
            Counter = 0;
            FullWindow = 0;
            CurrentLine = 0;
            CurrentIndex = 0;

            for (int i = 0; i < Message.Length; i++)
            {

                if (Counter == MaxCharacterPerLine)
                {

                    CurrentLine++;
                    Counter = 0;

                }

                if (FullWindow <= (MaxCharacterPerLine * 3) - 1)
                {
                    GameObject Character;
                    Character = WindowManager.Letter(Message[i]);
                    Character.transform.position = ThisWindow.WindowContainer.transform.position;
                    Character.transform.position += new Vector3((ThisWindow.WindowSize.x * -1) + Counter * 0.40f, ThisWindow.WindowSize.y - CurrentLine);
                    Character.transform.parent = Content.transform;
                    MessageString.Add(Character);
                    RemainingCharactersCount--;
                    CurrentIndex++;
                    FullWindow++;
                    Counter++;

                }

            }

            if (RemainingCharactersCount != 0)
            {

                string NextMessage;
                NextMessage = string.Empty;

                for (int i = CurrentIndex; i < Message.Length; i++)
                {

                    NextMessage += Message[i];

                }

                Message = NextMessage;

            }

        }

    }

}