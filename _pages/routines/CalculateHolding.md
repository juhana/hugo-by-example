---
title: CalculateHolding
permalink: /routines/calculateholding/
categories: 
  - Routines
---

`CalculateHolding` is a [hugolib.h](library/hugolib.h/)
[routine](routines/) used by [Acquire](guts/acquire) to
determine how much a [container](attributes/container/) is already
holding (which then determines if it can receive anything else). This is
one of the reasons that Hugo prefers that every container has
[holding](properties/holding/) (which can just be "0", as
`CalculateHolding` will rewrite it) and [capacity](properties/capacity/)
[properties](properties/).

## The code

    !----------------------------------------------------------------------------
    ! CalculateHolding(object)
    ! recalculates the correct holding property for an object; used before
    ! adding or subtracting children

    routine CalculateHolding(obj)
    {
        local i

        obj.holding = 0
        for i in obj
        {
            if i is not worn or obj ~= player
                obj.holding = obj.holding + i.size
        }
    }
