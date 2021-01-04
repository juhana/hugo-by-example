---
title: AssignPronoun
permalink: /parsing/assignpronoun/
categories: 
  - Parsing
  - Routines
---

Since Zork, players have had the luxury of referring to objects and
characters as "it"'s, "her"'s, and "him"'s. In Hugo, the parser normally
assigns pronouns to the last object the player has interacted with. If
one doesn't exist, it may be assigned to the last object listed in a
room. The AssignPronoun routine gives the author some control over
pronouns, but it is trickier than one would initially assume!

The manual says this:

| calling form            | description                                                                                          |
|-------------------------|------------------------------------------------------------------------------------------------------|
| `AssignPronoun(object)` | Sets the appropriate global (`it_obj`, `them_obj`, `him_obj`, or `her_obj`) to the specified object. |

### Simpler Usage (Room Descriptions)

Let's start off with an example where we have an object in a room
description that we specifically want the player to interact with. For
reasons of readability, the following room and object are coded
intentionally sparsely:

    room STARTLOCATION "Start Location"
    {}

    object hat "top hat"
    {
        noun "hat"
            adjective "top"
            article "the"
        short_desc {
               "A top hat sits in the center of the room, demanding your attention."
               AssignPronoun(hat)
               parser_data[PARSER_STATUS] = PRONOUNS_SET
               }
        is container, clothing
        in STARTLOCATION
    }

    object couch "couch"
    {
            noun "couch"
            in STARTLOCATION
    }

This gives us:

>Start Location  
>A top hat sits in the center of the room, demanding your attention.  
>Couch is here.
>
>&gt;x it  
>(assuming you mean the top hat)  
>The top hat looks just like you would expect.

An important bit in the code about is the line that reads
**`parser_data[PARSER_STATUS]`` ``=`` ``PRONOUNS_SET`**. DescribePlace
calls routines that call AssignPronoun for every object in the room.
This might negate any AssignPronoun we set.
**`parser_data[PARSER_STATUS]`` ``=`` ``PRONOUNS_SET`** locks the
current pronoun in until the end of the turn (the parser flags are
automatically reset at the beginning of each cycle).

Now, that would be great if that's all it took for every case, but no,
sometimes there are some other steps. This is why we drink.

### More Complex Usage (Changing Pronouns Mid-Action)

Occasionally, you might want to have interaction with one object bring
the player's attention to another. So, searching a couch rewards the
player with some change, and you want typing &gt;COUNT IT next to
correctly refer to the change. Other times, instead of coding one
conditional-filled object, you might want to swap in and out several
simpler objects at opportune moments.

If we do all of this object-and-pronoun-switching in a `before` or
`after` routine, though, there are some complications.
[Perform](/routines/perform/), at its end, automatically resets the
[object](/globals/object/) global variable to
whatever it was in the beginning (which will still be the first item).
On the next turn, [Parse](/routines/parse/) gets a little too excited if
an `object` value exists. The offending code is:

        ! Last player-specified object
        if object > 0 and object < objects and last_object ~= -1
            AssignPronoun(object)

Still, there's that "last_object \~= -1" loophole, and `Perform` *does*
also set the `last_object` global to whatever `object` we have. We'll
work off of that.

In the following example, we will keep our top hat from the example
above, but we will be adding a bunny that the player can put in the hat.
The bunny will then be replaced by a dove since we are the best magician
in town!

    room STARTLOCATION "Start Location"
    {}

    object bunny "bunny"
    {
        noun "bunny"
        article "the"
        in you
    }

    object hat "top hat"
    {
        noun "hat"
            adjective "top"
            article "the"
        short_desc {
               "A top hat sits in the center of the room, demanding your attention."
               AssignPronoun(hat)
               parser_data[PARSER_STATUS] = PRONOUNS_SET
               }
        before
               {
               xobject DoPutIn
                    {
                    if object = bunny
                        {
                        "You lower the bunny in the depths of the top hat. You tap the
                        hat a couple times. There is a flash of light, and you are
                        momentarily blinded. When your vision clears, you see the bunny
                        has been replaced by a white dove, which proceeds
                        to fly around your head."
                        remove bunny
                        move dove to STARTLOCATION
                        AssignPronoun(dove)
                        object = -1
                        return true
                        }
                    return false
                    }
               }
        is container, clothing
        in STARTLOCATION
    }

    object dove "white dove"
    {
        adjective "white"
        noun "dove"
        article "the"
    }

This will successfully give us this:

>&gt;put bunny in top hat  
>You lower the bunny in the depths of the top hat. You tap the hat a
>couple times. There is a flash of light,
>and you are momentarily blinded. When your vision clears, you see the
>bunny has been replaced by a white dove,
>which proceeds to fly around your head.
>
>&gt;x it  
>(assuming you mean the white dove)  
>The white dove looks just like you would expect.

So yeah, by setting `object` to -1, we also end up setting `last_object`
to -1. We don't have to worry about resetting `object` since it'll get a
new value before the turn is over. All is right with the world!

That's how to use AssignPronoun. I hope you loved "it"! Har har!
