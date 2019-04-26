using Assets.Scripts.Objects.Window;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.Scripts.Managers
{
    public static class WindowManager
    {

        public static List<IWindow> Windows { get; set; }
        public static void DeactivateWindows()
        {

            foreach (WindowBase W in Windows)
            {

                W.IsActive = false;

            }

        }
        public static IWindow FindActive()
        {

            foreach (IWindow W in Windows)
            {

                if (W.IsActive) { return W; }

            }

            return null;

        }
        public static IWindow FindWindow(string Name)
        {

            foreach (WindowBase W in Windows)
            {

                if (W.WindowName == Name) { return W; }

            }

            return null;

        }
        public static bool AnyWindowActive()
        {

            foreach (IWindow W in Windows)
            {

                if (W.IsActive) { return true; }

            }

            return false;

        }
        public static GameObject Letter(char Character)
        {

            GameObject ReturnedCharacter;

            switch (char.ToUpper(Character))
            {

                case 'A':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/A")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'B':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/B")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'C':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/C")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'D':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/D")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'E':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/E")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'F':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/F")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'G':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/G")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'H':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/H")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'I':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/I")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'J':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/J")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'K':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/K")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'L':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/L")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'M':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/M")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'N':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/N")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'O':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/O")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'P':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/P")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'Q':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/Q")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'R':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/R")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'S':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/S")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'T':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/T")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'U':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/U")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'V':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/V")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'W':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/W")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'X':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/X")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'Y':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/Y")) as GameObject;
                        return ReturnedCharacter;

                    }
                case 'Z':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/Z")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '0':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/0")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '1':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/1")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '2':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/2")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '3':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/3")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '4':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/4")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '5':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/5")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '6':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/6")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '7':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/7")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '8':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/8")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '9':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/9")) as GameObject;
                        return ReturnedCharacter;

                    }
                case ':':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_COLON")) as GameObject;
                        return ReturnedCharacter;

                    }
                case ';':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_SEMICOLON")) as GameObject;
                        return ReturnedCharacter;

                    }
                case ',':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_COMMA")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '.':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_PERIOD")) as GameObject;
                        return ReturnedCharacter;

                    }
                case (char)39:
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_APOSTROPHE")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '!':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_EXCLAMATION")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '?':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_QUESTION")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '-':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_HYPHEN")) as GameObject;
                        return ReturnedCharacter;

                    }
                case ' ':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_SPACE")) as GameObject;
                        return ReturnedCharacter;

                    }
                case '/':
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_SPACE")) as GameObject;
                        return ReturnedCharacter;

                    }
                default:
                    {

                        ReturnedCharacter = Object.Instantiate(Resources.Load("Prefabs/MessageWindow/Alphanumerics/_SPACE")) as GameObject;
                        return ReturnedCharacter;

                    }

            }


        }

    }
}
