---
title: Informal Questions
permalink: /tips/informal-questions/
categories: 
  - Tips
---

Several Infocom games had moments where the player was asked a YES/NO
question. Unlike the [YesorNo](YesorNo) method, though, the
player had the option to ignore the question altogether and do anything
else (all other normal commands were also accepted). This entry attempts
to show how one could code such a system.

## Back to the Egress

Let's implement the "egress" from Ballyhoo. This one acts much more like
the version in the original game:

    ! To be added to verb grammar
    verb "yes","y"
        *                   DoYes
    verb "no"
        *                   DoNo
    ! A global variable to hold any current question being asked, if applicable
    global currentquestion

    ! Let's tweak PreParse so "n" means "no" when a question is being asked of the PC
    ! note: Ballyhoo did not actually do this
    replace PreParse
    {
        if currentquestion and word[1] = "n"
            word[1] = "no"
    }

    room whitewagon "Near White Wagon"
    {
        !  Going "south" four times will also leave the circus
        s_to {
            if currentquestion = mystery
                        endflag = 3
            if currentquestion = mammal
                NewQuestion(mystery)
            if currentquestion = egress
                NewQuestion(mammal)
            if not currentquestion
                NewQuestion(egress)
             }
    }

    ! a question class so to help organize our questions
    class Question
    {}

    question egress
    {
        long_desc
            "Are you sure you're mentally and otherwise prepared to meet up with an egress?"
    }

    question mammal
    {
        long_desc
            "Then you're fully aware of the ferociousness of this rare mammalian species, right?"
    }

    question mystery
    {
        long_desc
            "Alright, so you know all about egresses.
             But do you really want to leave the circus in all of its mystery
             and all of its pageantry behind?"
    }

    ! A fuse so that each question is only answerable for one turn
    fuse questionwindow
    {}

    event questionwindow
    {
        if not self.tick
            currentquestion = 0
    }

    ! A routine that sets the current question, prints it out, and starts its timer (fuse)
    routine NewQuestion(topic)
    {
        currentquestion = topic
        run topic.long_desc
        Activate (questionwindow, 2)
    }

    ! note that I decided to return false if there is no current question
    ! (meaning that the turn counter doesn't increase)
    routine DoYes
    {
        if not currentquestion
            {
            "Yes?"
            return false
            }
        else
        select currentquestion
            case egress: NewQuestion(mammal)
            case mammal: "Then you'd be helpless against this dangerous beast."
            case mystery: endflag = 3
        return true
    }

    routine DoNo
    {
        if not currentquestion
            {
            "You sound rather negative."
            return false
            }
        else
        select currentquestion
            case egress: "Then you'd be helpless against this dangerous beast."
            case mammal: NewQuestion(mystery)
            case mystery: "That's the spirit."
        return true
    }
