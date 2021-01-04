---
title: Replace ShortDescribe
permalink: /replacements/shortdescribe/
categories: 
  - Replacements
---

### What it fixes

1.  Removes the [jump](guts/jump/) command.
2.  In [SUPERBRIEF](globals/verbosity/) mode, even objects with
    [short_desc](properties/descriptions/) properties are treated like
    they don't have them.

### The code

    replace ShortDescribe(obj)
    {
        local ListContents
        obj is known

        if list_nest = 1
            print newline

        AssignPronoun(obj)

        if obj is not moved and &obj.initial_desc
        {
            Indent
            run obj.initial_desc
            ListContents = true
        }
        elseif obj is openable
        {
            if obj is open
            {
                if &obj.when_open
                {
                    Indent
                    run obj.when_open
                    ListContents = true
                }
            }
            elseif &obj.when_closed
            {
                Indent
                run obj.when_closed
                ListContents = true
            }
        }

        if (not ListContents)
            {
                    if verbosity = 1
                        return

            if &obj.short_desc
                Indent

            if not obj.short_desc
                return
            }

    !  "ListContents" section
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
