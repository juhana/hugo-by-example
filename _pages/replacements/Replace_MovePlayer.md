---
title: Replace MovePlayer
permalink: /replacements/moveplayer/
categories: 
  - Replacements
---

### What it fixes

If not interrupted by a [before](/properties/before/) routine, the
original sets [event_flag](/globals/event_flag/) to
[true](/definitions/true/) (1). This is annoying when you have already set
[event_flag](/globals/event_flag/) to 2 and don't want the player to
be interrupted with a "Do you want to keep waiting?" message. This fixes
that. It also gets rid of the [jump](/guts/jump/) command.

### The code

    replace MovePlayer(loc, silent, ignore)
    {
       local v, obj, xobj, act, ret, LeavingMovePlayer

    #ifclear NO_OBJLIB
       if loc.type = direction
       {
          local l
          l = location.(loc.dir_to)
          if l > 1                ! since a message always returns 1
             loc = l
          else
             return
       }
    #endif

    #ifset USE_ATTACHABLES
       if ObjectisAttached(player, location, loc)
          return
    #endif

       ! Check if there's a before routine for MovePlayer in the new
       ! location.  Note that the (potential) new location and the old
       ! location are stored in object and xobject, respectively.
       !
       v = verbroutine
       obj = object
       xobj = xobject
       act = actor
       verbroutine = &MovePlayer
       object = loc
       xobject = location
       actor = player
       if not ignore
       {
          while (true)
             {
             ret = player.before
             if ret
                {
                LeavingMovePlayer = true
                break
                }
             ret = location.before
             if ret
                {
                LeavingMovePlayer = true
                break
                }
             ret = loc.before
             if ret
                {
                LeavingMovePlayer = true
                break
                }
             break
             }
       }
       if (not LeavingMovePlayer)
          {
          move player to loc
          old_location = location
          if parent(loc) = 0              ! if it's likely a room object
             location = loc
          else                            ! if it's an enterable object
             location = parent(loc)  ! (noting that the object must be
                      ! in a room, not inside another
                      ! non-room object)

    #ifset USE_ATTACHABLES
          MoveAllAttachables(player, old_location, location)
    #endif

          PrintStatusline
          }

    ! LeavingMovePlayer area

       if not ret
       {
          if not FindLight(location)
             DarkWarning
          elseif not silent
          {
             DescribePlace(location)
             if not event_flag
                event_flag = true
             location is visited
          }

       ! Check if there's an after routine for MovePlayer in the new
       ! location:
       !
          if not ignore
          {
             ret = player.after
             if not ret
                ret = location.after
          }
       }
       verbroutine = v
       object = obj
       xobject = xobj
       actor = act

       return ret
    }
