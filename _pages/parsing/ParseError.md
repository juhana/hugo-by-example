---
title: ParseError
permalink: /parsing/parseerror/
categories: 
  - Parsing
  - Routines
---

`ParseError` is responsible for the error messages that are printed when
something keeps a command from being successfully executed, whether it
be a mistyped word or referring to an unknown object or what have you.

Normally, when we want to change particular error messages, we replace
[NewParseError](NewParseError), but since we must be aware of
the various error numbers and what they stand for, it is good to be
familiar with `ParseError`'s default messages.

| Error Number | When Called                                                          | Message Example                                |
|--------------|----------------------------------------------------------------------|------------------------------------------------|
| *0*          | *Carriage return pressed with nothing typed*                         | "What?"                                        |
| 1            | Not understood word in input                                         | "You don't have to use the word '`parse$`'"    |
| *2*          | *Command does not start with a verb*                                 | "Better start with a verb."                    |
| 3            | Tried to use ALL with a verb that doesn't support it                 | "You can't read multiple objects like that."   |
| *4*          |                                                                      | "Can't do that."                               |
| 5            | Player's command didn't match any object, but all words used are in the game's dictionary | "You haven't encountered something like that." |
| 6            | Command didn't make sense                                            | "That didn't make any sense."                  |
| *7*          | *Use ALL as an xobject where not supported*                          | "You can't use multiple objects like that."    |
| *8*          | *Ambiguity problems*                                                 | "Which &lt;parse$&gt; do you mean, ... ?"      |
| 9            | Tried to &gt;VERB ALL where there is nothing to &gt;VERB             | "Nothing to get."                              |
| 10           | Object isn't known                                                   | "You haven't seen anything like that."         |
| 11           | Known object is not in current location                              | "You don't see that."                          |
| 12           | Can't do something (like, talking to a non-living object)            | "You can't do that with the object."           |
| 13           | Command was vague                                                    | "You'll have to be more specific."             |
| 14           | Referring to an object in a container or platform not actually there | "You don't see that there."                    |
| 15           | Trying to do a "held"-requiring verb with a non-held object          | "You are not holding that."                    |
| *16*         | *Tried to OOPS when there's nothing to correct*                      | "You'll have to make a mistake first"          |
| *17*         | *Tried to OOPS multiple words*                                       | "You can only correct one word at a time."     |

*error numbers in italics have defaults handled by the Hugo engine*
