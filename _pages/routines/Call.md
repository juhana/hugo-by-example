---
title: Call
permalink: /routines/call/
categories: 
  - Routines
---

Occasionally, you'll write a [routine](routine) that uses
other routines as its [arguments](arguments). Take, for
instance, the `SortArray` routine from [Sort.h](Sort.h) uses
other routines to provide the "rules" for how an array should be sorted:

    routine SortArray(data, num, comp_routine)
    {
        local i
        local did_swap

        for (i = 0; i < num; i = i + 1)
        {
            local j
            did_swap = false
            for (j = num - 1; j > i; j = j - 1)
            {
                local swap
                swap = call comp_routine(array data[j-1], array data[j])
                if swap
                {
                    local tmp
                    tmp = array data[j]
                    array data[j] = array data[j-1]
                    array data[j-1] = tmp
                    did_swap = true
                }
            }
            ! if we didn't swap any elements, then the array is sorted
            if not did_swap : return
        }
    }

`comp_routine`, in the above, is the sorting routine, and we have to
execute it to determine whether or not we need to swap. To execute it by
its argument name, we have to preface it with "call" (just like an array
routine argument has to be prefaced with "array").

As implied by the Hugo Book description, `call` would also be necessary
if the applicable routine address was in the form of a [global
variable](global) or [object property](property).
