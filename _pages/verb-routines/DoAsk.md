---
title: DoAsk
permalink: /verb-routines/doask/
categories: 
  - Verb Routines
---

`DoAsk` is the verblib.h verb routine that is called when players enter
`>ASK CHARACTER ABOUT THING`.

## Grammar definition (from [verblib.g](Verblib.h_g))

    verb "ask", "question", "consult"
        *                                                       DoAsk
        * "about" anything                                      DoAskQuestion
        * living "about" anything                               DoAsk
        * living                                                DoAsk

The `anything` grammar token allows the player to ask about things that
are not in scope. `DoAskQuestion` checks to make sure the player is
talking to someone before heading back to `DoAsk`.

## Usage

To illustrate how one provides `DoAsk` with responses, let us look at
some abridged source of the character Old Dan in the game Spur:

    spur_character dan "Old Dan"
    ! is special once initial grumbling is done
    {
        in mainstreet_south
        nouns "dan", "daniel"
        adjectives "old", "town", "drunk"
        short_desc
        {
            "Old Dan, the town drunk, is here, standing in place and
            swaying slightly.";
            run self.misc
            print newline
        }
        after
        {
            object DoAsk
            {
                select xobject
                case gradys_building
                    "\"Ah...Grady's.  My home away from home.  \
                    Actually, just my home.  Grady's casa, mi
                    casa.\""
                case lucilles_building
                    "\"Guess you could probably pick up
                    whatever you needed there:  bullets and
                    other stuff.  No whiskey, though.\""
                case glenheffer
                    "\"Glen Heffer?  Well, now, Glen Heffer is
                    another story.  Wouldn't think twice I don't
                    think 'bout shooting you in the back.  Or
                    the front.\""
                case else
                    "\"I just don't know anything about that,
                    cowboy.  How's about buying me a drink
                    anyway?\""
            }
        }
    }

As you can see, unlike Inform 6 where one writes every word the player
might ask about, in this case, we just point to the objects themselves
(so the code inherits the nouns and adjectives already declared for
them). Of course, unless you rewrite the routine to work off of words
instead (as some have done), you'll have to create conversational
objects for topics not already represented by an existing object.

## Keeping Track of Times Asked

Here is some experimental code for allowing for changing answers,
depending on how many times you have asked.

    property asked ! this property will keep track of times asked for each topic

    character SampleGuy "Sample Guy"
    {
            noun "guy"
            adjective "sample"
            asked #3 ! this gives 'asked' 3 empty elements for us to fill, one for each topic we can ask about
        after
        {
            object DoAsk
            {
                select xobject
                case self   !  asked element #1
                                    {
                                    if  not self. asked #1  ! Check to make sure we haven't asked about this
                            "\"What can I say?  \
                            I'm just this guy.\""
                                    else
                                            "\"I told you about myself already!\""
                                            self.asked #1 += 1  ! take note that we were asked this
                                    }
                case state_of_hugo_today  ! asked element #2
                    "\"It's great!\""
                case unix  ! asked element #3
                    "\"Unix? I /Bknow/b this!\""
                    }
            }
    }

Of course, if you wanted, you could quicken up property-checking with
routines like this:

    routine AddAsked(char,element)
    {
        char.asked #element += 1
    }

    routine IfAsked(char,element)
    {
        return object.asked #element
    }

Which you could execute with:

    if not IfAsked(self,1)
        "thing1"
    else
        "thing2"
    AddAsked(self,1)
