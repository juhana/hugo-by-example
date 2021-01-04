---
title: hugolib.h
permalink: /library/hugolib.h/
categories: 
  - Hugo Library
---

**hugolib.h** is the master file for the Hugo Standard Library. It will
automatically `#include` the other files as needed.

This file defines the common [properties](properties/) and
[attributes](attributes/) used in Hugo games. It also defines
several global [variables](basics/variables/) constants used by
routines in the library files.

It also defines several of the base [objects](basics/objects/) used
by the library.

There are also several [routines](routines/) such as:

| Routine                                                            | Summary of what it does                                                                                                                                                                                                               |
|--------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [`EndGame(end_type)`](routines/endgame/)                          | This routine is called by the Hugo game engine when the `endflag` is set to a non-zero value. It calls the **PrintEndGame()** routine then offers the player the choice to restart/restore the game, or undo the last move.           |
| [`PrintEndGame(end_type)`](routines/printendgame/)                | This is the routine that actually prints the "you have won" or the "you have died" message at the end of a game. It is usually [replaced](guts/replace/) by the game author to make it fit in more with the tone of the game.    |
| [`Parse`](routines/parse/)                                        | The library Parse routine twiddles the player's input, replacing pronouns, removing unnecessary words and whatnot before passing the information to the engine's parser.                                                              |
| [`PreParse`](parsing/preparse/)                                  | This routine is normally empty and is meant to be replaced by the author so he (or she) can twiddle the input before it is handled by the Parse routine.                                                                              |
| [`ParseError(errornumber,`` ``obj)`](parsing/parseerror/)        | This routine is called to print an error message if there is a problem with the player's input. If the [variable](basics/variables/) *errornumber* is equal or greater than 100, it makes the engine call the CustomError routine. |
| `NewParseError(errornumber, obj)`                                  | A blank routine that is there to be replaced by the game author to print out a custom error message for library parsing.                                                                                                              |
| `CustomError(errornumber, obj)`                                    | A blank routine that is there to be replaced by the game author to print out a custom error message for library parsing.                                                                                                              |
| `SpeakTo(char)`                                                    | SpeakTo is called by the engine when a command is addressed to a character. (ie. `Roody, read the newspaper.`                                                                                                                         |
| [`PutInScope(obj, act)`](properties/in_scope/)           | Places the `obj` into the `act`or's [scope](scope/).                                                                                                                                                                        |
| [`RemoveFromScope(obj, act)`](properties/in_scope/) | Like the PutInScope routine, but takes said object out of scope.                                                                                                                                                                      |
| `PrintStatusLine`                                                  | Called by the engine to print the status line across the top of the screen. If you need to change how/what the status line shows, you need to replace this routine with one of your own.                                              |
| `IsorAre(obj, a)`                                                  | Used to choose the correct verb based on whether or not the `obj`ect is plural or singular.                                                                                                                                           |
| [`MovePlayer(loc, silent, ignore)`](routines/moveplayer/)         | Routine to move the Player character to a specific `loc`ation.                                                                                                                                                                        |
| `Acquire(newparent, newchild)`                                     | Used to move `newchild` to `newparent`, returns `true` if successful. (It may be unsuccessful if the newparent can't contain any more objects.)                                                                                       |

And many others.
