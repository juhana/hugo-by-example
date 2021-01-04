---
title: Scoring
permalink: /tips/scoring/
categories: 
  - Tips
---

Hugo has some support for score and rankings built-in. The first thing
you'll want to do is declare the MAX_SCORE (highest score possible in
the game), MAX_RANK (highest rank), and descriptions for each ranking.
A game with a 30 points total with four ranks (set at 0, 10, 20, and 30
points each) would have something like this:

    !    This goes up at the top somewhere
        MAX_SCORE = 30
        MAX_RANK = 3
        ranking[0] = "A Big Zero"
        ranking[1] = "Barely Started"
        ranking[2] = "Almost There"
        ranking[3] = "Ruler of the Example Game"

You'd be all ready to go if there wasn't a little problem in the current
version of the Hugo library (v3.1.03.1). Until things are fixed in the
next release, you'll want to use this replacement:

    replace PrintScore(end_of_game)
    {
        if STATUSTYPE = 1 and MAX_SCORE
        {
            if end_of_game:  print ""
            print "You ";
            if not end_of_game
                print "have ";
            print "scored a total of ";
            print number score; " out of "; number MAX_SCORE;
            if ranking[0] ~= ""
            {
                print ", giving you the rank of ";

                ! A complicated formula, since only
                ! integer division is allowed:
                !
                print ranking[(score*MAX_RANK)/MAX_SCORE];
            }
            print "."
        }
    }

This code changes both the formula for determining the rank (the old one
came up with wrong answers in some situations) and adds a semicolon at
the end of that line so there isn't a new line before the full stop.

Last of all, wherever you want to reward the player with points (10 in
this case), add:

    score = score + 10

Just make sure the trigger isn't repeatable or else it'll break your
ranking. Voilà!

## Score Notification

Some games have a "**\[Your score has gone up\]**" text pop up every
time the player has been awarded some points. Let's throw together a
quick routine that handles this for us automatically!

1.  First, let's make some grammar so the player can turn the
    notification system on and off.
        xverb "notify"
        *                     DoNotifyOnOff
        * "on"                DoNotifyOn
        * "off"               DoNotifyOff
2.  Now, let's make those verb routines, along with a global to keep
    track of score notificaion:
        global score_notify

        routine DoNotifyOnOff
        {
              if score_notify
                    Perform(&DoNotifyOff)
              else
                    Perform(&DoNotifyOn)
        }

        routine DoNotifyOn
        {
              if score_notify
                   "[Score notification already on.]"
              else
                   {
                   "[Score notification on.]"
                   score_notify = 1
                   }
        }

        routine DoNotifyOff
        {
              if not score_notify
                   "[Score notification already off.]"
              else
                   {
                   "[Score notification off.]"
                   score_notify = 0
                   }
        }
3.  Now let's get into the actual score notification stuff. First, add a
    "ScoreNotify" call to [main](/routines/main/), after runevents and
    RunScripts (but before PrintStatusLine):
        routine main
        {
                counter = counter + 1
                run location.each_turn
                runevents
                RunScripts
                ScoreNotify
                if speaking not in location
                     speaking = 0
            PrintStatusLine
        }
4.  Now make another global to hold the points-to-be-added-to-the-score
    and a ScoreNotify routine
        global points

        routine ScoreNotify
        {
              if points and score_notify
                   {
                   "\n\B[Your score has gone up.]\b"
                   ! or possibly
                   ! print "\n\B[Your score has gone up by "; number points; " points.]\b"
                   }
              score = points + score   ! add the points to the score
              points = 0    ! reset the point counter
        }
5.  Lastly, wherever in the game that the player scores points, instead
    of doing the usual "score = score + <points to be added>", do this:
             points = points + <score-to-be-added>
