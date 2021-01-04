---
title: Replace DescribePlace
permalink: /replacements/describeplace/
categories: 
  - Replacements
---

### What it fixes

1.  [initial_desc](initial_desc) properties are still run in
    `SUPERBRIEF` mode.
2.  In `SUPERBRIEF` mode, objects with
    [short_desc](short_desc) properties are treated like
    they don't have them.
3.  The [DESCFORM_F](DESCFORM_F) [FORMAT](FORMAT)
    mask now adds a blank line between every grouping, not just the one
    between the room description and room contents.
4.  Setting an array determines order of object listing (see below).

### How to use

1.  Set the `DESCFORM_F FORMAT` mask by adding the following line to
    [init](init) or somewhere:
        FORMAT = FORMAT | DESCFORM_F
2.  In [init](init), set the values in the
    `DescribePlaceOrder` [array](array) if you want a
    non-default order. Like so:
            DescribePlaceOrder[0] = 1,2,4,5,6,3

    The "key" for the order is as follows:

    1.  Contents of [parent](parent) of player (if the player
        is in or on something)
    2.  Characters with [short_desc](short_desc)'s or
        [initial_desc](initial_desc)'s
    3.  Characters without descriptions
    4.  Objects with [short_desc](short_desc)'s or
        [initial_desc](initial_desc)'s
    5.  Objects without descriptions
    6.  Attachments and contents of [scenery](scenery)
        objects

### Requirements

Descriptionless characters must be listed *after* characters with
descriptions, and descriptionless objects must be listed *after* objects
with descriptions.

### The code

    array DescribePlaceOrder[6]
    attribute already_printed

    replace Describeplace(place, long)
    {
        local obj, count, notlisted, tempformat, charcount, order, didprint
        local need_carriage

        parser_data[PARSER_STATUS] &= ~PRONOUNS_SET

        ! Since, for example, a room description following entering via
        ! DoGo does not trigger before/after properties tied to looking
        ! around:
        !
    #ifclear NO_VERBS
        if verbroutine ~= &DoLookAround
        {
            if place is not visited and verbosity ~= 1
                return Perform(&DoLookAround)
            elseif long = true or verbosity = 2
                return Perform(&DoLookAround)
        }
    #endif

        if not light_source
        {
            Message(&DescribePlace, 1)     ! "It's too dark to see..."
            return
        }

        place is known

        ! Print the name of the location as a heading
        Font(BOLD_ON)
        if not (FORMAT & DESCFORM_F)
            print "\n";

        print capital place.name;

        ! Print ", in <something>" if necessary
        if location = place and player not in place
        {
            if parent(player).prep
                print ", "; parent(player).prep; " ";
            elseif parent(player) is platform
                print ", "; ON_WORD; " ";
            else
                print ", "; IN_WORD; " ";
            print Art(parent(player))
        }
        print newline

        Font(BOLD_OFF)
        override_indent = false

        if place is not visited and verbosity ~= 1
        {
            if &place.initial_desc or &place.long_desc
                {
                didprint = true
                Indent
                }
            if not place.initial_desc
                run place.long_desc
        }
        elseif long = true or verbosity = 2
        {
            if &place.long_desc
                {
                Indent
                didprint = true
                }
            run place.long_desc
        }
        elseif place is not visited and verbosity = 1
        {
            if &place.initial_desc
                {
                Indent
                didprint = true
                }
            run place.initial_desc
        }

        if &place.list_contents and (FORMAT & DESCFORM_F)
            print ""        ! for double-space-after-heading formatting

        ! A location may contain an overriding listing routine, as may any
        ! parent, in the list_contents property
        !
        for obj in place
            obj is not already_printed

        if not place.list_contents
        {
            list_nest = 0

        while order < (DescribePlaceOrder[])
            {
            if not DescribePlaceOrder[order]
                {
                DescribePlaceOrder[order] = order + 1
                }
            select DescribePlaceOrder[order]
                case 1  ! contents of parent of player
                {
                    if player not in location
                    {
                        for obj in (Parent(player))
                        {
                            if obj is not hidden and obj ~= player
                                {
                                need_carriage = true
                                break
                                }
                        }
                    }
                }

                case 2  ! characters with descs
                {
                    for obj in place
                    {
                        if (obj is not hidden and obj is living and
                             obj ~= player and ((&obj.short_desc and verbosity ~= 1) or
                            (obj is not moved and &obj.initial_desc)) and
                            obj is not already_printed )
                        {
                            need_carriage = true
                            break
                        }
                    }
                }

                case 3   ! Characters without descs
                {
                            for obj in place
                            {
                                if (obj is not hidden and obj is living and
                                obj ~= player and
                                (not &obj.short_desc or
                                (&obj.short_desc  and verbosity = 1)) and
                                obj is not already_printed)
                                {
                                    need_carriage = true
                                    break
                                }
                            }
                }

                case 4  ! objects with descs
                {
                    for obj in place
                    {
    #ifset USE_ATTACHABLES
                        ! Exclude all attachables for now (and characters)

                        if obj is not living and not obj.type = attachable and
                            player not in obj and obj is not hidden and
                            ((verbosity ~= 1 and &obj.short_desc) or
                            (&obj.initial_desc and verbosity = 1)) and
                            obj is not already_printed
    #else
                        if obj is not living and player not in obj and
                        obj is not hidden and
                        ((verbosity ~= 1 and &obj.short_desc) or
                            (&obj.initial_desc and verbosity = 1)) and
                            obj is not already_printed
    #endif
                            {
                            need_carriage = true
                            break
                            }
                    }
                }

                case 5  ! objects without descs
                {
                    for obj in place
                    {
    #ifset USE_ATTACHABLES
                        ! Exclude all attachables for now (and characters)

                        if obj is not living and not obj.type = attachable and
                            player not in obj and obj is not hidden and
                            obj is not already_printed and
                            (not &obj.short_desc or (&obj.short_desc and verbosity = 1))
    #else
                        if obj is not living and player not in obj and
                        obj is not hidden and obj is not already_printed and
                        (not &obj.short_desc or (&obj.short_desc and verbosity = 1))
    #endif
                            {
                            need_carriage = true
                            break
                            }
                    }
                }

                case 6  ! attachables and scenery objects
                {
    #ifset USE_ATTACHABLES
                    for obj in place
                    {
                        ! Print attachables last
                        if obj.type = attachable and obj is not hidden
                        {
                            need_carriage = true
                            break
                        }
                    }
    #endif
                    for obj in place
                    {
                        if obj.type = scenery
                        {
                            if player not in obj and
                                (obj is open or obj is not openable)
                            {
                                local a
                                for a in obj
                                    {
                                    if a is not hidden
                                        {
                                        need_carriage = true
                                        break
                                        }
                                    }
                            }
                        }
                    }
                }

            if (FORMAT & DESCFORM_F)
                {
                if need_carriage and didprint
                    ""
                need_carriage = false
                }

            select DescribePlaceOrder[order]
                case 1 ! Contents of Parent
                {
                    ! List contents of chair, vehicle, etc. player is in
                    if player not in location
                    {
                        list_nest = 1
                        if WhatsIn(Parent(player))
                            didprint = true
                    }
                }
                case 2 ! List Characters with Descriptions
                {
                    ! List all characters, if any
                    count = 0
                    for obj in place
                    {
                        if obj is hidden or obj is not living or
                            player in obj
                        {
                            obj is already_listed
                        }
                        else
                        {
                            obj is not already_listed
                        }
                    }
                    for obj in place
                    {
                        if obj is not already_listed
                        {
                            print newline
                            if verbosity ~= 1 or (obj is not moved and &obj.initial_desc)
                                ShortDescribe(obj)
                            if obj is not already_listed
                                charcount++
                            else
                                {
                                didprint = true
                                obj is already_printed
                                }
                        }
                    }
    !               list_count = charcount
                }

                case 3   ! characters without short_desc's
                {
                    count = 0

                    if charcount ! list_count      ! if characters are to be listed
                    {
                        for obj in place
                        {
                            if obj is hidden or obj is not living or
                                player in obj or (&obj.short_desc and verbosity ~= 1) or
                                obj is already_printed
                            {
                                obj is already_listed
                            }
                            else
                            {
                                obj is not already_listed
                            }
                        }
                        list_count = charcount
                        tempformat = FORMAT
                        FORMAT = FORMAT | FIRSTCAPITAL_F | ISORAREHERE_F
                        FORMAT = FORMAT | USECHARNAMES_F
                        if (FORMAT & LIST_F)
                        {
                            FORMAT = FORMAT & ~LIST_F       ! clear it
                            FORMAT = FORMAT | TEMPLIST_F
                        }
                        Indent
                        list_nest = 0
                        ListObjects(place)
                        FORMAT = tempformat
                        didprint = true
                    }
                }
                case 4 ! List Objects with Descs
                {
                    for obj in place
                    {
                    count = 0
    #ifset USE_ATTACHABLES
                        ! Exclude all attachables for now (and characters)

                        if obj is living or obj.type = attachable or
                            player in obj or obj is already_printed
    #else
                        if obj is living or player in obj or obj is already_printed
    #endif
                            obj is already_listed
                        else
                            obj is not already_listed
                    }

                    for obj in place
                    {
    #ifset USE_PLURAL_OBJECTS
                        ! ...And don't list identical objects yet, either

                        if (obj.identical_to).type = identical_class
                        {
                            if obj is not hidden
                                count++
                        }
                        elseif player not in obj
    #else
                        if player not in obj
    #endif
                        {
                            if obj is not already_listed and
                                obj is not hidden
                            {
                                if verbosity ~= 1 or (verbosity = 1 and
                                (obj is not moved and &obj.initial_desc))
                                    ShortDescribe(obj)
                                if obj is not already_listed
                                    notlisted++
                                else
                                    {
                                    didprint = true
                                    obj is already_printed
                                    }
                            }
                        }
                    }
                }
                case 5 ! List Other Objects
                {
                    for obj in place
                    {
                    count = 0
    #ifset USE_ATTACHABLES
                        ! Exclude all attachables for now (and characters)

                        if obj is living or obj.type = attachable or
                            player in obj or (&obj.short_desc and verbosity ~= 1) or
                            obj is already_printed
    #else
                        if obj is living or player in obj or (&obj.short_desc and verbosity ~= 1) or obj is already_printed
    #endif
                            obj is already_listed
                        else
                            obj is not already_listed
                    }

                    if notlisted or count
                    {
                        list_count = notlisted + count
                        tempformat = FORMAT
                        FORMAT = FORMAT | FIRSTCAPITAL_F | ISORAREHERE_F
                        if FORMAT & LIST_F
                        {
                            FORMAT = FORMAT & ~LIST_F       ! clear it
                            FORMAT = FORMAT | TEMPLIST_F
                        }
                        Indent
                        list_nest = 0
                        ListObjects(place)
                        FORMAT = tempformat
                        didprint = true
                    }
                }
                case 6 ! List Attachables and Scenery
                {
    #ifclear NO_OBJLIB
    #ifset USE_ATTACHABLES
                    for obj in place
                    {
                        ! Print attachables last
                        if obj.type = attachable and obj is not hidden
                        {
                            ShortDescribe(obj)
                            if obj is not already_listed
                                Message(&DescribePlace, 2, obj)
                            else
                                didprint = true
                        }
                    }
    #endif
                    print newline
                    override_indent = false

                    ! Finally, list contents of scenery objects (unless we've
                    ! already done so as the parent of the player)
                    !
                    for obj in place
                    {
                        if obj.type = scenery
                        {
                            obj is known
                            if player not in obj and
                                (obj is open or obj is not openable)
                            {
                                list_nest = 1
                                WhatsIn(obj)
                            }
                        }

                        ! For scenery-derived objects that may change the type
                        elseif obj is static, hidden
                            obj is known
                    }
    #endif  ! ifclear NO_OBJLIB
                }

            order++
            }

            print newline
            need_newline = false

        }
    }
