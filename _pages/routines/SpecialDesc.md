---
title: SpecialDesc
permalink: /routines/specialdesc/
categories: 
  - Routines
---

SpecialDesc(obj) is called by [WhatsIn](/routines/whatsin/) and
[ListObjects](/routines/listobjects/). It checks if objects have special
[initial_desc](/properties/descriptions/) or
[inv_desc](/properties/inv_desc/) property routines that preclude them
from normal object listing in room descriptions and inventories (those
routines then proceed to list everything else).

## The original code

    !----------------------------------------------------------------------------
    ! SpecialDesc(object)
    ! checks the children of <object> and runs any applicable preliminary
    ! descriptions; returns the total number of remaining (i.e. non-listed)
    ! objects in the list_count global variable

    routine SpecialDesc(obj)
    {
        local a, c, flag, printed_blankline

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
        list_count = c - list_count
    }

    routine AddSpecialDesc(a)
    {
        a is already_listed
        a is known
        list_count++
        AssignPronoun(a)
    }

As you can see, in applicable cases, an object's
[initial_desc](/properties/descriptions/) or
[inv_desc](/properties/inv_desc/) property is executed if present, and
then `AddSpecialDesc` is called, which gives the object the
`already_listed` global so it is not listed again with the rest of the
inventory/container listing/whatever.

## See Also

Check out the [SpecialDesc replacements page](/replacements/specialdesc/) for more info.
