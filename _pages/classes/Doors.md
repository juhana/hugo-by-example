---
title: Doors
permalink: /classes/doors/
categories: 
  - Basics
  - Classes
---

## Basics

Many games take place inside buildings (or boats, or spaceships) and one
thing these places have in common is doors.

The [Hugo Library](library/) includes a door class to
make using doors in your game very easy. It will automatically take care
of most of the drudge-work. It provides the appropriate response if the
door is locked, closed or open, and will automatically open doors for
players that go in their direction.

The door [class](basics/object_classes/) is defined in the
*objlib.h* file (part of the Hugo Library). The
property **between** is [aliased](basics/alias/) to the property
**found_in**, which means you won't be able to use
[found_in](scope/found_in/) in your door's definition.

It also defines the action to automatically open a door if a player
tries to go through a closed door. (This will use up two turns in total,
opening the door, and going through it. The class also redirects the
verb **push** into the **open** action, and the **pull** verb into the
**close** action.

## Examples

#### Simple Door Example

Here's an example of a simple door between a bedroom and hall

    door bed_door "bedroom door"
    {
      between master_bedroom, main_hall
      article "the"
      adjective "bedroom"
      noun "door"
    }

The between [property](properties/) takes care of making the
hall and bedroom accessible from each other.

To make use of this door, the <direction>_to object in the
**master_bedroom** and the **main_hall** to the following:

    room master_bedroom "master bedroom"
    {
      ! Code here for the descriptions and things
      e_to
      {
        return bed_door.door_to
      }
    }

    room main_hall "main hall"
    {
      ! code here for the description and things
      w_to
      {
        return bed_door.door_to
      }
    }

#### Locked Door Example

Sometimes you want to have a door that's locked, as part of a puzzle, or
just as a way to pace the game.

    ! Somewhere else in the code, we define an object to be used
    ! an actual key in this example.
    object brass_key "brass key"
    {
      noun "key"
      adjectives "large", "brass", "heavy"
      article "your"

      long_desc
      {
        "Your brass key. This is the key to your very own house, the first house you've
        actually bought yourself. It's heavy weight is a comfortable feeling in your hand."
      }
    }

    ! some other code happens here

    ! defining the door

    door front_door "front door"
    {
      ! place the door
      between foyer, porch
      noun "door"
      adjectives "front", "brown", "house", "beautiful"
      article "the"

      long_desc
      {
        "The beautiful front door to your house. The wood grain shows through the dark stain.
        the solidly built door. The brass doorknob is still shining with newness."
      }

      ! the door needs to be lockable before lock/unlock will work on it
      ! also, it starts out locked.
      is lockable, locked
      key_object brass_key
    }

Now, unless the player uses the brass key, they won't be able to unlock
the *front_door*.

#### A Door By Any Other Name

Doors are a great place to break out the whole *conditional name* shtick
since how you refer to a door often is affected by where you are
referring to it. For example:

    door bathroom_door
    {
      name
        {
          if location = hallway
            return "bathroom door"
          elseif location = bathroom
            return "door"
        }
      adjective "bathroom"
      noun "door"
      article "the"
      between hallway, bathroom
    }

In this example, while in the hallway, the game will refer to the door
"the bathroom door." In the bathroom, though, it'll just be "the door."

#### Unseen Doors

Since a door's `between` property is just an [alias](basics/alias/)
of [found_in](scope/found_in/), doors aren't *technically* in the
room (as far as the [object tree](basics/object_tree) is concerned,
anyway). This means that the door's [short_desc](properties/descriptions/)
is not normally called by [DescribePlace](guts/describeplace/).
There are some ways of getting around this:

-   **Have the door be physically in one of the two rooms.**
    If you use this method, at least in *one* of the rooms, you can have
    the door's [short_desc](properties/descriptions/) called (or
    [when_open](properties/descriptions/) and
    [when_closed](properties/descriptions/), if you are so inclined). The
    other room will have to get by with a mention of the exit in the
    room's [long_desc](properties/descriptions/).
-   **Have the door's description be an event**
    Of course, going this route means that the door's description will
    be printed *after* any other room objects, and you'll have to take
    care that it isn't also called after other, more-action-y events.
-   **Just throw it all into the room's `long_desc`**
    The sometimes-unappealing-but-always-viable route is to just throw
    the door descriptions into the room's
    [long_desc](properties/descriptions/). This way, you're always sure
    where the door is going to be mentioned.
