---
title: Debugger
permalink: /basics/debugger/
categories: 
  - Basics
---

The Hugo Debugger is a very useful program for tracking down bad code.
`Appendix D` in the Hugo Book is devoted to explaining both it and the
HugoFix Debugging Suite. Don't get those two
confused, though. While HugoFix is a bunch of in-game commands that
allows game world manipulation and state monitoring, the debugger is an
external program that lets you watch the values of
[variables](/basics/variables/), word array elements, or whatever. It
even lets you run your game one line of code at a time, if need be.


=Quick Start= First off, [compile](/basics/compiler/) your game
with the **-d** switch so it compiles into the .HDX (Hugo Debuggable
Executable) format. Load that up into the debugger.

***Help! I've never used the debugger before! I've opened it up, and now
it's doing nothing! What the crap?***
Before jumping into your game, the debugger gives you a moment to set up
your watch values and breakpoints and things. Still, when you want to
proceed, go to to "Run" menu and select "Go." There, better?

***Okay, that's cool, but how would I actually \*use\* this to solve a
problem?***
Let's say you have a routine called `IsObjectAHelicopter` which returns
true if an object is of type `helicopter`, and it has been returning
false when you feed it things that are, indeed, helicopters.

In the debugger, you would go to the "Debug" menu and select
"Breakpoint," where you would enter "IsObjectAHelicopter" as the routine
you want the debugger to pause on. Then, you'd select "Go" from the
"Run" menu and play your game up until the point the routine is called.
When it's called, it'll kick you back to the debugger stuff screen, at
which point you can keep an eye on the code window as you use "Step"
from the "Run" menu to go through your routine line by line.

When the code does something you didn't want it to do, you can figure
out how you used the wrong conditional statement and fix your problem!

=Components= The next section will go into detail about the various menu
options.

### File / Edit

These menus don't have anything important worth covering.

### View

If not already shown, these options will bring various informational
windows to the forefront.

| Menu Option                | Summary of what it does                                                                                                            |
|----------------------------|------------------------------------------------------------------------------------------------------------------------------------|
| Code                       | Shows game code as it is processed                                                                                                 |
| Watch Window               | Shows all things set with the Debug menu "Watch" option                                                                            |
| Calls                      | Shows routine calls \*while they are open\* (won't show anything while game is waiting for input)                                  |
| Breakpoints                | Lists any breakpoints that have been set                                                                                           |
| Local Variables            | Shows any [local variables](/basics/variables/) that currently are defined (saves you the trouble of having to "Watch" for them) |
| Property/Attribute Aliases | Shows all property and attribute aliases                                                                                           |
| Help                       | Shows the help window                                                                                                              |
| Output                     | Switches to the game window                                                                                                        |

### Run

These options determine the speed at which you progress through the game
code.

| Menu Option    | Summary of what it does                                                                             |
|----------------|-----------------------------------------------------------------------------------------------------|
| Go             | go "full speed ahead" to the end of the turn or the next breakpoint                                 |
| Finish Routine | Finish off the current routine                                                                      |
| Step           | Progress to the next step (basically, the next line of code)                                        |
| Step Over      | Only lists steps within the current routine (code from other routines that are called is not shown) |
| Skip Next      | Skips the next line of code (without executing)                                                     |
| Step Back      | Goes back one step without undoing any modified values                                              |

### Debug

These options are WHERE THE MAGIC HAPPENS.

| Menu Option                | Summary of what it does                                                                                                                                                                                     |
|----------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Search code...             | Search the game code that has been executed \*so far\* (in the code window) for expressions, objects, whatever. You can use the Browse function to select anything from the list of Public Symbols.         |
| Watch                      | Select a value or expression that will be shown in the Watch window (see the note below)                                                                                                                    |
| Set Value                  | Manually set a variable or such to a specific value or give an object an attribute                                                                                                                          |
| Breakpoint..               | Declare a routine, object property, or code window address where you want the debugger to pause. Beyond your regular property names, you can also declare things like `Beforeroutines` and `Afterroutines`. |
| View Local Variables As... | If you need your local variables window to list something other (object names, etc.) than numerical values, you set that here.                                                                              |
| View All Public Symbols    | A browsable tree containing all of the game's public symbols                                                                                                                                                |
| Object Tree                | Show the game's object tree                                                                                                                                                                                 |
| Move object                | Moves an object to a new parent (doesn't change the location global variable so it shouldn't be used with the player object)                                                                                |


====Watching Values==== When you are watching values, you have several
options in what form you want to want to watch the value (object,
dictionary entry, routine address, etc.). It may take a while figuring
out what you want in any particular case. If you are working with a verb
routine where the variable are objects being fed into it, you'd probably
want "object." If the variable is a word in the word array, you would
want "dictionary entry." In other cases, you might just want the
numerical value of something. In many cases, there's no harm in watching
a value for several different things, so play with it until you get what
you want.

#### Watching Expressions

While you can't watch an object to get a list of its current attributes,
something you *can* do is enter an expression like "sportscoat is worn"
which will return 1 when true or 0 when false. This is useful when you
aren't sure if the code is setting attributes correctly (or really just
have no idea).
