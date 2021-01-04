---
title: AfterRoutines
permalink: /guts/afterroutines/
categories: 
  - Hugo Guts
---

`AfterRoutines` is the [hugolib.h](hugolib.h)
[routine](routine) that actually calls the various
[after](after) routines (as described on the [game
loop](game_loop) page). Taking a good look at it can help
attain a better understanding of the order of things.

## The code

    !----------------------------------------------------------------------------
    ! AfterRoutines
    !
    ! Runs all relevant routines that might follow a verbroutine.  Note that
    ! object.after and xobject.after are not called here, nor is anything that
    ! should be explicitly called by a verbroutine depending on its (degree of)
    ! failure or success.
    !----------------------------------------------------------------------------

    routine AfterRoutines
    {
        local i, r

        r = player.after
        if r
        {
    #ifset DEBUG
            if debug_flags & D_PARSE
            {
                print "\B["; player.name;
                if debug_flags & D_OBJNUM
                    print " ["; number player; "]";
                print ".after returned "; number r; "]\b"
            }
    #endif
        }

        r = player.react_after
        if r
        {
    #ifset DEBUG
            if debug_flags & D_PARSE
            {
                print "\B["; player.name;
                if debug_flags & D_OBJNUM
                    print " ["; number player; "]";
                print ".react_after returned "; number r; "]\b"
            }
    #endif
        }

        r = location.after
        if r
        {
    #ifset DEBUG
            if debug_flags & D_PARSE
            {
                print "\B["; location.name;
                if debug_flags & D_OBJNUM
                    print " ["; number location; "]";
                print ".after returned "; number r; "]\b"
            }
    #endif
        }

        r = location.react_after
        if r
        {
    #ifset DEBUG
            if debug_flags & D_PARSE
            {
                print "\B["; location.name;
                if debug_flags & D_OBJNUM
                    print " ["; number location; "]";
                print ".react_after returned "; number r; "]\b"
            }
    #endif
        }

        for i in location
        {
            r = i.react_after
            if r
            {
    #ifset DEBUG
                if debug_flags & D_PARSE
                {
                    print "\B["; i.name;
                    if debug_flags & D_OBJNUM
                        print " ["; number i; "]";
                    print ".react_after returned "; number r; "]\b"
                }
    #endif
            }
        }
    }
