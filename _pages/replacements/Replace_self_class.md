---
title: Replace self_class
permalink: /replacements/self_class/
categories: 
  - Replacements
---

### What it fixes

In a room with 2 (male) NPCs, after a command involving one (setting
him_obj to that object), ASK OTHER GUY ABOUT HIMSELF acts like you were
asking about the first guy. This fixes that.

### The code

    replace self_class
    {
        type self_class
        before
        {
            object
            {
                Perform(verbroutine, self.self_object, xobject)
            }
            xobject
            {
                if object > themselves
                {
                    ! Rule out numbers used as xobjects:
                    local i
                    for (i=words; i>2; i--)
                    {
                        if word[i] <= 0 or StringToNumber(word[i]) = xobject
                        {
                            return false
                        }
                    }

                    if not self.self_resolve
                    {
                        OMessage(self_class, 1)
                    }
                    else
                    {
                                    !       (the old code)
                    !   Perform(verbroutine, object, self.self_object)
                    Perform(verbroutine, object, object)
                    }
                }
                else
                    return false
            }
        }
        is known
    }
