---
title: verbroutine
permalink: /globals/verbroutine/
categories: 
  - Global Variables
---


After the player's input, the Hugo engine compares it against the game's
declared [grammar](basics/grammar/). If it finds a match, the address
of the associated verb routine is stored in the 
[global variable](basics/global/) `verbroutine` before
going on to execute the various [before routines](loops/game-loop/)
and the verb routine itself. `verbroutine` is useful for many things.

Specifically, `verbroutine` is set (or reset) after
[PreParse](parsing/preparse/) but *before*
[Perform](routines/perform/) is called by the engine. While `PreParse`
is executed, `verbroutine` still equals its value from the previous
turn. 

### Checking the current verbroutine

Object properties like [react_before](properties/react_before/) and
[react_before](properties/react_before/) need to use `verbroutine` to
work properly, but the same thing can be applied to
[events](timers/events/) and other things.

For instance, exit-checking routines will often print whatever text is
within a room's direction properties, much to your chagrin. You can get
around this with code like this:

    room desertroom1 "In The Desert"
    {
        s_to  {
              if verbroutine = &DoGo ! the next line will only run if the player actually typed >GO SOUTH
                  "Blinking your eyes against the whirling sandstorm, you trudge southward until you reach the..."
              return desertoasis
              }
    }

### Character Orders

[order_response](property/order_response/) can use `verbroutine` to
organize how the character should respond to several commands.

        ! from Kent Tessman's Spur
        order_response
        {
            select verbroutine
            case &DoGo
                "Old Dan is probably perfectly capable of figuring
                out on his own which way to swagger."
                    ! ...

### Redirection

Sometimes, interactions with objects should be redirected to another
object. Look how Future Boy's redirection 
[object class](basics/object_classes/) uses it with the
[Perform](routines/perform/) routine:

    class reflector_object
    {
        real_object <object directions should be redirected to>
        found_in
            return parent(self.real_object)
        before
        {
            object
            {
                Perform(verbroutine, self.real_object, xobject)
            }
            xobject
            {
                Perform(verbroutine, object, self.real_object)
            }
        }
        parse_rank
            return self.real_object.parse_rank - 1
    }

### Clearing verbroutine

Lastly, very rarely, you may want to clear the `verbroutine`. This
[DoListen replacement](replacements/dolisten/) clears the variable
to avoid executing `after` routines.
