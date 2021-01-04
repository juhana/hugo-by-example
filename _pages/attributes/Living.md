---
title: living
permalink: /attributes/living/
categories: 
  - Attributes
---

`living` is an [attribute](attributes) given to living
things. As such, it is an important part of the [character class definition](Character_Classes).
The [standard library](standard_library) usually uses it in
[grammar tokens](Grammar_Tokens) and routines to check for
interactions with [characters](characters), but you could use
it for animals and such, too. You'll just have to take care to properly
set object [pronouns](pronouns) and messages.

## Some Examples

Vault of Hugo uses it thus:

    ...
        before
        {
            object DoThrowAt
            {
                if xobject is living
                    "Trying to start something, are we?"
                else
                    Perform(&DoAttachObject, object, xobject)
            }
        }
    ...


    routine DoPunt
    {
        if object is living
            "Oh, good.  Real good.  Pick a fight, now.  That's really
            going to get you places."
        elseif object.type ~= balls
            "You won't get very far trying to kick that around."
        else
        {
            "You wind up and give ";
            The(object)
            " a good boot.  ";
            if dwarf in ballroom
                "The dwarf nods approvingly."
            else
                print newline
            move object to ballroom
            player.holding = player.holding - object.size
        }
        return true
    }

Here's some Future Boy! code that uses it as grammar tokens:

    verb "ask"
        * object                    DoAskObject
        * living "about" "her"/"his"/"their" "name"/"names" DoAskName
        * living "about" "hername"          DoAskName
        * living "hername"              DoAskName
        * living "her"/"his"/"their" "name"/"names" DoAskName
        * living "where" anything "is"/"are"        DoAskWhere
        * living "who" anything "is"/"are"      DoAsk
