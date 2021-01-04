---
title: Changing Player Characters
permalink: /strings/changing-player-characters/
categories: 
  - Tips
---

While writing some kinds of games, instead of writing one
`player_character` object that is a mess of conditional statements,
it'll be more convenient to create several `player_character` objects
that the game switches between.

Before we start writing multiple player_character examples, let's look
at how `player_character` is defined in `objlib.h`.

### player_character class definition

    character player_character
    {
        ! 'nouns' and 'pronouns' as defined below are the defaults
        ! for second-person, i.e., when player_person is 2--'name'
        ! should be "you"
        !
        nouns "me", "myself"
        pronouns "you", "you", "your", "yourself"

        long_desc
        {
            print "Looking good."
        }

        capacity 100
        is hidden
        is plural       ! because player_person defaults to 2
    }

### sample player_character objects

    player_character human "you"
    {
        long_desc {
                "You are a human!"
              }
    }

    player_character werewolf "you"
    {
        long_desc {
                "You are a werewolf! Rar! You have fangs and claws and stuff!"
              }
    }

    component fangs "fangs"
    {
            noun "fangs"
            long_desc {
                      "Fangs!"
                      }
            part_of werewolf
    }

    component claws "claws"
    {
            noun "claws"
            long_desc {
                      "Claws!"
                      }
            part_of werewolf
    }

    component stuff "stuff"
    {
            noun "stuff"
            long_desc {
                      "Stuff!"
                      }
            part_of werewolf
    }

Notice how player_character objects don't have nouns or pronouns, as
that will overwrite the class nouns or pronouns (breaking "EXAMINE ME").

### The transformation

In the above example, the code for changing into the werewolf might look
like this:

    move werewolf to location
    player = werewolf
    remove human

Of course, your code will also need to address inventory concerns. In
the above example, if the player drops everything he isn't wearing, the
code might look like this:

        for i in human
                    {
            if i is not worn
                    move i to location
                    else
                    move i to werewolf
                    }

### Changing players \*and\* locations

In a game where we switch to a player character in another location, we
have to let the game know the `location` global has changed, lest there
be trouble.

Let's imagine a game like *Suspended* where you can switch between
*\*TWO\** robots:

    routine DoChange
    {
        if player = robot1
            player = robot2
        else
            player = robot1
        location = parent(player)
            old_location = location
            DescribePlace(location)
            location is visited
    }
