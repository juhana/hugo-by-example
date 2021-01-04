---
title: Scripts
permalink: /characters/scripts/
categories: 
  - Characters
---

A character script is an array that dictates the sequence of actions
that a NPC (non-playable character) will take. Hugo's character scripts
are of the old school design; the NPC follows the script exactly, almost
completely unaffected by the player's actions. Kent Tessman himself says
he would now design a different approach. That said, the old system
still is useful for specific situations and- compared to other character
scripting approaches in Hugo- it has the advantage of being already
written. 

### setscript

All we have to do to get a script going is to fill the
[hugolib.h](Hugolib.h)-defined `setscript` array, using the
`Script` routine and a bunch of "[character
routines](#Character_Routines)" (we'll get to that later).

| calling form                                                                                        | description                                                                                       |
|-----------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------|
| `setscript[Script(`**`character`` ``object`**`,`**`number`` ``of`` ``steps`` ``in`` ``script`**`)]` | `Script` fills the array element with the character routine and returns the number of the element |

In the following code:

    setscript[Script(magician, 1)] = &CharTakeABow, 0 ! &CharTakeABow is a fictional routine

`Script(magician,1)` would return 0, giving us **setscript\[0\]**, just
as we would use if were filling a one-element array.

The Hugo Book's example is longer:

    setscript[Script(ned, 5)] = &CharMove, s_obj,
                                &CharGet, cannonball,
                                &CharMove, n_obj,
                                &CharWait, 0,
                                &CharDrop, cannonball

A single script may have up to 32 steps.
Once declared, a character script will run *immediately* (well, as soon
as [main](Main) is run next, as it calls the `RunScripts`
routine). If we want to pause or delay scripts, we must use [script
management routines](Scripts#Script_Management_Routines).

### Character Routines

You can't just fill a character script like any old verb routine like
`DoSmell`, as those have been written with the player character in mind.
You need to use "character routines" instead.
[Hugolib.h](Hugolib.h) comes with several already written.
Here is one:

    !----------------------------------------------------------------------------
    ! CharGet
    ! Script usage:  &CharGet, <object>

    routine CharGet(char, obj)
    {
        if FindObject(obj, parent(char)) = 1
        {
            if Acquire(char, obj)
            {
                if char in location
                {
                    Message(&CharGet, 1, char, obj) ! "[The character] picks up [the object]."
                    event_flag = true
                }
            }
            return true
        }
    }

If the player is in the same location as the character picking something
up, we get a message letting us know that he or she picked it up.

The [hugolib.h](Hugolib.h)-defined character routines, in
their entirety:

| character routine | object requirement                            |
|-------------------|-----------------------------------------------|
| CharMove          | needs a direction object (u_to, e_to, etc.) |
| CharWait          | uses `nothing` object                         |
| CharGet           | requires takeable object                      |
| CharDrop          | requires object held by character             |
| LoopScript        | uses `nothing` object                         |

`LoopScript` is a special routine that causes the script to loop
indefinitely. This is used by the bum in the game "Spur" who stumbles
around town in an endless loop.

## Script Management Routines

Once started, we *do* have the means to interrupt character scripts.

| script management routine | description                                                                            |
|---------------------------|----------------------------------------------------------------------------------------|
| CancelScript(<obj>)       | Immediately cancels the script for <obj>                                               |
| FindScript(<obj>)         | Useful (**undocumented**!) routine that returns true if <obj> has a script in progress |
| PauseScript(<obj>)        | Pauses script for object <obj>                                                         |
| ResumeScript(<obj>)       | Resumes paused script for object <obj>                                                 |
| SkipScript(<obj>)         | Skips the script for object <obj> for the next call to `RunScripts` only               |

### Polite Characters!

Imagine a game where NPCs stop what they are doing when you talk to
them. Using the aforementioned script management routines, how would you
have your game do that? (HINT: Take a look at the `FindScript` routine
in [hugolib.h](Hugolib.h) and see how the other script
routines call it)
<spoiler text = "[Click for answer]"> Looking at `FindScript`, we see
that it checks to see if there are scripts associated with an object. If
there are none, it returns the number equal to the constant
MAX_SCRIPTS. We can use this to check to see if there are any scripts
associated with the `speaking` global variable.

Then it's a simple case of [main](Main) routine maneuvering:

    routine main
    {
            counter = counter + 1
            PrintStatusLine
            run location.each_turn
            runevents
            ! we move the speaking check *before* RunScripts so we have
            ! an accurate idea of whether we are still talking to anyone
            if speaking not in location
            speaking = 0
            ! if we are talking to a character *and* that character has
            ! scripts, we will skip that script for now
        if speaking and FindScript(speaking) ~= MAX_SCRIPTS
            SkipScript(speaking)
        RunScripts
    }

</spoiler>

## Character Overrides

Using the `before` property, we can change the execution of a character
routine, just like any other verb routine.

    character giantslug "giant slug"
    {
    article "the"
    adjective "giant"
    noun "slug"
    before
         {
         actor CharGet
             {
             if Contains(location,self)
                  {
                  print "\nThe slug looks at "; Art(object) " glumly, as it has no arms."
                  }
             }
         }
    }

Of course, if you are only changing the *flavor* of the descriptive
text, your replacement code will have to have all of the functionality
of the original routine (check to make sure the object is in scope,
etc.).
