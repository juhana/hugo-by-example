---
title: Opportune.h
permalink: /contributions/opportune.h/
categories: 
  - Library Contributions
---

`Opportune.h` started as the code from the [Informal
[Questions](/tips/informal-questions/) page but was adapted and
simplified so that it could be applied to more types of situations. Now
it has been further adapted and commented for easy inclusion in a game.
Download it [here](http://roody.gerynarsabode.org/hbe/opportune.h).

## The code

    !\-----------------------------------------------------------------------
    Opportune.h, a Hugo library contribution for WINDOWS OF OPPORTUNITY
    version 1.2 by Jon Blask

    This contribution lets you start different 1-turn timers for when you
    want a special response only when an action is taken directly after a
    specific other action.

    It is hoped that using objects (instead of global variables or something)
    to keep track of these WINDOWS OF OPPORTUNITY will be a nice way to keep
    things organized.

    An example:

    opp brokelamp
    {}

    [If somebody pushes the lamp, we'll say it tips over and breaks on the
    floor.]

    We start our timer with:

    NewOpp(broke_lamp)

    [Now, let's change the response to >OOPS.]

    replace NewParseError(errornumber, obj)
    {
        select errornumber
        case 16 : {
                  if current_opp = broke_lamp
                     {
                     "Smooth move, um, Mr. Smooth."
                     current_opp = 0
    ! in this case, we clear the opportunity by hand
    ! since a ParseError response will not use a turn
                      }
                  else
                     return false
                  }
        case else : return false
        return true
    }

    We can make an opportunity last longer by giving it an "extra_turns"
    value; the opportunity will last (that value + 1) turns.

    Having extra_turns also makes it important to clear the current_opp global
    by hand if the player does the opportunity-enabled action.

    opp longwindow
    {
        extra_turns 3
    }

    (longwindow would be open for 4 turns.)

    This feature is not entirely recommended, though, as it leaves the window
    open (no pun intended) for triggering multiple opportunities, and this
    system only supports one at a time.

    -----------------------------------------------------------------------\!

    #ifclear _OPPORTUNE_H
    #set _OPPORTUNE_H

    #ifset VERSIONS
    #message "Opportune.h Version 1.2"
    #endif

    global current_opp ! current opportunity

    ! A fuse so that each question is only answerable for one turn
    ! opp_window = short for "opportunity window"
    fuse opp_window
    {}

    event opp_window
    {
       if not self.tick
          current_opp = 0
    }

    class Question
    {}

    routine NewQuestion(new_question)
    {
       current_opp = new_question
       run new_question.long_desc  ! Prints the question
       Activate (opp_window, 2) ! Starts the new timer
    }

    !\
    ! Optional Yes/No Question Section
    ! If you want to have some in-game Yes/No questions like those in
    ! the Infocom games ("Are you sure you're mentally and otherwise prepared to meet up with an egress?"),
    ! define questions like the following.

    ! NOTE: >YES and >NO are not supported by verblib.h and verblib.g; they are in the
    ! verbstub files. If you don't want to define those verbs yourself, uncomment
    ! #set VERBSTUBS at the beginning of your game file (assuming you started out with
    ! the Hugo shell).

    question egress
    {
       long_desc
          "Are you sure you're mentally and otherwise prepared to meet up with an egress?"
    }

    ! When you want to print a question, use NewQuestion, like:
    ! NewQuestion(egress)

    ! Then, in your code, where you want to check if the player is currently being asked a question, say:
    ! if current_opp = egress
    !     <code to execute>

    ! Here is some example code:

    room whitewagon "Near White Wagon"
    {
        !  Going "south" four times will also leave the circus
       s_to {
          if current_opp = mystery
                        endflag = 3
          if current_opp = mammal
             NewQuestion(mystery)
          if current_opp = egress
             NewQuestion(mammal)
          if not current_opp
             NewQuestion(egress)
            }
    }

    replace DoYes  ! this routine assumes VERBSTUBS has been included
    {
       if not current_opp
          {
          "Yes?"
          return false
          }
       else
       select current_opp
          case egress: NewQuestion(mammal)
          case mammal: "Then you'd be helpless against this dangerous beast."
          case mystery: endflag = 3
       return true
    }
    \!

    routine NewOpp(opportunity)
    {
       current_opp = opportunity
       Activate (opp_window, (2 + opportunity.extra_turns))
    }

    property extra_turns alias holding

    class opp
    {}

    #endif

## Hugo Homework

This library extension isn't very ambitious, but it accomplishes what it
sets out to do. Imagine a game that requires multiple, concurrent
opportunities, though. Think you could amp up this extension using
object property elements and [InList](/routines/inlist/) to do the job?
