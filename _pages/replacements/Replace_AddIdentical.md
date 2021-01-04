---
title: Replace AddIdentical
permalink: /replacements/addidentical/
categories: 
  - Replacements
---

### What it fixes

The original just has a typo in the [for](/loops/for/) loop.

### The code

    replace AddIdentical(obj, i)
    {
        local j

        for (j=1; j<=i.#plural_of; j++)
        {
            if i.plural_of #j = 0           ! a blank slot
            {
                i.plural_of #j = obj    ! add it
                return j
            }
        }
        return false
    }
