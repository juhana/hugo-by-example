---
title: PrintEndGame
permalink: /routines/printendgame/
categories: 
  - Routines
---

`PrintEndGame(end_type)` provides the **\*\*\* YOU'VE WON THE GAME
\*\*\*** (or variations thereof) text at the end of a game. It is called
by the [EndGame](/routines/endgame/) routine.

### The code

    routine PrintEndGame(end_type)
    {
        Font(BOLD_ON)
        select end_type
            case 1:  print "\n*** YOU'VE WON THE GAME! ***"
            case 2
            {
                if player_person = 2
                    print "\n*** YOU HAVE DIED ***"
                else
                    print "\n*** "; CThe(player); \
                        MatchPlural(player, "has", "have"); \
                        " died! ***"
            }

        Font(BOLD_OFF)
        PrintScore(true)
    }

### Replacing PrintEndGame

Some people replace `PrintEndGame` with a simple "The game is
over."-type text. Conversely, you could add more `select cases` so that
your game offers all sorts of stylized end-messages, depending on what
[endflag](/globals/endflag/) value you set to end the game.

    replace PrintEndGame(end_type)
    {
        Font(BOLD_ON)
        select end_type
            case 1:  print "\n*** YOU ARE A TRUE HUGONAUT! ***"
            case 2:  PRINT "\n*** YOU HAVE REACHED THE NADIR OF GREATNESS ***"
            case 3:  print "\n*** YOU ARE AREN'T A DUCK! ***"

        Font(BOLD_OFF)
        PrintScore(true)
    }
