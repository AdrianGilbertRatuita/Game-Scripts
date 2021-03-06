﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

class DynamicTimer : RegularTimer
{
    public DynamicTimer(TimerManager manager, float start, float end) : base(manager, start, end)
    {
    }

    public DynamicTimer(TimerManager manager, float start, float end, RunTimer TimerDelegate) : base(manager, start, end, TimerDelegate)
    {
    }

    public DynamicTimer(TimerManager manager, float start, float end, RunTimer TimerDelegate, GameObject gameObject) : base(manager, start, end, TimerDelegate, gameObject)
    {
    }

    public override void AddTimer()
    {

        managerReference.SetupTimerList();
        managerReference.Timers.Add(this);

    }

    public override void DeleteTimer()
    {

        managerReference.Timers.Remove(this);

    }

    // Add time to the counter
    public void AddTime(float moreTime)
    {

        startTime -= moreTime;

    }

    // Subtract time to the counter
    public void SubtractTime(float lessTime)
    {

        startTime += lessTime;

    }

    // Add time to the passed timer's counter
    public static void AddTime(DynamicTimer timerToAddTimeTo, float moreTime)
    {

        timerToAddTimeTo.AddTime(moreTime);

    }

    // Subtract time to the passed timer's counter
    public static void SubtractTime(DynamicTimer timerToSubtractTimeTo, float lessTime)
    {

        timerToSubtractTimeTo.SubtractTime(lessTime);

    }

}