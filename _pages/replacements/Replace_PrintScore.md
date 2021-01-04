---
title: Replace PrintScore
permalink: /replacements/printscore/
categories: 
  - Replacements
---

### What it fixes

1.  The original `PrintScore` uses some bad math to calculate the proper
    ranking. This version attempts to fix that.
2.  The original also has an accidental new line, leaving the full stop
    stranded by itself.

(See also: [Scoring](tips/scoring/))

### The code

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
