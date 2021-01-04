---
title: PushDir
permalink: /verb-routines/pushdir/
categories: 
  - Verb Routines
---

`PushDir` is a verb routine to support pushing objects in specific
directions, or just to avoid the following:

>&gt; push boulder southwest  
>You haven't encountered any "boulder southwest". (If you're sure you
>need to refer to that, try putting it another way.)


### Don't Call Me a Dummy, Dummy

Even if your game doesn't support pushing objects from room to room, you
might want to add some dummy grammar entries and a routine to properly
parse **&gt;PUSH BOULDER SOUTHWEST**. If you think someone might try
that in your game, you'd want to add something like the following to
your code:

    ! add to grammar
    verb "push","pull","press","move"
        * object "to" xobject           DoPushDir
        * object "north"/ "n"/ "south"/ "s"/ "east"/ "e"/ "west"/ "w"/ \
        "southeast"/ "se"/ "southwest"/ "sw"/ "northwest"/ "nw"/ \
        "northeast"/ "ne"/ "up"/ "u"/ "down"/ "d"/ "in"/ "out"/ \
        "inside"/ "outside"             DoPushDir


    routine DoPushDir
    {
        "That would not help the present situation."
        return false ! let's not use up a turn
    }

Your game will seem *so smart*!

### Pushing In Earnest

Next, let's code up a working example. As you saw in the code above, we
had to specifically mention every direction for the `PUSH` command. The
parser really hates if the object is directly next to the xobject since
it has no way to distinguish what's what without our help. Our code will
turn **&gt;PUSH OBJECT DIRECTION** into **&gt;PUSH OBJECT TO THE
DIRECTION** to get around that. We will also include code so that
pushable objects can't be pushing into every room.

    verb "push","pull","press","move"
        * object "to" xobject           DoPushDirTo
        * object "north"/ "n"/ "south"/ "s"/ "east"/ "e"/ "west"/ "w"/ \
        "southeast"/ "se"/ "southwest"/ "sw"/ "northwest"/ "nw"/ \
        "northeast"/ "ne"/ "up"/ "u"/ "down"/ "d"/ "in"/ "out"/ \
        "inside"/ "outside"             DoPushDir


    property outofbounds
    property pushstart
    property pushend

    ! This routine turns >PUSH OBJECT DIRECTION into >PUSH OBJECT TO DIRECTION
    routine DoPushDir
    {
        local a,m

        ! the for loop finds the last word before the direction
        ! which should be the object's noun
        for (a=2; ; a=a+1)
            {
            if ObjWord(word[a],object) = noun
                break
            }
        ! Let's add one to find the direction words
        a = a + 1

        ! Let's identify what we've got and point to the right direction object
        select word[a]
            case "north", "n":      m = n_obj
            case "south", "s":      m = s_obj
            case "east", "e":       m = e_obj
            case "west", "w":       m = w_obj
            case "northwest", "nw": m = nw_obj
            case "northeast", "ne": m = ne_obj
            case "southeast", "se": m = se_obj
            case "southwest", "sw": m = sw_obj
            case "up", "u":         m = u_obj
            case "down", "d":       m = d_obj
            case "in", "inside":    m = in_obj
            case "out", "outside":  m = out_obj

        ! Let's run it
        return Perform(&DoPushDirTo, object, m)
    }

    routine DoPushDirTo
    {
        local moveto
        moveto = xobject

        if not (object is mobile and object is not clothing) ! if the item is not rollable, we'll just act
            return Perform(&DoMove, object)    ! like the player just tried to move it.
        elseif xobject.type ~= direction           ! since mobile = worn, we make sure the item is not
            {                                  ! clothing
            ! possibly, you might want to add code that checks to see
            ! if the xobject is a container and in such cases, interpreters
            ! >PUSH OBJECT INTO XOBJECT as DoPutIn. To avoid the checkheld headache
            ! that introduces, we will ignore that possiblity for now
            VMessage(&DoPushDirTo,1)
            return false
            }

        ! Let's check to see if we're pushing to a location
        ! we don't want the player pushing to
        local k
        k = location.(moveto.dir_to)
        if k > 1  ! means the direction we are moving in is a viable direction
            {
            ! is the direction a room we can walk to but can't push objects to?
            if k.outofbounds
                return false

            ! Let's print a success message before the move "You start pushing..."
            if not object.pushstart
                VMessage(&DoPushDirTo,2)
            }

        ! If DoGo works, then move the object to the location and print
        ! a followup success message.
        if Perform(&DoGo, xobject)
            {
            print ""
            move object to location
            VMessage(&DoPushDirto,3)
            return true
            }
    }

    replace NewVMessages(r, num, a, b)
    {
            select r

        case &DoPushDirTo
        {
            ! Let's set default DoPushDirTo messages
            select num
            case 1:  print "Try pushing "; Art(object); " in a direction."
            case 2:  print CThe(player); MatchPlural(player, " pushes ", " push "); Art(object); " over to the..."
            case 3:  print CArt(object); " slows to a stop."
        }

            case else : return false

           return true ! this line is only reached if we replaced something
    }

Note the addition of the extra properties. Here is some sample code that
makes use of the above:

    room STARTLOCATION "Start Location"
    {
    long_desc
           "This is the starting room description."
    e_to EastRoom
    cant_go
        {
        if object = s_obj
            "That wing is closed."
        else
            return false
        }
    }

    object onion "giant onion"
    {
    adjective "giant"
    noun "onion"
    article "the"
    in STARTLOCATION
    is mobile
    pushstart
        "You roll the giant onion to the..."
    pushend
        "The onion rolls to a stop."
    }

    room EastRoom "East Room"
    {
    w_to STARTLOCATION
    u_to Stairs
    }

    room Stairs "Upstairs"
    {
    d_to EastRoom
    outofbounds
        print "You can't push "; art(object); " up the stairs."
    }

That gives us:

>Start Location  
>The giant onion is here.
>
>&gt;push onion east  
>You roll the giant onion to the...
>
>East Room  
>The onion rolls to a stop.
>
>&gt;push onion u  
>You can't push the giant onion up the stairs.

### Requirements

`DoPushDirTo` has been updated to require the
[mobile](Attributes) attribute, as that is a seldom used
attribute somewhat meant for such things (it is also used for attachable
objects, so if your game uses attachables, you may need to use something
else). You also need to be mindful of your exit code, putting all "You
can't go that way." messages in the `cant_go` property, like above.
