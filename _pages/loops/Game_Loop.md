---
title: Game Loop
permalink: /loops/game-loop/
categories: 
  - Loops
---

In Hugo terminology, the "game loop" is the sequence of game elements
processed from one command input to the next. Having a familiarity with
it will greatly help an author design his game.

## Overview

Let's quickly go over game loop over, as detailed by the Hugo Book:

` 1. Init`
` 2. Main (which calls PrintStatusLine, location.each_turn, runevents, RunScripts)`
` 3. Input`
` 4. Parsing`
` 5. Grammar Matching`
` 6. Before routines (as called by Perform in hugolib.h)`
` 7. Verb routine (as called by Perform in hugolib) and after routines`
` 8. Loop back to Main`

Let's discuss this.

-   **Init:** The Init routine is run only when the game is first
    started or restarted. It sets up beginning global values and things
    like that.
-   **Main:** Main is the routine that gives the sense of *forward
    progress* to the game. It increases the turn counter and executes
    turn-based game aspects like [each_turn](timers/each_turn/),
    [runevents](timers/events/), and
    [RunScripts](characters/scripts/).
-   **Input:** This is where the player types in a command.
-   **Parsing:** The command is checked for validity by the engine.
    [Parse](routines/parse/) is called.
-   **Grammar Matching:** The engine attempts to match the input line
    with a valid verb and syntax in the grammar table. If no match is
    found, the engine loops back to Input ("Line 3"). If successful,
    `verbroutine`, `object`, and `xobject` are set.
-   **Before routines:** `Before` routines are checked this order:
    <div align="center">

    <table>
    <tbody>
    <tr class="odd">
    <td><p><code>player.before</code><br />
    <code>location.before</code><br />
    <code>xobject.before</code> (only if the verbroutine <em>has</em> an xobject)<br />
    <code>object.before</code> (only if the verbroutine <em>has</em> an object)<br />
    </p></td>
    </tr>
    </tbody>
    </table>

    </div>

    `         After that, the game checks to see if there are any `[`react_before`](properties/react_before/)` properties that should be executed.`
-   **Verb routine :** If no `before` routine skipped over it, the verb
    routine executes as normal. `After` routines are also run.
-   **The Loop Back** [Main](routines/main/) is executed again, taking
    us back to `Input`.

This loop continues until the player quits the game or the
[endflag](globals/endflag/) variable is set to a non-zero value.

## Game Loop in Game Output

Let's code a "game" with the sole purpose of showing where functions
would be called. In the `init` routine, we'll fill a 
[character script](characters/scripts/) with calls to `CharGet`. Then:


    player_character you "you"
    {
        before
            {
            actor PreParse
                {
                "[actor.before PreParse code]"
                return false
                }
            actor DoLook, DoLookAround
                {
                "[actor.before code]"
                return false
                }
            }
        after
            {
            actor DoLook, DoLookAround
                {
                "[actor.after code]"
                return false
                }
            }
    }

    room STARTLOCATION "Start Location"
    {
        long_desc
            "[Room description]"
        each_turn
            "[location.each_turn code]"
        before
            {
            location
                {
                "[location.before code]"
                return false
                }
            }
        after
            {
            location
                {
                "[location.after code]"
                return false
                }
            }
    }

    object rock "rock"
    {
        noun "rock"
        in STARTLOCATION
        article "a"
        before
            {
            object DoLook
                {
                "[object.before DoLook code]"
                return false
                }
            }
        after
            {
            object DoLook
                {
                "[object.after DoLook code]"
                return false
                }
            }
        react_before
            {
            "[rock.react_before code]"
            return false
            }
        react_after
            {
            "[rock.react_after code]"
            return false
            }
    }

    event
    {
    "[Global event code]"
    }

    event in rock
    {
    "[Local (object) event]"
    }

    character giantslug "giant slug"
    {
    in STARTLOCATION
    article "the"
    adjective "giant"
    noun "slug"
    before
         {
         actor CharGet
             {
         "[actor.before character script code]"
         return false
             }
         }
    }

    replace CharGet
    {
        "[character script code]"
    }

Playing this game will give us this output:

>Intro to game
>
>Game Loop Follies  
>Game Loop Blurb  
>Hugo v3.1 / Library 31031  
>put-IFID here  
>\[actor.before code\]  
>\[location.before code\]  
>\[rock.react_before code\]
>  
>Start Location  
>\[Room description\]  
>The giant slug is here.  
>A rock is here.  
>\[actor.after code\]  
>\[location.after code\]  
>\[rock.react_after code\]  
>\[location.each_turn code\]  
>\[Global event code\]  
>\[Local (object) event\]  
>\[location.before code\]  
>\[actor.before character script code\]  
>\[character script code\]  
>  
>&gt;look  
>\[actor.before PreParse code\]  
>\[actor.before code\]  
>\[location.before code\]  
>\[rock.react_before code\]  
>  
>Start Location  
>\[Room description\]  
>The giant slug is here.  
>A rock is here.  
>\[actor.after code\]  
>\[location.after code\]  
>\[rock.react_after code\]  
>\[location.each_turn code\]  
>\[Global event code\]  
>\[Local (object) event\]  
>\[location.before code\]  
>\[actor.before character script code\]  
>\[character script code\]  
>  
>&gt;examine rock  
>\[actor.before PreParse code\]  
>\[actor.before code\]  
>\[location.before code\]  
>\[rock.react_before code\]  
>\[object.before DoLook code\]  
>The rock looks just like you would expect.  
>\[object.after DoLook code\]  
>\[actor.after code\]  
>\[location.after code\]  
>\[rock.react_after code\]  
>\[location.each_turn code\]  
>\[Global event code\]  
>\[Local (object) event\]  
>\[location.before code\]  
>\[actor.before character script code\]  
>\[character script code\]  
>  
>&gt;  

Ta-da!
