using Assets.Scripts.Managers;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HUD : MonoBehaviour
{

    public bool Show;
    public float Padding;
    //
    private GameObject GUIHUD;
    private GameObject NAME;
    private GameObject HP;
    private GameObject LEVEL;
    private GameObject GOLD;
    private PlayerControl Player;
    private GameObject PlayerObject;

    // Use this for initialization
    void Start ()
    {

        Initialize();
        

    }

    public void Initialize()
    {

        PlayerObject = GameObject.FindGameObjectWithTag("Player");
        Player = PlayerObject.GetComponent<PlayerControl>();

    }

    public void CreateCharacters()
    {
        string Name = Player.NAME;
        string HPString = "HP: " + Player.HP.ToString();
        string LevelString = "LVL: " + Player.LEVEL.ToString();
        string GoldString = "GOLD: " + Player.GOLD.ToString();
        
        GameObject Character;

        for (int i = 0; i < Name.Length; i++)
        {

            Character = WindowManager.Letter(Name[i]);
            Character.name = Name[i].ToString();
            Character.transform.position = NAME.transform.position;
            Character.transform.position += new Vector3(Padding + i * 0.40f, 4, 0);
            Character.transform.parent = HP.transform;

        }

        for (int i = 0; i < HPString.Length; i++)
        {

            Character = WindowManager.Letter(HPString[i]);
            Character.name = HPString[i].ToString();
            Character.transform.position = HP.transform.position;
            Character.transform.position += new Vector3(Padding + i * 0.40f, 3, 0);
            Character.transform.parent = HP.transform;

        }

        for (int i = 0; i < LevelString.Length; i++)
        {

            Character = WindowManager.Letter(LevelString[i]);
            Character.name = LevelString[i].ToString();
            Character.transform.position = LEVEL.transform.position;
            Character.transform.position += new Vector3(Padding + i * 0.40f, 2, 0);
            Character.transform.parent = LEVEL.transform;

        }

        for (int i = 0; i < GoldString.Length; i++)
        {

            Character = WindowManager.Letter(GoldString[i]);
            Character.name = GoldString[i].ToString();
            Character.transform.position = LEVEL.transform.position;
            Character.transform.position += new Vector3(Padding + i * 0.40f, 1, 0);
            Character.transform.parent = LEVEL.transform;

        }


    }

    public void UpdateHUD()
    {

        if (GUIHUD != null) { Destroy(GUIHUD); }
        if (NAME != null) { Destroy(NAME); }
        if (HP != null) { Destroy(HP); }
        if (LEVEL != null) { Destroy(LEVEL); }

        //
        GUIHUD = new GameObject();
        GUIHUD.name = "GUIHUD";
        GUIHUD.transform.position = PlayerObject.transform.position;
        GUIHUD.transform.parent = PlayerObject.transform;

        NAME = new GameObject();
        NAME.name = "NAME";
        NAME.transform.position = GUIHUD.transform.position;
        NAME.transform.parent = GUIHUD.transform;

        HP = new GameObject();
        HP.name = "HP";
        HP.transform.position = GUIHUD.transform.position;
        HP.transform.parent = GUIHUD.transform;

        LEVEL = new GameObject();
        LEVEL.name = "LEVEL";
        LEVEL.transform.position = GUIHUD.transform.position;
        LEVEL.transform.parent = GUIHUD.transform;

        GOLD = new GameObject();
        GOLD.name = "GOLD";
        GOLD.transform.position = GUIHUD.transform.position;
        GOLD.transform.parent = GUIHUD.transform;
        //
        CreateCharacters();

    }

    // Update is called once per frame
    void Update ()
    {

        if (Show)
        {

            UpdateHUD();

        }
        else
        {

            Destroy(GUIHUD); 
            Destroy(NAME); 
            Destroy(HP); 
            Destroy(LEVEL);
            Destroy(GOLD);

        }
        

    }

}
