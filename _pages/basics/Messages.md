---
title: Messages
permalink: /basics/messages/
categories: 
  - Basics
---

Hugo, where possible, will separate a routine's functions (say, the
actual game-restoring of DoRestore) from its text ("Restored."). This
allows for easy manipulation of one or the other as it will be rare that
you would need to change both. Also, writing routines in this way should
help keep you in a mindset conducive to writing general-case code
applicable to multiple games.

## `Message` and `VMessage`

The routines `Message` (in [hugolib.h](Hugolib.h)),
`VMessage` (in [verblib.h](Verblib.h_g)), and `OMessage` (in
[objlib.h](Objlib)) work in an identical fashion, so we will
cover them together.


    ! Abridged Message() routine

    routine Message(r, num, a, b)
    {
        ! Check first to see if the NewMessages routine provides a
        ! replacement message:
        if NewMessages(r, num, a, b):  return

        select r

            ! [various routine messages]

            ! &Parse, as as an example
        case &Parse
        {
            select num
            case 1:  print CThe(player); \
                    MatchPlural(player, "doesn't", "don't"); \
                    " need to refer to that."
            case 2:  print "(assuming you mean";
            case 3:  print ", respectively";
        }

            ! [more routine messages]
    }

    ! Now let's look at an abridged VMessages

Lastly, an abridged `OMessage`

    routine OMessage(obj, num, a, b)
    {
        ! Check first to see if the NewOMessages routine provides a
        ! replacement message:
        !
        if NewOMessages(obj, num, a, b):  return

        select obj

        case self_class
        {
            select num
            case 1
            {
                print "\""; capital self.name;
                print "\" isn't quite appropriate for ";
                print The(object); "."
            }
        }

            ! skipping several other classes, such as directions, vehicles, attachments, etc.
    }

## Custom or New Routine Responses

Notice how `Message`, `VMessage`, and `OMessage` check for
`NewMessages`, `NewVMessages`, and `NewOMessages` routines,
respectively? Those are what we use to change messages or provide a new
one. We'll [replace](Replace) them.

    replace NewMessages(r, num, a, b)
    {
            select r

        case &DescribePlace
        {
            ! Let's change the "It's too dark to see." response
            select num
            case 1:  print "Man, I can't see jack in here."
            case 2:  return false  ! otherwise, do nothing
        }

            case else : return false

           return true ! this line is only reached if we replaced something
    }

Returning false in all other scenarios tells `Message` to go on as
planned, printing whatever default is there. Not returning false in all
other scenarios will make your game very sad.
`NewVMessages` and `NewOMessages` work in the same way.

## Some blank message routines

Here are some routines for quick copy-and-pasting into your games!

    routine <blank>Message(r, num, a, b)
    {
        ! Check first to see if the new messages routine provides a
        ! replacement message:
        if New<blank>Messages(r, num, a, b):  return

        select r

        case <first routine>
        {
            select num
            case 1:
        }
    }

    routine New<blank>Messages(r, num, a, b)
    {
        select r

        case <first routine>
        {
            select num
            case 1:
        }

        case else : return false

        return true ! this line is only reached if we replaced something
    }

    ! Now, a blank object message routine

    routine <blank>OMessage(obj, num, a, b)
    {
        ! Check first to see if the New<blank>OMessages routine provides a
        ! replacement message:
        !
        if New<blank>OMessages(obj, num, a, b):  return

        select obj

        case <object>
        {
            select num
            case 1 :
        }

            ! skipping several other classes, such as directions, vehicles, attachments, etc.
    }

    routine New<blank>OMessages(obj, num, a, b)
    {
        select obj

        case <object>
        {
            select num
            case 1:
        }

        case else : return false

        return true ! this line is only reached if we replaced something
    }
