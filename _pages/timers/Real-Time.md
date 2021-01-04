---
title: Real-Time
permalink: /timers/real-time/
categories: 
  - Timers
---

For all intents and purposes, time has stopped while the Hugo
interpreter waits for the player to type in a command. It is not
possible to code a game like Melbourne House's The Hobbit or Infocom's
Border Zone, where the player can just dumbly stare at the screen and
NPCs move around without waiting for a command to be entered.

Still, using the [time.h](/contributions/time.h/) library extension, one
could *fake* a real-time game by having actions affected by the passage
of real time.

## Example Code

Let's code a test example where the game gives the player 10 real-time
minutes to leave a cave after an explosion:

    time_object timenow
    {
    }

    ! and a time object to hold difference results
    time_object timesince
    {
    }

    player_character you "you"
    {
    before
         {
               actor
                    {
                    ! let's get the current time *before* we process the move
                    GetCurrentTime(timenow)
                    return false  ! continues the rest of the turn as usual
                    }
         }
    }

    ! let's pretend we coded an explosion that ran GetCurrentTime with the time object timesploded

    time_object escapetime
    {
           ! this object is the amount of time the player has to leave before a cave-in blocks his way
           tm_minute 10
    }

    room crawlpassage "Cave Crawl Passage"
    {
         w_to bigroom
         e_to  {
               CalculateTimeDifference(timenow, timesploded, timesince)
               if IsTimeLonger(timesince,escapetime)
                     "Drat, the explosion caused a cave-in which has trapped you here FOREVER."
               else
                    return exitroom
               }
    }

## Game Design Ramifications

There is at least a couple good reasons why somebody shouldn't design a
game around this kind of system. Still, that doesn't mean it can't be
done!
