---
title: Fuses and Daemons
permalink: /timers/fuses-and-daemons/
categories: 
  - Timers
---

# Description

Fuses and daemons are object-attached [events](Events) that
are moved in and out of scope (and therefore, starting or stopping them)
with [`Activate`](Fuses_and_Daemons#Activating/Deactivating)
and [`Deactivate`](Fuses_and_Daemons#Activating/Deactivating)
routines. They are described here together mainly because most things
done in one can also be done in the other (this author almost always
uses fuses but knows at least one other author who always uses daemons).

## Daemons

The simpler of the two is daemons as they are nothing more than events
that can be started and stopped.

    daemon <name>
    {}

    event in <name>  ! the "in" is optional
    {
    !  Event/daemon code
    }

## Fuses

Fuses are event objects with the addition of `timer` and `tick`
properties.

| fuse property | description                                                                                                           |
|---------------|-----------------------------------------------------------------------------------------------------------------------|
| timer         | the number of turns before the fuse event runs (can be set "by hand" or by `Activate(`<fuse name>`, `<timer turns>`)` |
| tick          | a routine that decrements timer by one and returns the number of turns remaining (i.e., the value of timer)           |

    fuse <name>
    {}

    event in <name> ! the "in" is optional
    {
    ! any code that executes each turn the fuse is running
          if not self.tick
          {
          ! code that executes when the fuse runs out
          }
    }

### Vault of Hugo example

The `bombfuse` fuse object in "Vault of Hugo" does this:

          if not self.tick
          {
            if Contains(location, bomb)     ! if in player's location
            {
                "\nKABOOM!\n\n\
                (Right next to the bomb was not, as they say, such
                a great place to be as it went off.  You're dead now.)"

                endflag = 2     ! when endflag is non-false, it
                        ! immediately triggers the end of the
                        ! game
            }
            else
            {
                    ...  ! what happens if the player is NOT in the same room as the bomb

# Activating/Deactivating

Both daemons and fuses are started and stopped by `Activate` and
`Deactivate`, respectively.

| Usage                         |
|-------------------------------|
| `Activate(`<daemon_object>`)` |

*Starting daemons*

| Usage                                                      |
|------------------------------------------------------------|
| `Activate(`<daemon_object>`,`<number_of_turns_in_timer>`)` |

*Starting fuses*

| Usage                           |
|---------------------------------|
| `Deactivate(`<daemon_object>`)` |

*Stopping either*

# The code for everything listed above

For reference, here is the code from [hugolib.h](Hugolib.h)
that defines all of this:

    !\
    *****************************************************************************

    FUSE AND DAEMON CLASSES AND ROUTINES

    *****************************************************************************
    \!

    #ifclear NO_FUSES

    property timer alias n_to               ! for fuses only
    property tick alias ne_to               !

    property activate_event alias when_open
    property deactivate_event alias when_closed

    class fuse
    {
        type fuse
        size 0
        timer 0
        in_scope 0
        tick
        {
            if --self.timer < 0
                self.timer = 0

    #ifset DEBUG
            if debug_flags & D_FUSES
            {
                print "[Running fuse "; number self; ":  timer = ";
                print number self.timer; "]"
            }
    #endif

            if self.timer = 0
                Deactivate(self)
            return self.timer
        }
    }

    class daemon
    {
        type daemon
        size 0
        in_scope 0
    }

    routine Activate(a, set)                ! <set> is for fuses only
    {
        local err

        a.in_scope = player
        a is active
        if a.type = fuse
        {
            if set
                a.timer = set

            run a.activate_event
        }
        elseif a.type = daemon
        {
            if set and not a.#timer
            {
                print "[WARNING:  Attempt to set nonexistent timer
                    property on daemon (object "; number a; ")]"
                err = true
            }
            else
                a.timer = set

            run a.activate_event
        }
        else
        {
            print "[WARNING:  Attempt to activate non-fuse/\
            daemon (object "; number a; ")]"
            err = true
        }

    #ifset DEBUG
        if debug_flags & D_FUSES and not err
        {
            print "[Activating "; a.name; " "; number a;
            if a.type = fuse
                print " (timer = "; number a.timer; ")";
            print "]"
        }
    #endif

    }

    routine Deactivate(a)
    {
        local err

        remove a
        a.in_scope = 0
        a is not active

        if a.type ~= fuse and a.type ~= daemon
        {
            print "[WARNING:  Attempt to deactivate non-fuse/\
                daemon (object "; number a; ")]"
            err = true
        }
        else
        {
            run a.deactivate_event
        }

    #ifset DEBUG
        if debug_flags & D_FUSES and not err
        {
            print "[Deactivating "; a.name; " "; number a; "]"
        }
    #endif

    }

    #endif  ! ifclear NO_FUSES


    !\
