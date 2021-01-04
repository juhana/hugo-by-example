---
title: Replace DoSearch
permalink: /replacements/dosearch/
categories: 
  - Replacements
---

### What it fixes

-   The original has this:
              if object.pronouns #2
              {
                 " search ";
                 if object.pronouns #2
                    print object.pronouns #2;
                 else
                    print object.pronoun;
              }

    That has some redundant code. It has been assumed that the code was
    meant to be:

              if object.pronouns
              {
                 " search ";
                 if object.pronouns #2
                    print object.pronouns #2;
                 else
                    print object.pronoun;
              }

### The code

    #ifset _VERBSTUB_H
    replace DoSearch
    {
        if object = player
        {
            "Search ";
            The(player)
            " indeed."
        }
        elseif object is container and child(object)
            Perform(&DoLookIn, object)
        elseif object is living
        {
            print CThe(object); MatchPlural(object, "doesn't", "don't");
            " let ";
            The(player)
            if object.pronouns
            {
                " search ";
                if object.pronouns #2
                    print object.pronouns #2;
                else
                    print object.pronoun;
            }
            print "."
        }
        else
        {
            CThe(player)
            MatchPlural(player, "doesn't", "don't")
            " find anything new."
        }
        return true
    }
    #endif
