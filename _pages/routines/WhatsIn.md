---
title: WhatsIn
permalink: /routines/whatsin/
categories: 
  - Routines
---

`WhatsIn(object)` lists the possessions of the specified parent, according the form given by the global [FORMAT](FORMAT). Returns the number of objects listed. Also calls: [SpecialDesc](SpecialDesc), [ListObjects](ListObjects)

Basically, `WhatsIn` is the routine that lists everything in an open or
transparent container (or platform) when you `>LOOK` around or examine
that aforementioned container. In older versions of the Hugo library,
one would have to call `WhatsIn` manually, but these days, routines like
[DescribePlace](DescribePlace), [DoLook](DoLook),
or [DoLookIn](DoLookIn) will do it for you.

>Inside the small mailbox is a leaflet.

In particular, `WhatsIn` first determines that there are child objects
to be listed. Then, depending on the object, it prints the proper
beginning text. For instance, if the object is the player character, it
prints, "You are carrying..." In the above example, the object (the
mailbox) is a container, causing it to print, "Inside the "
&lt;object name&gt; " is..."

[ListObjects](ListObjects) is then called and lists all
applicable objects in the right format.

## The code

    !----------------------------------------------------------------------------
    ! WhatsIn(object)
    ! lists the children of <object>, if any, in a relatively orderly manner

    routine WhatsIn(obj)
    {
        local i, totallisted
        local initial_list_nest

        if FORMAT & NORECURSE_F
            return

        for i in obj
        {
            i is not already_listed
            if i is not hidden
                totallisted++
        }

        if totallisted = 0
            return

        list_count = totallisted

        if obj is not container or (obj is container and obj is platform) or
            (obj is container and (obj is not openable or
                (obj is openable and
                    (obj is open or obj is transparent)))) and
            (obj ~= player or FORMAT & INVENTORY_F) and obj is not quiet
        {
            SpecialDesc(obj)

            ! If list_count is 0 now, but totallisted was not, something must have been
            ! printed by SpecialDesc


            if list_count = 0
            {
                if FORMAT & INVENTORY_F and not (FORMAT & LIST_F) and
                    list_nest = 0
                {
                    print ""
                }
                return totallisted
            }

                if obj.list_contents
                return totallisted

            initial_list_nest = list_nest

            if FORMAT & LIST_F
            {
                if list_nest
                {
                    ! Indent the first time so that it lines up with
                    ! paragraph indentation:
                    i = list_nest
                    if list_nest = 1 and not (FORMAT & NOINDENT_F)
                    {
                        Indent
                        i--
                    }

                    print to (i * 2);   ! INDENT_SIZE);
                }
            }
            else
            {
                Indent
            }

            if obj.contains_desc    ! custom heading
            {
                if FORMAT & LIST_F
                    print ":"
            }
            else
            {
                if obj = player
                {
                    if FORMAT & LIST_F and list_count < totallisted
                        print "\n";

                    ! "You are carrying..."
                    Message(&WhatsIn, 1, totallisted)

                    if FORMAT & LIST_F
                        print ":"
                }
                elseif obj is living and not obj.prep
                {
                    ! "X has..."
                    Message(&WhatsIn, 2, obj, totallisted)
                    if FORMAT & LIST_F
                        print ":"
                }
                else
                {
                    if list_count < totallisted
                        ! "Also sitting on/in..."
                        Message(&Whatsin, 3, obj)
                    else
                        ! "Sitting on/in..."
                        Message(&Whatsin, 4, obj)
                    The(obj)
                    FORMAT = FORMAT | ISORARE_F
                }
            }

            ListObjects(obj)

            list_nest = initial_list_nest
        }
        return totallisted
    }
