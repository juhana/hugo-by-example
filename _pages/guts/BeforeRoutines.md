---
title: BeforeRoutines
permalink: /guts/beforeroutines/
categories: 
  - Hugo Guts
---

`BeforeRoutines` is the [hugolib.h](library/hugolib.h/)
[routine](routines/) that actually calls the various
[before](properties/before/) routines (as described on the
[game loop](loops/game-loop/) page). Taking a good look at it can help
attain a better understanding of the order of things.

## The code

    !----------------------------------------------------------------------------
    ! BeforeRoutines(queue)
    !
    ! Runs all relevant routines that might precede a verbroutine, returning
    ! true if any of them returns true.
    !----------------------------------------------------------------------------

    routine BeforeRoutines(queue)
    {
        local r, i

        r = player.react_before
        if r
        {
    #ifset DEBUG
            if debug_flags & D_PARSE
            {
                print "\B["; player.name;
                if debug_flags & D_OBJNUM
                    print " ["; number player; "]";
                print ".react_before returned "; number r; "]\b"
            }
    #endif
            return r
        }
        r = player.before
        if r
        {
    #ifset DEBUG
            if debug_flags & D_PARSE
            {
                print "\B["; player.name;
                if debug_flags & D_OBJNUM
                    print " ["; number player; "]";
                print ".before returned "; number r; "]\b"
            }
    #endif
            return r
        }

        r = location.react_before
        if r
        {
    #ifset DEBUG
            if debug_flags & D_PARSE
            {
                print "\B["; location.name;
                if debug_flags & D_OBJNUM
                    print " ["; number location; "]";
                print ".react_before returned "; number r; "]\b"
            }
    #endif
            return r
        }
        r = location.before
        if r
        {
    #ifset DEBUG
            if debug_flags & D_PARSE
            {
                print "\B["; location.name;
                if debug_flags & D_OBJNUM
                    print " ["; number location; "]";
                print "before returned "; number r; "]\b"
            }
    #endif
            return r
        }

        for i in location
        {
            r = i.react_before
            if r
            {
    #ifset DEBUG
                if debug_flags & D_PARSE
                {
                    print "\B["; i.name;
                    if debug_flags & D_OBJNUM
                        print " ["; number i; "]";
                    print ".react_before returned "; number r; "]\b"
                }
    #endif
                return r
            }
        }

        ! queue is -1 if the object was a number (i.e., a literal digit)
        if queue ~= -1 and xobject > display
        {
            r = xobject.before
            if r
            {
    #ifset DEBUG
                if debug_flags & D_PARSE
                {
                    print "\B["; xobject.name;
                    if debug_flags & D_OBJNUM
                        print " ["; number xobject; "]";
                    print ".before returned "; number r; "]\b"
                }
    #endif
                return r
            }
        }

        if queue ~= -1 and object > display
        {
            r = object.before
            if r
            {
    #ifset DEBUG
                if debug_flags & D_PARSE
                {
                    print "\B["; object.name;
                    if debug_flags & D_OBJNUM
                        print " ["; number object; "]";
                    print ".before returned "; number r; "]\b"
                }
    #endif
                return r
            }
        }
    }
