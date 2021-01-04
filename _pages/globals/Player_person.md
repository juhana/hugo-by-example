---
title: player_person
permalink: /globals/player_person/
categories: 
  - Global Variables
---

The value of the `player_person` 
[global variable](basics/global/) determines whether the
game is told in a first, second, or third person.

| player_person value | behavior              | example                                       |
|----------------------|-----------------------|-----------------------------------------------|
| 1                    | Game is first-person  | "I can't see that anywhere."                  |
| 2                    | Game is second-person | "You are likely to be eaten by a stereotype!" |
| 3                    | Game is third-person  | "Pinochio throws the hammer at the cricket!"  |

## Additional changes

Any game that changes the default value (2) of `player_person` also has
to make changes to the `player_character` object so error messages work
correctly:

### first person player

Set the [global variable](basics/global/)
`player_person` to `1`:

    player_character you "I"
    {
     ! nouns "you", "yourself" ! possibly (depending on whether you want the player typing >EXAMINE YOURSELF)
     pronouns "I", "me", "my", "myself"
    }

### second person player

Set the [global variable](basics/global/)
`player_person` to `2` (this is the default value):

    player_character you "you"
    {
     ! default values work (nouns "me" "myself" / pronouns "you" "you" "your" "yourself")
    }

### third person

Set the [global variable](basics/global/)
`player_person` to `3`:

    player_character jack "Jack"
    {
     nouns "jack" "himself"
     pronouns "he","him", "his", "himself"
     is not plural
    }
