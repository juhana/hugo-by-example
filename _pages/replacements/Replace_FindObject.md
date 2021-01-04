---
title: Replace FindObject
permalink: /replacements/findobject/
categories: 
  - Replacements
---

### What it fixes

1.  Removes the [jump](/guts/jump/) command for easier replacing.
    I've never had to [replace](/guts/replace/)
    [FindObject](/scope/findobject/), though.

### The code

    replace FindObject(obj, objloc, recurse)
    {
        local a, p
        local this_parse_rank
        local found_result = true
        local FindObjectIsFound

        if obj = nothing or obj = player
        {
            if obj = nothing and not recurse
            {
    #ifset DEBUG
                if debug_flags & D_FINDOBJECT
                {
                    print "[Resetting FindObject]"
                }
                if debug_flags & D_PARSE_RANK
                {
                    print "[parser_data[BEST_PARSE_RANK] = 0]"
                }
    #endif
                parser_data[BEST_PARSE_RANK] = 0
                parser_data[PARSE_RANK_TESTS] = 0
                parser_data[PARSER_STATUS] &= ~FINDOBJECT_KNOWN
                parser_data[PARSER_STATUS] &= ~FINDOBJECT_NONLIVING
            }
            elseif obj = player
            {
                this_parse_rank = obj.parse_rank
                if this_parse_rank > parser_data[BEST_PARSE_RANK]
                    parser_data[BEST_PARSE_RANK] = this_parse_rank
            }

            ! nothing and player are always available
            obj is known
            return true
        }

    #ifclear NO_FUSES
        if obj.type = fuse or obj.type = daemon
        {
            ! Optimize checking of simple fuses and daemons:
            if obj.#in_scope = 1 and not &obj.in_scope and not obj.#found_in and not &obj.found_in
            {
                if obj is active and obj.in_scope = player
                    return true
                else
                    return false
            }
        }
    #endif

        ! Do some parse_rank tweaking to rank lower objects which (probably) don't
        ! apply to a particular command, like trying to open something that's
        ! already open:
        this_parse_rank = obj.parse_rank

        ! And be ready to prefer the last specifically referred to object in
        ! the event of disambiguation
        if obj = parser_data[LAST_SINGLE_OBJECT]
            this_parse_rank++

    #ifclear NO_VERBS
        select verbroutine
        case &DoOpen
        {
            if obj is openable and obj is open
                this_parse_rank--
        }
        case &DoClose
        {
            if obj is openable and obj is not open
                this_parse_rank--
        }
        case &DoSwitchOn
        {
            if obj is switchable and obj is switchedon
                this_parse_rank--
        }
        case &DoSwitchOff
        {
            if obj is switchable and obj is not switchedon
                this_parse_rank--
        }
        case &DoWear
        {
            if obj is clothing and obj is worn
                this_parse_rank--
        }
        case &DoTakeOff
        {
            if obj is clothing and obj is not worn
                this_parse_rank--
        }
    #endif  ! #ifclear NO_VERBS

    #ifset USE_CHECKHELD
        if checkheld is active
        {
            if checkheld is plural      ! >DROP ALL, etc. ...
            {
                if (verbroutine = &DoDrop_CheckHeld, &DoPutonGround_CheckHeld) or
                    (verbroutine = &DoPutIn_CheckHeld and xobject)
                {
                    if obj is not checkheld_flag
                    {
    #ifset DEBUG
                        if debug_flags & D_FINDOBJECT
                        {
                            print "[FindObject("; obj.name; " ["; number obj; "], "; \
                                objloc.name; " ["; number objloc; "]):  "; \
                                "false (not checkheld_flag)]"
                        }
    #endif
                        return false
                    }
                }
            }
            elseif obj is checkheld_flag    ! ...or >DROP OBJECT, etc.
            {
                if (verbroutine = &DoDrop_CheckHeld, &DoPutonGround_CheckHeld) or
                    (verbroutine = &DoPutIn_CheckHeld and xobject)
                {
                    this_parse_rank += 100
                }
            }
        }
    #endif  ! USE_CHECKHELD

        ! The objloc argument is equal to 0 if a) the grammar token is
        ! "anything", or b) the engine is re-testing object availability
        ! given the setting of parser_data[BEST_PARSE_RANK] during the first
        ! pass of object disambiguation.

        if objloc = 0
        {
    #ifclear NO_VERBS
            if verbroutine = &DoGet and not recurse
            {
                if obj in player
                {
    #ifset DEBUG
                    if debug_flags & D_FINDOBJECT
                    {
                        print "[FindObject("; obj.name; " ["; number obj; "], "; \
                            objloc.name; " ["; number objloc; "]):  "; \
                            "false (object in player)]"
                    }
    #endif
                    return false
                }
            }
    #endif
            if location
            {
                if FindObject(obj, location, true)
                    object is known
            }

            if not ObjectIsKnown(obj)
            {
    #ifset DEBUG
                if debug_flags & D_FINDOBJECT and not recurse
                {
                    print "[FindObject("; obj.name; " ["; number obj; "], "; \
                        objloc.name; " ["; number objloc; "]):  "; \
                        "false (object not 'known')]"
                }
    #endif
                return false
            }

            if not recurse
            {
                if parser_data[PARSE_RANK_TESTS]++ = 0
                {
    #ifset DEBUG
                    if debug_flags & D_FINDOBJECT and not recurse
                    {
                        print "[FindObject("; obj.name; " ["; number obj; "], "; \
                            objloc.name; " ["; number objloc; "]):  "; \
                            "true]"
                    }
                    if debug_flags & D_PARSE_RANK and this_parse_rank > parser_data[BEST_PARSE_RANK]
                    {
                        print "[parser_data[BEST_PARSE_RANK] = "; number this_parse_rank; "]"
                    }
    #endif
                    parser_data[BEST_PARSE_RANK] = this_parse_rank
                    return true
                }

                if this_parse_rank < parser_data[BEST_PARSE_RANK]
                {
    #ifset DEBUG
                    if debug_flags & D_FINDOBJECT and not recurse
                    {
                        print "[FindObject("; obj.name; " ["; number obj; "], "; \
                            objloc.name; " ["; number objloc; "]):  "; \
                            "false (this_parse_rank = "; number this_parse_rank; \
                            " < parser_data[BEST_PARSE_RANK] = "; number parser_data[BEST_PARSE_RANK]; ")]"
                    }
    #endif
                    return false
                }
                else
                {
    #ifset DEBUG
                    if debug_flags & D_PARSE_RANK and this_parse_rank > parser_data[BEST_PARSE_RANK]
                    {
                        print "[parser_data[BEST_PARSE_RANK] = "; number this_parse_rank; "]"
                    }
    #endif
                    parser_data[BEST_PARSE_RANK] = this_parse_rank
                }
            }

    #ifset DEBUG
            if debug_flags & D_FINDOBJECT and not recurse
            {
                print "[FindObject("; obj.name; " ["; number obj; "], "; \
                    objloc.name; " ["; number objloc; "]):  "; \
                    "true]"
            }
    #endif
            return true
        }

        if word[2] = "~all" or word[3] = "~all" and not recurse
        {
            if not IsPossibleXobject(obj) or (xobject and xobject ~= obj)
            {
                a = obj.exclude_from_all
                if a < 2
                {
                    if a or ExcludeFromAll(obj) = true
                    {
    #ifset DEBUG
                        if debug_flags & D_FINDOBJECT and not recurse
                        {
                            print "[FindObject("; obj.name; " ["; number obj; "], "; \
                                objloc.name; " ["; number objloc; "]):  "; \
                                "false (excluded from \"all\")]"
                        }
    #endif
                        return false
                    }
                }
            }
        }

        if obj is not living
            parser_data[PARSER_STATUS] |= FINDOBJECT_NONLIVING

        p = parent(obj)

        ! If any object FindObject is attempting to disambiguate
        ! is known, make a note of it (if during the parsing phase)
        if parser_data[PARSER_STATUS] & PARSER_ACTIVE
        {
            if ObjectisKnown(obj)
                parser_data[PARSER_STATUS] |= FINDOBJECT_KNOWN
        }

        if obj = objloc or
            (player in obj and obj ~= objloc and (obj~=location or not recurse)) or
            p = obj or p = objloc or p = player
        {
            obj is known
            FindObjectIsFound = true
        }
        elseif (p is not openable or p is platform) and p is not quiet and
            p ~= nothing
        {
            if FindObject(p, objloc, true) and ObjectisKnown(p)
            {
                obj is known
                FindObjectIsFound = true
            }
        }
        elseif p is openable and p is open and p is not quiet and
            p ~= nothing
        {
            if FindObject(p, objloc, true) and ObjectisKnown(p)
            {
                obj is known
                FindObjectIsFound = true
            }
        }
        elseif (p is openable, not open, transparent, not quiet) and
            p ~= nothing
        {
            if FindObject(p, objloc, true) and ObjectisKnown(p)
            {
                obj is known
                found_result = 2
                FindObjectIsFound = true
            }
        }

        if obj.#found_in and not FindObjectIsFound
        {
            for (a=1; a<=obj.#found_in; a++)
            {
                if obj.found_in #a and (obj.found_in #a = objloc or
                    FindObject(obj.found_in #a, objloc, true))
                {
                    obj is known
                    FindObjectIsFound = true
                }
            }
        }

        if obj.#in_scope and not FindObjectIsFound
        {
            for (a=1; a<=obj.#in_scope; a++)
            {
                if obj.in_scope #a
                {
                    if obj.in_scope #a=objloc or obj.in_scope #a=actor
                    {
                        obj is known
                        FindObjectIsFound = true
                    }
                    if FindObject(obj.in_scope #a, objloc, true)
                    {
                        obj is known
                        FindObjectIsFound = true
                    }
                }
            }
        }

        if not FindObjectIsFound
        {
    #ifset DEBUG
            if debug_flags & D_FINDOBJECT and not recurse
            {
                if obj.type ~= fuse and obj.type ~= daemon
                {
                    print "[FindObject("; obj.name; " ["; number obj; "], "; \
                        objloc.name; " ["; number objloc; "]):  "; \
                        "false]"
                }
            }
    #endif
            return false
        }

    ! FindObjectIsFound area
        if not recurse
        {
            if parser_data[PARSE_RANK_TESTS]++ = 0
            {
    #ifset DEBUG
                if debug_flags & D_PARSE_RANK and this_parse_rank > parser_data[BEST_PARSE_RANK]
                {
                    print "[parser_data[BEST_PARSE_RANK] = "; number this_parse_rank; "]"
                }
    #endif
                parser_data[BEST_PARSE_RANK] = this_parse_rank
            }
            elseif this_parse_rank > parser_data[BEST_PARSE_RANK]
            {
    #ifset DEBUG
                if debug_flags & D_PARSE_RANK and this_parse_rank > parser_data[BEST_PARSE_RANK]
                {
                    print "[parser_data[BEST_PARSE_RANK] = "; number this_parse_rank; "]"
                }
    #endif
                parser_data[BEST_PARSE_RANK] = this_parse_rank
            }
        }
    #ifset DEBUG
        if debug_flags & D_FINDOBJECT and not recurse
        {
            print "[FindObject("; obj.name; " ["; number obj; "], "; \
                objloc.name; " ["; number objloc; "]):  "; \
                "true]"
        }
    #endif
        return found_result
    }
