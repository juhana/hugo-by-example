---
title: ExcludeFromAll
permalink: /routines/excludefromall/
categories: 
  - Routines
---

| calling form             | description                                                                                                                                                                                                                            |
|--------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `ExcludeFromAll(object)` | Returns true if, based on the current circumstances (verbroutine, etc.), the supplied object should be excluded from actions using “all”—such as `multi`, `multiheld`, and `multinotheld` [grammar tokens](Grammar_Tokens). |

## The Code

    !----------------------------------------------------------------------------
    ! ExcludeFromAll(obj)
    ! If global decision rules are desired for "all" actions, replace
    ! ExcludeFromAll, returning true if <obj> is to be excluded.  Return 2 to
    ! force the INCLUSION of <obj>.

    routine ExcludeFromAll(obj)
    {
        if obj is hidden
            return true
        return false
    }

## Replacement Example

Future Boy! replaces `ExcludeFromAll` with some added code to handle
objects carried by NPCs:

    replace ExcludeFromAll(obj)
    {
        if obj is hidden
            return true

    ! Exclude things NPCs are carrying unless the NPC is explicitly
    ! given as the parent
    if parent(obj) is living
    {
        if IsPossibleXobject(parent(obj)) or parent(obj) = player
            return false
        return true
    }

        return false
    }
