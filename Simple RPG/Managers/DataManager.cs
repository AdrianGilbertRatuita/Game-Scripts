using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Assets.Scripts.Objects.Player;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using UnityEngine;

namespace Assets.Scripts.Managers
{
    public class DataManager
    {

        public static void SaveData(GamePlayer SavePlayer)
        {

            FileStream SaveFile = File.Open(Application.persistentDataPath + "/PlayerInfo.player", FileMode.OpenOrCreate);
            //
            BinaryFormatter Format;
            Format = new BinaryFormatter();
            //
            PlayerData NewSave;
            NewSave = new PlayerData(SavePlayer);
            //
            Format.Serialize(SaveFile, NewSave);
            SaveFile.Close();

        }

        public static GamePlayer LoadData()
        {

            
            PlayerData LoadedSave;
            GamePlayer LoadedPlayer;
            LoadedPlayer = new GamePlayer();

            if (File.Exists(Application.persistentDataPath + "/PlayerInfo.player"))
            {

                //
                FileStream SaveFile = File.Open(Application.persistentDataPath + "/PlayerInfo.player", FileMode.Open);
                //
                BinaryFormatter Format;
                Format = new BinaryFormatter();
                //
                LoadedSave = (PlayerData)Format.Deserialize(SaveFile);
                LoadedPlayer = LoadedSave.GetPlayerData();
                SaveFile.Close();

            }


            return LoadedPlayer;            
            
        }

    }

}
