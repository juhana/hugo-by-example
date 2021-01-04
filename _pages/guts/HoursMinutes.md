---
title: HoursMinutes
permalink: /guts/hoursminutes/
categories: 
  - Hugo Guts
---

`HoursMinutes` is the [hugolib.h](library/hugolib.h/)
[routine](routines/) that translates the turn
[counter](globals/counter/) into "clock format" for
[STATUSTYPE](globals/statustype/) 2 games. Examples:

    HoursMinutes(0,0) ! would result in "12:00 a.m."

    HoursMinutes(780,0) ! would result in "1:00 p.m."

    HoursMinutes(1080,1) ! would result in "18:00 ")

## The code

    !----------------------------------------------------------------------------
    ! HoursMinutes(val[, military])
    ! prints the time in 12-hour hh:mm format, as given by <val> minutes past
    ! midnight, or in 24-hour hh:mm military-time format if <military> is true

    routine HoursMinutes(val, military)
    {
        local hours, minutes

        hours = val / 60
        minutes = val - hours * 60

        if not military
        {
            if hours > 12:     hours -= 12
            elseif hours = 0:  hours = 12
        }
        elseif hours < 10:  print "0";

        print number hours; ":";
        if minutes < 10
            print "0";
        print number minutes; " ";

        if not military
        {
            if val >= 720
                print "p.m.";
            else
                print "a.m.";
        }
    }
