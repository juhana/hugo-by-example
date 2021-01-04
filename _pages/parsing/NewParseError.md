---
title: NewParseError
permalink: /parsing/newparseerror/
categories: 
  - Parsing
  - Routines
---

`NewParseError` allows you to replace individual parser messages
including those defined by the engine (see the
[ParseError](/parsing/parseerror/) entry for a list of error messages).
This is useful for catering existing error messages to your game.

#### Example

All you have to do is replace the `NewParseError` routine defined by
[hugolib.h](/library/hugolib.h/):

    replace NewParseError(errornumber,obj)
    {
         select errornumber
              case 0 : "I say, wot?"
              case 1 : print "You don't have to use the word \""; parse$; \
    ",\" my good fellow!"
              ! ... more case options
              case else : return false
         return true
    }

That's all, folks!
