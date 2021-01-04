---
title: ListObjects
permalink: /routines/listobjects/
categories: 
  - Routines
---

`ListObjects(object)` lists all the possessions of the specified object in the appropriate form (according to the global [FORMAT](/globals/format/).

Possessions of possessions are listed recursively if [FORMAT](/globals/format/) does not contain the `NORECURSE_F` bit.

Also calls: [WhatsIn](/routines/whatsin/)

>Inside the tub is the butcher, the baker, and the candlestick-maker.

In the above line, `ListObjects` provides "the butcher, the baker, and
the candlestick-maker." The text before that was determined by
[WhatsIn](/routines/whatsin/).

Check out the [FORMAT](/globals/format/) page for more listing options.

## The code

    !----------------------------------------------------------------------------
    ! ListObjects(object)
    ! lists all the objects in <object>, providing that the list_count global
    ! contains the total number of objects to be listed.

    routine ListObjects(thisobj)
    {
        local i, obj, count, pluralcount
        local templist_count            ! temporary total of unlisted objs.
        local id_count                  ! for identical (or plural) objects
    #ifset USE_PLURAL_OBJECTS
        local j, this_class
    #endif

        list_nest++
        for obj in thisobj
        {
            if obj is hidden
            {
                obj is already_listed
    #ifclear NO_OBJLIB
                if obj.type = scenery
                    obj is known
    #endif
            }
            else
                obj is known

    #ifset USE_PLURAL_OBJECTS

            ! Need to count identical (and possibly plural) objects
            ! for grouping in listing

            if obj.identical_to and obj is not already_listed
            {
                this_class = obj.identical_to
                if this_class.type = identical_class or
                    FORMAT & GROUPPLURALS_F
                {
                    id_count = 1
                    for (i=1; i<=this_class.#plural_of; i++)
                    {
                        j = this_class.plural_of #i
                        if j in thisobj and j~=obj and j is not hidden
                        {
                            id_count++
                            pluralcount++
                            list_count--
                            j is already_listed
                        }
                    }
                }
            }
    #endif
            if obj is not already_listed
            {
                ! May have a leading "is" or "are" that needs to
                ! be printed at the head of the list

                if FORMAT & ISORARE_F
                {
                    if list_count = 1 and id_count <= 1 and
                        obj is not plural
                    {
                        print " "; IS_WORD;
                    }
                    else
                    {
                        print " "; ARE_WORD;
                    }
                    if FORMAT & LIST_F
                        print ":"
                    FORMAT = FORMAT & ~ISORARE_F    ! clear it
                }

                need_newline = false
                if obj is plural
                    pluralcount++

                AssignPronoun(obj)
                if not (FORMAT & LIST_F)
                {
                    if list_count > 2 and count
                        print ",";
                    if list_count > 1 and count = list_count - 1
                        print " "; AND_WORD;
                    if not (FORMAT & FIRSTCAPITAL_F)
                        print " ";
                }
                else
                {
                    print to (list_nest * 2);   ! INDENT_SIZE);
                }

    #ifset USE_PLURAL_OBJECTS

                ! If a number of identical (or possibly plural)
                ! objects are grouped together, they are printed
                ! as a single entry in the list
                !
                if obj.identical_to and
                    (this_class.type = identical_class or
                    FORMAT & GROUPPLURALS_F)
                {
                    if id_count = 1
                    {
                        if FORMAT & FIRSTCAPITAL_F
                            CArt(obj)
                        else
                            Art(obj)
                    }
                    else
                    {
                        if FORMAT & FIRSTCAPITAL_F
                            print NumberWord(id_count, true);
                        else
                            print NumberWord(id_count);
                        print " "; this_class.name;

                        if this_class.type = plural_class
                        {
                            local k

                            if FORMAT & LIST_F
                                print ":";
                            else
                                print " (";

                            k = 0
                            for (i=1; i<=this_class.#plural_of; i++)
                            {
                                j = this_class.plural_of #i
                                if parent(j) = thisobj
                                {
                                    if not (FORMAT & LIST_F)
                                    {
                                        if id_count > 2 and k
                                            print ",";
                                        if k = id_count - 1
                                            print " "; AND_WORD;
                                        if k
                                            print " ";
                                    }
                                    else
                                    {
                                        print "\n";
                                        print to ((list_nest+1) * 2);   ! INDENT_SIZE);
                                    }
                                    Art(j)
                                    if not (FORMAT & NOPARENTHESES_F)
                                        ObjectIs(j)
                                    k++
                                }
                            }
                            if not (FORMAT & LIST_F):  print ")";
                        }
                    }
                }
                else
                {
    #endif
                    ! Regular old non-plural, non-identical
                    ! objects get listed here:

                    if FORMAT & FIRSTCAPITAL_F
                        CArt(obj)
                    else:  Art(obj)
                    if not (FORMAT & NOPARENTHESES_F)
                        ObjectIs(obj)
    #ifset USE_PLURAL_OBJECTS
                }
    #endif
                FORMAT = FORMAT & ~FIRSTCAPITAL_F       ! clear it

                count++
            }

            ! For itemized listings, list the children of
            ! each object immediately after that object (unless
            ! it is a SpecialDesc-printed description)

            if obj is not hidden and FORMAT & LIST_F
            {
                print newline
                if children(obj)
                {
                    if not obj.list_contents
                    {
                        templist_count = list_count
                        WhatsIn(obj)
                        list_count = templist_count
                    }
                }
            }
        }

        ! If not an itemized list, it is necessary to finish off the
        ! sentence, adding any necessary words at the end.  Then, the
        ! children of all previously objects listed at this level are
        ! listed.

        if not (FORMAT & LIST_F)
        {
            if count
            {
                if list_nest = 1 and FORMAT & ISORAREHERE_F
                {
                    if count + pluralcount > 1
                        print " "; ARE_WORD;
                    else:  print " "; IS_WORD;
                    print " "; HERE_WORD;
                    FORMAT = FORMAT & ~ISORAREHERE_F  ! clear it

                    if not (FORMAT&LIST_F or FORMAT&TEMPLIST_F)
                        override_indent = true
                }

                if not (FORMAT & NORECURSE_F)
                    print ".";
            }

            i = 0

            for obj in thisobj
            {
                if children(obj) and obj is not hidden and
                    (obj is not already_listed or
                        thisobj ~= location)
                {
                    if FORMAT & TEMPLIST_F
                    {
                        FORMAT = FORMAT | LIST_F & ~TEMPLIST_F
                        i = true
                        print newline
                    }

                    templist_count = list_count
                    WhatsIn(obj)
                    list_count = templist_count
                }
            }
        }

        if --list_nest = 0
        {
            if not (FORMAT & LIST_F) and not (FORMAT & NORECURSE_F)
            {
                print newline
                override_indent = false
                need_newline = false
            }
        }
    }
