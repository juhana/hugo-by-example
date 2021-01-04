---
title: Replace CalculateHolding
permalink: /replacements/calculateholding/
categories: 
  - Replacements
---

### What it fixes

[CalculateHolding](routines/calculateholding/) doesn't count
[worn](attributes/worn/) objects against a player's
[capacity](properties/capacity/). Since the [mobile](attributes/mobile/)
[attribute](attributes/) is [aliased](basics/alias/) to
`worn`, in the rare instances that an object is `mobile` *and* can be
picked up, those items are not being counted towards player (and
container) capacities. This fixes that.

### The code

    replace CalculateHolding(obj)
    {
        local i

        obj.holding = 0
        for i in obj
        {
            if i is not worn or i is not clothing and obj ~= player
                obj.holding = obj.holding + i.size
        }
    }
