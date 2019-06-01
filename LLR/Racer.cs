using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Racer : MonoBehaviour
{

    // How many checkpoints has this player has passed
    public int checkpointTotal;

    // How much time does this racer currently have
    // In Seconds
    public float thisRacerCurrentTime;

    //
    [SerializeField]
    private Text timerDisplay;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

        UpdateTimerDisplay();

    }

    private void UpdateTimerDisplay()
    {

        // start losing time
        thisRacerCurrentTime -= Time.deltaTime;

        // Declare temp integeres
        int hours = 0, minutes = 0, seconds = 0;

        // Convert total time into HMS format
        hours = (int)(thisRacerCurrentTime / 3600);
        minutes = ((int)thisRacerCurrentTime - (hours * 60)) / 60;
        seconds = ((int)thisRacerCurrentTime - (minutes * 60));

        if (seconds < 0) seconds = 0;

        // Put all integers into a string
        string timeToDisplay = string.Format("{0}:{1}:{2}", hours, minutes, seconds);

        // Update string to display
        timerDisplay.text = timeToDisplay;

    }

}
