---
title: AnyVerb
permalink: /guts/anyverb
categories: 
  - Hugo Guts
---

`AnyVerb` is a [hugolib.h](/library/hugolib.h/)
[routine](/routines/) that allows for trapping for any verb in a
location without also affecting xverbs (Save, Restore, etc.).

## Why it's needed

Imagine trying to code one of the dark rooms from Hitchhiker's Guide to
the Galaxy. One might have something like this (ok, no, they wouldn't):

    room dark_room "Darkness"
    {
       long_desc
          "You can see nothing, feel nothing, hear nothing, taste nothing, and are not entirely certain who you are."
       ! this is the room where the player must >SMELL
       before
          {
          location
             {
             if verboutine = &DoSmell
                 return false
             else
                 "You can see nothing, feel nothing, hear nothing, taste nothing, and are not entirely certain who you are."
             }
          }
       after
          {
          location DoSmell
             {
             "You smell smelling salts... yadda yadda."
             }
          }
    }

Great, right? No! When the player tries to SAVE, RESTORE, QUIT, or
RESTART, he or she will get that same damned line. We don't want that!
Instead, we'll use `AnyVerb`, like so:

    room dark_room "Darkness"
    {
       long_desc
          "You can see nothing, feel nothing, hear nothing, taste nothing, and are not entirely certain who you are."
       ! this is the room where the player must >SMELL
       before
          {
          AnyVerb(location)
             {
             if verboutine = &DoSmell
                 return false
             else
                 "You can see nothing, feel nothing, hear nothing, taste nothing, and are not entirely certain who you are."
             }
          }
       after
          {
          location DoSmell
             {
             "You smell smelling salts... yadda yadda."
             }
          }
    }

Now, the `before` [block](/definitions/block/) is only run if the command
is not an xverb. Right on!

## The code

    !----------------------------------------------------------------------------
    ! AnyVerb(obj)
    ! returns <obj> if the verbroutine global applies to a verb as opposed to
    ! an xverb; otherwise returns false

    routine AnyVerb(obj)
    {
    #ifclear NO_XVERBS
        if parser_data[VERB_IS_XVERB]
            return false
    #endif
        if obj
            return obj
        else
            return true
    }
