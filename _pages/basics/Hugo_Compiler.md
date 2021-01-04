---
title: Hugo Compiler
permalink: /basics/compiler/
categories: 
  - Basics
---

The Hugo Compiler is the program that takes the source code, the text
you write, and turns it into a story file that the interpreters can play
your game.

This article will describe using the compiler from the command line.

### Notes

In Microsoft Windows, you can get to the command line by clicking on the Start menu, selecting run and entering  `commmand` (Windows XP) or `cmd` (Vista/Windows 7)

In Linux, just open your favorite terminal emulator (gnome-terminal/xterm/konsole).

In Mac OS X, open the Terminal.app.

## Command Line Usage

The command to compile your source file is <b>hc</b>.

The full structure of the command is:

    hc [-switches] <sourcefile[.hug]> [objectfile]

-   **hc** the actual command to compile the source
-   **\[-switches\]** optional switches (to change the default behavior
    of the compiler)
-   **&lt;sourcefile\[.hug\]&gt;** the source code you're compiling.
    (**.hug** is optional, if your file is called *GreatGame.hug*, the
    hc program is smart enough to add the **.hug** if you leave it off.
-   **&lt;objectfile&gt; the name of the game file (if you want it to be
    different than the name of the source).

The simplest command line command is simply **hc &lt;sourcefile&gt;**. For
example, if your source file is called *GreatGame.hug* you can just type
the following to compile your game.

<div class="command">

`hc GreatGame`

</div>

### Command Line Switches

| Switch | Action                                                | Description                                                                                                                                                                                                                            |
|--------|-------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **-a** | **A**bort compilation on *any* error                  | Any error, no matter how small causes the compiler to quit right there, without checking the rest of the code. Helpful if there is an explosion of error messages.                                                                     |
| **-d** | Compile as an .HDX (**D**ebuggable executable format) | This format includes extra information in the story file to make debugging information easier (line numbers, variable names, etc...                                                                                                    |
| **-e** | **E**xpanded error format                             | Normally, the Hugo compiler error messages are rather terse, easy for a computer to understand, but may be puzzling to new users. This option expands the information about the errors                                                 |
| **-f** | **F**ull object summaries                             | This causes the compiler to output a list of detailed information about each [object](/basics/objects/) in the sourcefile.                                                                                                           |
| **-h** | Compile in .HLB (Precompiled **h**eader format)       | This generates a precompiled header. Useful if there many files in your program as it will help speed up compilation as you work on your game.                                                                                         |
| **-i** | Display debugging **i**nformation                     | Tells the compiler that after finishing compilation to print out a list of all symbols used and information associated with them.                                                                                                      |
| **-l** | Print **l**isting to disk as <sourcefile>.lst         | Records all compiler output to a file. The default name is <sourcefile>.lst                                                                                                                                                            |
| **-o** | Display **o**bject tree                               | Outputs a list of all objects you created, along with a visual representation of their inheritance                                                                                                                                     |
| **-p** | Send output to standard **p**rinter                   | Print the compiler output to the standard printer. *Not available in all versions of the compiler*                                                                                                                                     |
| **-s** | Print compilation **s**tatistics                      | Displays a summary of various compiler statistics.(Number of lines compiled, objects, routines, properties, dictionary words and other elements of a .HEX file)                                                                        |
| **-t** | Text to listfile for spell checking                   | Sends textual output to a file so you can run a spell check on it.                                                                                                                                                                     |
| **-u** | Show memory **u**sage for objectfile                  | Shows a breakdown of memory used by the .HEX file for things such as the object table, property table and executable code.                                                                                                             |
| **-v** | **V**erbose compilation                               | Displays real-time compilation information (number of lines compiled, and a percentage of the compilation completed) *not available in all versions of the compiler*                                                                   |
| **-w** | **W**rite <objectfile> despite any errors             | Normally, when the compiler runs into errors, it will not create the .HEX file. This option forces the compiler to create the .HEX file anyways. Useful if you want to test a section of code that is not causing the compiler errors. |
| **-x** | Ignore switches in source code                        | This causes the compiler to ignore any of these switches that are used inside the source file, overriding what the author wanted done.                                                                                                 |

These switches can also be combined such as: `-ls` which combines both
the -l switch and the -s switch.

### Limit Settings

Because computers do not have an infinite amount of memory, the Hugo
compiler has limits on how many objects, attributes and other elements.
To help manage the memory used by a game, there is a default set of
limits that may not always work with your game. The defaults generally
work for most games, but may need tweaking if your game grows quite
large.

To see what the limits are set to on your system, just type the
following:

<div class="command">

hc $list

</div>

*Note:* In Linux or Mac OS, you will need to "escape" the $ with a
backslash \\ so that the command shell doesn't try to interpret $list as
a variable instead of the command $list

You should see something like the following:

<div class="output">

    $ hc \$list
    ---------------------------------------------------------------
    Static limits (non-modifiable):
        MAXATTRIBUTES     128   MAXGLOBALS        240
        MAXLOCALS          16
    ---------------------------------------------------------------
    Default limits:
        MAXALIASES        256   MAXARRAYS         256
        MAXCONSTANTS      256   MAXDICT          1024
        MAXDICTEXTEND     (0)   MAXDIRECTORIES     16
        MAXEVENTS         256   MAXFLAGS          256
        MAXLABELS         256   MAXOBJECTS       1024
        MAXPROPERTIES     254   MAXROUTINES       320
        MAXSPECIALWORDS    64

    Modify non-static default limits using:  $<setting>=<new limit>
    ---------------------------------------------------------------

</div>

For example, if you need more than 256 aliases, the option
**$MAXALIASES=350** needs to be added to the command line like so:

<div class="command">

hc $MAXALIASES=350 GreatGame
*or*
hc \\$MAXALIASES=350 GreatGame
*on Linux or OS X*

</div>

<table>
<thead>
<tr class="header">
<th><p>Limit Name</p></th>
<th><p>Definition</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><strong>MAXATTRIBUTES</strong></p></td>
<td><p>The maximum number of definable attributes, not counting aliases (CANNOT BE CHANGED)</p></td>
</tr>
<tr class="even">
<td><p><strong>MAXGLOBALS</strong></p></td>
<td><p>The maximum bumber of definable global variables (CANNOT BE CHANGED)</p></td>
</tr>
<tr class="odd">
<td><p><strong>MAXLOCALS</strong></p></td>
<td><p>The maximum number of local variables allowed in a routine, including the arguments passed to the routine (CANNOT BE CHANGED)</p></td>
</tr>
<tr class="even">
<td><p><strong>MAXALIASES</strong></p></td>
<td><p>The maximum number of aliases that may be defined for attributes and/or properties<br />
Set with <em>$MAXALIASES=<num></em></p></td>
</tr>
<tr class="odd">
<td><p><strong>MAXARRAYS</strong></p></td>
<td><p>The maximum number of arrays that may be defined (not the total array space)<br />
Set with <em>$MAXARRAYS=<num></em></p></td>
</tr>
<tr class="even">
<td><p><strong>MAXCONSTANTS</strong></p></td>
<td><p>The maximum number of constants that can be defined<br />
Set with <em>$MAXCONSTANTS=<num></em></p></td>
</tr>
<tr class="odd">
<td><p><strong>MAXDICT</strong></p></td>
<td><p>The maximum number of entries that the compiler can put in the dictionary table.<br />
Set with <em>$MAXDICT=<num></em></p></td>
</tr>
<tr class="even">
<td><p><strong>MAXDICTEXTEND</strong></p></td>
<td><p>The number of bytes (not entries) available for dynamic dictionary extension during runtime. One dictionary entry requires a byte for every letter and an extra byte that holds the total number of letters.<br />
Set with <em>$MAXDICTEXTEND=<num></em></p></td>
</tr>
<tr class="odd">
<td><p><strong>MAXEVENTS</strong></p></td>
<td><p>The maximum number of global events or object-linked events.<br />
Set with <em>$MAXEVENTS=<num></em></p></td>
</tr>
<tr class="even">
<td><p><strong>MAXFLAGS</strong></p></td>
<td><p>The maximum number of compiler flags that may be set at one time.<br />
Set with <em>$MAXFLAGS=<num></em></p></td>
</tr>
<tr class="odd">
<td><p><strong>MAXLABELS</strong></p></td>
<td><p>The maximum number of labels that may be defined during compilation.<br />
Set with <em>$MAXLABELS=<num></em></p></td>
</tr>
<tr class="even">
<td><p><strong>MAXOBJECTS</strong></p></td>
<td><p>The maximum number of objects that may be defined during compilation.<br />
Set with <em>$MAXOBJECTS=<num></em></p></td>
</tr>
<tr class="odd">
<td><p><strong>MAXPROPERTIES</strong></p></td>
<td><p>The maximum number of properties that may be defined.<br />
Set with <em>$MAXPROPERTIES=<num></em></p></td>
</tr>
<tr class="even">
<td><p><strong>MAXROUTINES</strong></p></td>
<td><p>The maximum number of stand-alone routines that may be defined.<br />
Set with <em>$MAXROUTINES=<num></em></p></td>
</tr>
</tbody>
</table>

### Sample Compilation

Here is a sample of what you might see when you run a compilation (with
no errors in source)

    $ hc -ls GreatGame

    ===============================================================================
    HUGO COMPILER v3.1.03 STATISTICS FOR:  GreatGame.hug
    12/07/10 22:16:57
    ===============================================================================
    Compiled 13321 lines in 9 file(s)

    Objects:       85 (maximum  1024)      Routines:   220 (maximum   320)
    Attributes:    25 (maximum   128)      Events:       4 (maximum   256)
    Properties:    60 (maximum   254)      Labels:      13 (maximum   256)
    Aliases:       34 (maximum   256)      Globals:     55 (maximum   240)
    Constants:     94 (maximum   256)      Arrays:      11 (maximum   256)

    Words in dictionary:   570    Special words:    24    Verbs:   119

    Object file:  GreatGame.hex (103929 bytes)
    (debuggable format)
    List file:    GreatGame.lst

    Elapsed compile time:  1 seconds
    ===============================================================================

### Directories

When compiling your source code, the Hugo compiler needs to know where
the files you're using are stored. If you don't give it specific
instructions, it will assume that all the files are in the same
directory (folder) where you run the **hc** command from. This means
that all of the Hugo Library files, resource files, and so on need to be
kept in the same directory as your game source.

Working this way can waste disk space if you have several copies of the
library files on your computer. It's more effecient to keep the library
files in one place, and then tell the compiler where to look for them
when you *\#include* them in your source code.

You can tell the compiler where certain files are kept by adding a bit
of code on the command line (like the switches above).

Currently there are six 'directories' that the Hugo compiler understands
on the command line

| Directory Name | Files found there                                                       |
|----------------|-------------------------------------------------------------------------|
| **source**     | Your source code file(s).                                               |
| **object**     | Where the .HEX files go after the compiler is done compiling your code. |
| **lib**        | Library files that get **\#include**d or **\#link**ed.                  |
| **list**       | Location of the .LST file goes (if specified)                           |
| **resource**   | Resources for the *resource* file list                                  |
| **temp**       | Temporary comile-time files.                                            |

You use the following syntax to declare a directory for the Hugo
compiler `hc @directory=`<real-path-to-directory> **Note:** In Linux/OS
X, depending on the shell you are using (usually Bash), you will need to
escape the **@** symbol to make sure that the shell doesn't try to
interpret the @dir as a command. Samples:

**Windows**

<div class="command">

hc @lib=C:\\Users\\CoolDude\\HugoLibrary GreatGame.hug

</div>

**Linux/OS X**

<div class="command">

hc \\@lib=/home/coolDude/HugoLib GreatGame.hug

</div>

To avoid the hassle of always remembering to type @dir=path-to-whatever
when you want to compile your source, you can set up what are known as
*Environment Variables*. These variables hold information that the OS
can use to keep track of information. The names of the environment
variable is in the form of **HUGO_*directory***. ie the library
variable would look like: **HUGO_LIB**, the *object* directory would be
**HUGO_OBJECT**, etc.

In Windows, environment variables can be set by the following steps:

1.  Right-click on **My Computer** (Windows XP) or **Computer**
    (Vista/Windows 7)
2.  Click on the **Advanced** tab
3.  Click **Environment variables**
4.  Click **New** and add the name (HUGO_*directory*) and the value

Or, you can download a free program called *varpanel* that makes editing
environment variables much easier. 
[varpanel download](http://www.softpedia.com/get/Programming/Other-Programming-Files/Varpanel.shtml)

In Linux/OS X (using the bash shell), edit your **.bashrc** file. (Yes,
there is a period in front of the name) and add the following line(s)

<div class="command">

**export HUGO_LIB=*"/path/to/hugo/library"***

</div>

After adding the lines to bash, you'll need to close and re-open the
terminal for the changes to take affect.

### Platform-Specific Notes

The Windows frontend will always create a .LST (list) file regardless of
what switches you have set. Switches only affect what goes into the .LST
file.
