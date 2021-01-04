---
title: Replace CalculateHolding
permalink: /replacements/calculateholding/
categories: 
  - Replacements
---

### What it fixes

[CalculateHolding](CalculateHolding) doesn't count
[worn](worn) objects against a player's
[capacity](capacity). Since the [mobile](mobile)
[attribute](attribute) is [aliased](alias) to
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
