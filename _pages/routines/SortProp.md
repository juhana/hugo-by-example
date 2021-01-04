---
title: SortProp
permalink: /routines/sortprop/
categories: 
  - Routines
---

`SortProp` is a routine based on [Sort.h](contributions/sort.h/), altered to
work with object properties. One would use it with the same sorting
routines.

### The routine

    routine SortProp(obj, prp, comp_routine)
    {
        local i
        local did_swap

        for (i = 1; i <= obj.#prp; i = i + 1)
        {
            local j
            did_swap = false
            for (j = obj.#prp ; j > i; j = j - 1)
            {
                local swap
                swap = call comp_routine(obj.prp #(j-1), obj.prp #j)
                if swap
                {
                    local tmp
                    tmp = obj.prp #j
                    obj.prp #j = obj.prp #(j-1)
                    obj.prp #(j-1) = tmp
                    did_swap = true
                }
            }
            ! if we didn't swap any elements, then the array is sorted
            if not did_swap : return
        }
    }
