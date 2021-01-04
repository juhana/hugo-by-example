---
title: PrintScore
permalink: /routines/printscore/
categories: 
  - Routines
---

`PrintScore` is the [hugolib.h](hugolib.h) routine that is
called either when someone quits, wins, or loses a game (or even, just
when they type **&gt;SCORE**). As you might imagine, if there is one, it
prints the game score.

## The code

    routine PrintScore(end_of_game)
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
                print ranking[(score*100)/MAX_SCORE*MAX_RANK/100]
            }
            print "."
        }
    }
