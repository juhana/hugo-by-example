---
title: ShortDescribe
permalink: /routines/shortdescribe/
categories: 
  - Routines
---

`ShortDescribe` is the [hugolib.h](library/hugolib.h/) routine (called
by [DescribePlace](guts/describeplace/)) that checks if an object
has an [initial_desc](properties/descriptions/#initial_desc),
[when_open](properties/descriptions/),
[when_closed](properties/descriptions/), or
[short_desc](properties/descriptions/) property that should be used. If
so, it prints it. If not, it returns false, and `DescribePlace` will go
on to put the object in the regular room listing.

*See also:* [Replace ShortDescribe](replacements/shortdescribe/)

## The code

    !----------------------------------------------------------------------------
    ! ShortDescribe(object)
    ! prints the initial description of <object> if not moved (if it has one),
    ! or the when_open or when_closed message, if applicable, or the short
    ! description if moved (if it has one).

    routine ShortDescribe(obj)
    {
        obj is known

        if list_nest = 1
            print newline

        AssignPronoun(obj)

        if obj is not moved and &obj.initial_desc
        {
            Indent
            run obj.initial_desc
            jump CheckContents
        }

        if obj is openable
        {
            if obj is open
            {
                if &obj.when_open
                {
                    Indent
                    run obj.when_open
                    jump CheckContents
                }
            }
            elseif &obj.when_closed
            {
                Indent
                run obj.when_closed
                jump CheckContents
            }
        }

        if &obj.short_desc
            Indent

        if not obj.short_desc
            return

    :CheckContents

        obj is already_listed
        AssignPronoun(obj)

        list_count = 0
        if children(obj) > 0 and (obj is not container or
            (obj is container and obj is not openable) or
            (obj is container and obj is openable and
                (obj is open or obj is transparent))) and
            obj is not quiet
        {
            list_nest = 1
            WhatsIn(obj)
        }

        ! If INDENT_SIZE is 0, formatting may be thrown off when listing
        ! the contents of an object:
        if INDENT_SIZE = 0:  need_newline = true

        if need_newline:  print newline
    }
