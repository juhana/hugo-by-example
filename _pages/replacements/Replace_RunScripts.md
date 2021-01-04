---
title: Replace RunScripts
permalink: /replacements/runscripts/
categories: 
  - Replacements
---

### What it fixes

This version doesn't *fix* anything, but it attempts to make
[RunScripts](RunScripts) a little more flexible. This version
allows for character scripts that pass a true (1) value for the
parameter. Previously, `RunScripts` would interpret this as the [display
object](Display).

### The code

    replace RunScripts
    {

    #ifclear NO_SCRIPTS

        local a, obj, step, total, routine, b
        local tempactor, tempverb, tempobject

        for (; a<number_scripts; a++)
        {
            obj = scriptdata[a * 3]         ! this object/character
            step = scriptdata[a * 3 + 1]    ! current step
            total = scriptdata[a * 3 + 2]   ! total steps in script

            if obj and total < 0            ! if skipping this script
                scriptdata[a * 3 + 2] = scriptdata[a * 3 + 2] + 32767

            elseif obj and step < total and step >= 0
            {
                ! action
                routine = setscript[a * MAX_SCRIPT_STEPS + step * 2]

                ! object being acted upon
                b = setscript[a * MAX_SCRIPT_STEPS + step * 2 + 1]

    #ifset DEBUG
                if debug_flags & D_SCRIPTS
                {
                    print "[Script for obj. ";
                    print number obj; " ("; obj.name; "), step ";
                    print number (step + 1); ":  $"; \
                    hex routine; ", obj. ";
                    print number b; " ("; b.name; ")]"
                }
    #endif

                scriptdata[a * 3 + 1] = step + 1
                tempactor = actor
                tempverb = verbroutine
                tempobject = object
                actor = obj
                verbroutine = routine
                object = b
                if not parent(actor).before
                {
                    if not actor.before
                    {
                        if not object.before or object = 1
                        {
                            call routine(obj, b)
                            run actor.after
                        }
                    }
                }
                if actor in location:  actor is known
                actor = tempactor
                verbroutine = tempverb
                object = tempobject
            }
            elseif step >= 0
            {
                scriptdata[a * 3] = 0   ! clear this object's script
                if a = number_scripts - 1
                    number_scripts--
            }
        }

    #endif  ! ifclear NO_SCRIPTS

    }
