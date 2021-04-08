---
title: Characters
permalink: /characters/
categories: 
  - Characters
---

Characters can add all sorts of elements to a game. This page covers
multiple aspects of the "character object"- both the *player character*
object that is set up for the player to inhabit or the *non-player
characters* that need responses to all sorts of situations.

# Player Characters

`player_character` objects, of course, represent the player.

The player object class, as defined by *objlib.h*:

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

## in-game player definitions

In *your* game, you'll just create a `player_character` object that
inherits all of the above. Depending what the narrative mode of your
game is, you'll make slight additions (or negations).

### first person player

Set the [global variable](basics/global/)
`player_person` to `1`:

    player_character you "I"
    {
     ! nouns "you", "yourself" ! possibly
     pronouns "I", "me", "my", "myself"
    }

### second person player

Set the [global variable](basics/global/)
`player_person` to `2` (this is the default value):

    player_character you "you"
    {
     ! inherits all of the above
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

## changing characters

For information on changing player characters, read the
[Changing_Player_Characters](strings/changing-player-characters/)
page.

# Non-Player Characters

When it comes to characters, the more substantial challenge comes from
coding the other living (or possibly undead) creatures that our
protagonist will have to interact with. Believable characters have
responses to a lot of commands. This section aspires to be a "quickstart
guide" to various ways of dealing with NPCs.

### asking characters about things

To set up **ASK CHARACTER ABOUT OBJECT** responses, add `after` routines
like the following:

        after
        {
            object DoAsk
            {
                select xobject
                case golf_ball
                    "\"To be honest, I don't know much about
                                 golf balls.\""
                case else
                    "\"I just don't know anything about that,
                    drink-buyer.  How about buying me a drink
                    anyway?\""
            }
        }

For more information, check the [DoAsk](verb-routines/doask/) page.

### telling characters about things

`DoTell`, the verb routine associated with **TELL CHARACTER ABOUT
OBJECT** works the same way:

        after
        {
            object DoTell
            {
                select xobject
                case golf_ball
                    "\"THANK YOU SO MUCH for enlightening me
                                 about golf balls!\""
                case else
                    "\"That's very interesting,
                    drink-buyer.  How about buying me a drink?\""
            }
        }

### showing objects to characters

`DoShow`'s verb grammar makes sure that the `xobject` is in scope. Other
than that, though, it is not much different:

        after
        {
            object DoShow
            {
                select xobject
                case golf_ball
                    "\"That is quite some golf ball you have there!\""
                case else
                    return false ! do default 'so-and-so isn't interested' response
            }
        }

### giving objects to characters

Of the last four examples, `DoGive` is the most complicated. The
`DoGive` routine itself basically makes sure the `xobject` is give-able
(the object must be held, not worn, etc.). What it *doesn't do* is
actually move any objects for you. You'll have to do that yourself in
the `after` routine:

        after
        {
            object DoGive
            {
                select xobject
                case golf_ball
                    {
                                    print self.name ; " happily accepts your golf ball!"
                                    move golf_ball to self
                                    }
                case else
                    return false ! do default 'so-and-so politely refuses' response
            }
        }

### ordering characters

Responses for commands to characters can be coded using the
`order_response` property:

    character fred "Fred"
    {
        noun "fred"
        in STARTLOCATION
        order_response
            {
            if verbroutine = &DoLook and object = player
                {
                "He says, \"Wow, you look lurvly.\""
                return true
                }
            return false
            }
    }

More information can be found on the
[order_response](properties/order_response/) page.

### characters reacting! to you!

There are a couple different ways one can have messages print when a
character 'sees' the player do this or that command. One way is to use
an event:

    event in <character name>
    {
    select verbroutine
        case &DoGet
            print self.name ; " watches you grab "; The(object) ; ". \"That is just like you.\""
        case &DoLookAround
            print self.name ; " says, \"Dang, you are always looking around.\""
        case else : return false
    }

Alternatively, you could also give the character a
[react_after](properties/react_after/) property:

    character fred "fred"
    {
        ! other fred code
        react_after
            {
            select verbroutine
               case &DoGet
                  print self.name ; " watches you grab "; The(object) ; ". \"That is just like you.\""
               case &DoLookAround
                  print self.name ; " says, \"Dang, you are always looking around.\""
               case else : return false
            }
    }
