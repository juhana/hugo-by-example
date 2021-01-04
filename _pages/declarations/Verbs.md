---
title: verb
permalink: /declarations/verb/
categories: 
  - Declarations
  - Verbs
---

describes how a command the user can type is to be interpreted at run
time. The general format is

    verb "first_command" [, "second_command [, ...] ]
       * ["optional string" or optional_object or optional_attribute  [... ] ]  <verb routine>
       * ["optional string" or optional_object or optional_attribute]/[... ] [...] ]  <verb routine>

It would be used similar to this:

       *                         <verb routine for the verb with no parameters>
       * "word2"                 <verb routine for the verb with this string as a parameter>
       * object                  <verb routine for the verb with an object as a parameter>
       * attribute               <verb routine for the verb with an object as a parameter that has this attribute>
       * "word3"/"word4"         <verb routine for the verb with either string as a parameter>

These can be combined to create very complicated commands. Here is an
example:

    verb "command"
       *                         DoCommand
       * "word2"                 DoCommand2
       * female                  DoCommand5
       * object                  DoCommand3
       * female "to" "go" object DoCommand6
       * "word3"/"word4"         DoCommand4

The first line means that if the command "command" is typed, and no
[parameters](/definitions/parameter/) were given, the
[routine](/routines/) **DoCommand** will be run as a
[verb](/declarations/verb/) for that verb. The other lines are routines for
the verb with different parameters passed to it, e.g. if the user types
the command "command word2" , **DoCommand2** will be run; the verb
"command" typed in followed by the name of an object as the parameter
will cause the routine **DoCommand3** to be run, etc.

Consider there is an object named Table that has been defined, and a
female_character named Leslie, if the user typed in the verb "Command
leslie" would run DoCommand5, but the verb "command table" would run
DoCommand3 (table is not female). If the user types in the verb "Command
leslie to go north" then command6 would be executed. It would also be
executed if the user typed in "Command leslie to go table" which might
not make sense in the particular game.

The use of a slash allows either of the parameters to be used
interchangeably, e.g. if the user typed the verb "command" followed by
either "word3" or "word4" then the verb routine **DoCommand4** will run.

While the name of the routine could be anything, it is common practice
to name a verb routine beginning with "Do", followed by the particular
verb or the equivalent, to differentiate it from routines used for other
purposes, e.g. the [standard library](/library/)
defines the verb routine for the "exit" verb as DoExit, the routine for
the "look" command as DoLook, etc.

When the user types a verb that has an object as a parameter, the
standard library defined variable *object* will contain the first
specified object, which can be tested by comparing it to another object
or examining the [name](/properties/name/) property, e.g. if you have the
following definition

    object wheatstalk "wheat"
    {
     ... ...
    }

then you can test for whether this was the object referenced with

        if (object.name = "wheat") {
       ...  other code ...
        }

or

        if (object = wheatstalk) {

        }

If you have a routine which will act on both a command with a parameter
or without one, you can test whether an object was given as the
parameter through the use in a routine of a reference to
**[object](/globals/object/)** or *not object*, e.g.

        if (object) {
    ! code which executes if the user gave an object as a parameter
        }

or

        if (not object) {
    ! code which executes if the user did not give an object as a parameter
        }

See Also: [routine](/routines/)
