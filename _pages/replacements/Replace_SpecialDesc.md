---
title: Replace SpecialDesc
permalink: /replacements/specialdesc/
categories: 
  - Replacements
---

## Replacing SpecialDesc(obj)

[SpecialDesc](SpecialDesc) is a routine called by
[WhatsIn](WhatsIn) and [ListObjects](ListObjects).
It checks if objects have special
[initial_desc](Descriptions#initial_desc) or
[inv_desc](Inv_desc) property routines that preclude them
from normal object listing in room descriptions and inventories.
Occasionally, one might want to replace it to better organize how these
listings are handled.

### Separating worn items from the rest of the inventory

The default handling of clothing in an inventory response just adds
`(being worn)` after each worn item. Sometimes, one might prefer to have
a response like this:

>You are wearing a top hat and a monocle. You are also carrying a cane.

To do this, we could use the following replacement, which borrows code
from [ListObjects](ListObjects) to list worn items all neat-like:

    replace SpecialDesc(obj)
    {
        local a, c, flag, printed_blankline, count, t

        if FORMAT & LIST_F
            return

        list_count = 0

        for a in obj
        {
            if a is not hidden
                {
                c++
                flag = true
                }
            else
                flag = false

            if FORMAT & INVENTORY_F and obj = player and flag
            {
                if &a.inv_desc
                    Indent
                if a.inv_desc
                {
                    if FORMAT & LIST_F:  print newline
                    AddSpecialDesc(a)
                }
                if a is worn
                    {
                    if FORMAT & LIST_F:  print newline
                    AddSpecialDesc(a)
                    t++
                    }
            }

            elseif a is not moved and flag
            {
                if &a.initial_desc
                {
                    print newline
                    override_indent = false
                    if FORMAT & INVENTORY_F and FORMAT & NOINDENT_F and not printed_blankline
                        print ""
                    printed_blankline = true
                    Indent
                }
                if a.initial_desc
                    AddSpecialDesc(a)
            }
        }
            if t
            {
            if list_count > t
                print "Additionally, you are wearing";
            else
                print "You are wearing";
            for a in obj
                {
                if a is worn
                    {
                    ! May have a leading "is" or "are" that needs to
                    ! be printed at the head of the list

                    if FORMAT & ISORARE_F
                        {
                        if t = 1 and a is not plural
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

                    AssignPronoun(a)
                    if not (FORMAT & LIST_F)
                        {
                        if t > 2 and count
                            print ",";
                        if t > 1 and count = t - 1
                            print " "; AND_WORD;
                        if not (FORMAT & FIRSTCAPITAL_F)
                            print " ";
                        }
                    else
                        {
                        print to (list_nest * 2);   ! INDENT_SIZE);
                        }


                    ! Regular old non-plural, non-identical
                    ! objects get listed here:

                    if FORMAT & FIRSTCAPITAL_F
                        CArt(a)
                    else:  Art(a)

                FORMAT = FORMAT & ~FIRSTCAPITAL_F       ! clear it

                count++
            }

                }
            print ".";
            }

        ! if you want "you aren't carrying anything" to show up even when some items in the
        ! inventory have inv_desc properties, change the next line to
        ! if list_count = c
        if t = c
            {
            print AFTER_PERIOD;
            VMessage(&DoInventory)   ! "You aren't carrying anything."
            }
        list_count = c - list_count
    }
