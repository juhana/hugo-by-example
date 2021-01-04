---
title: Introduction
permalink: /hugo/introduction/
categories: 
  - Basics
---

The purpose of this page is to introduce the Hugo Language and the Hugo
System. It is recommended that someone go read the 
[Hugo Book](/hugo/hugo-book/) before reading Hugo By Example, but this
page may serve as a quick overview of Hugo, as far as its programming
style is concerned.

**Hugo** is a programming language and design system for interactive
fiction created by Kent Tessman. While not as popular as other IF
development languages, it is still used, particularly for multimedia
interactive fiction.

## Language Construction

The Hugo language is a hybrid of several features to provide a command
processing system. The system consists of a [verb](/declarations/verb/)
definition section, a **[property](/properties/)** and
**[attribute](/attributes/)** definition section, an
**[object](/basics/objects/)** definition section, and a code section.
One may assign multiple names to the same attribute or property through
the [alias](/basics/alias/) parameter to an attribute or property.

The language is not case sensitive, although much of the code base in
the standard library uses *camel case* (a practice where a word
indicates the parts of it by inserting capital letters at certain
points, e.g. a variable holding time and temperature might be defined as
**TimeAndTemperature**) for identifiers.
Identifiers may be up to 31 characters, must start with a letter, and
may contain letters, numbers and underscores.
[Strings](/strings/) are defined by surrounding them with a
double quote ( " ). Where it is necessary to include a double quote in a
string, it may be escaped by preceding it with a backslash, i.e. \\", so
that the string "please tell him, "go to the store," and do it now"
would be rendered as "please tell him, \\"go to the store,\\" and do it
now". Continuations must be explicitly marked
with a backslash character, with three major exceptions:

1.  **Quoted strings.**
        print "The engine will properly
               print this text, assuming a
               single space at the end of each
               line."
2.  **Lines ending with a comma** Like:
        x[0] = 1, 2, 3, ! array assignment x[0]..x[4]
               4, 5
3.  **Lines ending with `and` or `or`**
        if rabbit is living or
            rabbit in location

Continuations look like this:

    x = 5 + 6 * \
        higher(a, b)

The system provides for procedures, called a
"[routine](/routines/)" which may optionally return a
value. All executable statements must be within a
routine, there is no "default" mode to execute code outside of a
routine. Comments may be specified anywhere that
white space is acceptable, and are indicated by an exclamation point ( !
). This causes anything remaining on the line from that point on to be
ignored. A special type of [block comment](/basics/block-comment/) for
commenting out a large area may be used by having the first two
characters on a line begin with the comment !\\ and the block comment is
closed by the next occurrence of the inverse string \\! .

Where a "[block](/definitions/block/)" is needed - a set of related values
or a particular piece of executable code - it is indicated by encasing
it in the open brace character ( { ) and closing it with the ( } ),
similar to the same functionality in the C programming language. As with
a number of other programming language, Hugo borrows from C for a number
of features, including "escaping" some values by preceding them with a
backslash, the use of the [++](/operators/++/) and [--](/operators/--/)
symbols to increment and decrement a variable, and the { and } braces
for block begin and block end, as noted earlier. Hugo borrows the use of
the "print" command for displaying variables and the use of the
semi-colon ( ; ) from the BASIC programming language to indicate output
that is not to be broken by a new line.

There are two mandatory routines, one named [init](/routines/init/) and
one named [main](/routines/main/). `init` is run once when the program
starts (or is restarted), and as the name implies, initializes anything
the game needs to do. After `init` ends, `main` is run. It is run again
after every turn- a "turn" being a command entered by the player that
has been accepted by the game's parser. The main routine is used to do
the typical housekeeping on each turn. The user is prompted for input,
the parser processes the input to translate it into a verb and options
to the verb, then determine the routine that processes that verb. The
routine then returns a set of responses to the verb and options (if
any), and the user is then prompted to type in a command.


See also: [Game Loop](/loops/game-loop/)

The system requests commands and continues to do so until a routine
indicates the program is over. Since the system was originally designed
for writing of games, the determination of the program being over is
typically because either because the player "won" according to the rules
for that game, or because the player "lost".

### Verbs


Main article: [Grammar](/basics/grammar/)

In the verb definition section, one begins by defining each command,
known as a "verb" in which the code defines the verb as a quoted string.
One then lists, one line at a time, each of the parameters to be used
for processing the command issued. For example, if one has a command of
"incinerate" one would define a verb such as

    verb "incinerate"
       *                           DoIncinerate
       * object                    DoIncinerate
       * "me"                      DoSuicide

Where the first parameter means that, if the user running the program
types the command "incinerate" with no options, it runs the routine
"DoIncinerate". If the user types the command "incinerate" and names a
defined object, the DoIncinerate routine is run with the default object
(whose name is 'object') being assigned the value of whatever object the
user selected. If the user types the command "incinerate" followed by
the option "me" then the DoSuicide routine is run.

### Attributes


Main article: [Attributes](/attributes/)

The system allows for up to 128 different attributes to be defined.
Attributes are true/false values that represent conditions of an object.
All attributes defined in a program are available to any object. For
example, if an attribute of an object was hot or cold, one could define
an attribute for one or the other, then use "not" preceding an attribute
to test for the opposite condition. Attributes are defined by the
attribute command and the name of the attribute, such as:

    Attribute wet
    attribute female
    attribute cold
    attribute hard

One defines an attribute as being possessed by an object by the is
command, followed by the name of the attribute. To explicitly state that
the attribute is not possessed, one indicated by placing "not" before
the attribute on the is command.

### Properties


Main article: [Properties](/properties/)

Properties can contain essentially any value desired, including other
objects. While every object contains all defined attributes, an object
only contains the properties assigned to it when it is defined. A
property may be defined either with or without a value, and is defined
by the property command, the name of the property, and the optional
value, such as

``` c
property color
property weight 30
property size 4
property comment "whoa"
```

### Objects


Main article: [Objects](/basics/objects/)

Every thing that can be manipulated in a Hugo program is an object.
Objects have attributes and properties. All defined attributes are
available to all objects, but each object only has the properties
assigned to it when it is created. An object is a block of
specifications stating all of the information about it, begins with the
object command, the name of the object, an optional descriptive string
for the name, a block open symbol (the open brace ( ) the various values
to assign to the object, and a block close symbol (the close brace } ).
In the following object

``` c
object table "Kitchen Table"
{
  is hard
  is not female
  color brown
  size 10
}
```

The "table" object would have the hard attribute (set to true) and would
have the cold, female and wet attributes, which are all false. The
object would have been set to "is not female" by default, but explicitly
specifying it may be useful, or if the object is a copy of another
object but with additional or different properties or differing values
for the attributes. The color property of the table object could be
referenced through "table.color".

### Routines


Main article: [Routines](/routines/)

All action in a Hugo program takes place in a routine. In the example
given above, if the user had typed "Incinerate me" the DoSuicide routine
would have been executed:

    routine DoSuicide
    {

       "I can't allow you to do this,";
       print player.realname;"." ! realname would be a property holding the player's name
                                 ! as the actual name property holds "you" or "I"
    }

A quoted string by itself is treated as an implicit print statement. To
print actual values such as the name property (one of about six
properties automatically defined by the compiler) it is necessary to
specify it through the print command, by specifying the name of the
object and the property, separated by the dot ( . ) operator. To
reference an attribute, it may be tested in an if statement, like so:

       if object.type = table and (object.inches > 34)
       {
        print "The table is "; number table.inches ;" inches wide.  It won't fit through the door."
       }

### Other features

The Hugo language also provides for
[classes](/basics/object_classes/), which are more like types of
objects than full classes as used in object oriented programming
(classes do not have direct methods in Hugo). A property may be a value,
an array, or it may represent executable code such as an equivalent to a
method in a full object oriented language.
