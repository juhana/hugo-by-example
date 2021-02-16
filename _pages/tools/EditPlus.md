---
title: EditPlus
permalink: /tools/editplus/
categories: 
  - Tools
---

EditPlus is a commercial text editor for Windows. Most of its features
are described in further detail on the [Supported Editors](tools/editors/)
page, but you can download a zip
[here](assets/editplus.zip) that has
several additional files to use with it, including some clip text files,
an autocomplete file (created by Robb Sherwin), and some templates.

# Favorite Features and How To Use Them

![EditPlus](assets/images/Cliptextshow.jpg)

**Clip Text:** "Clip text" allows for quick-clicking to add text into
wherever the cursor is in the current open file. It is both a time saver
and a memory helper. Personally, I use it for the ASCII table (for when
I need to do less-common characters), Hugo colors (to remind me both
exactly which colors are supported and their number values), and the
names (and how to call) all hugolib.h routines. Really, though, they can
be used for anything you have trouble remembering (like that pesky
_temp_string array!).

**To use:** Click on "Clip Text" in the directory-browsing area of the
screen. Then, to start a new clip text, right-click on the title of the
current clip text and select "New." Alternatively, if you have some
pre-made clip text files available (like those in the .zip above), just
drop them in EditPlus User Application Settings folder.

**Column Marker:** This is probably one of the more humble features.
All it is is a line to let you know where *X* characters end. I keep a
column marker at 80 characters so that when I share code, it is most
certain to fit on other people's screens, no matter their screen ratio.

![EditPlus](assets/images/Findinfiles.jpg)

**Find In Files:** "Find In Files" lets you search a bunch of files
at once. It is perfect when scouring Hugo code for examples of this or
that. You can search by directory or, if you have set up projects, you
can search by project, too. 

![EditPlus](assets/images/Projectshot.jpg)

**Function List:** "Function list" looks for whatever text you
specify and lists them in a floating window. If you double-click on any
entry, EditPlus will jump to that part of the file. It's a quick way to
get from routine to routine (or object to object).

**To use:** In Preferences, click on "settings & syntax" and make sure
the Hugo syntax file is selected. Then, click on the "function
patterns". Fill one of the two entries with:
`^(object\|option\|room\|character\|player_character\|door\|female_character\|class\|component\|scenery\direction\|remote_object\|supercontainer\|routine\|replace\|daemon\|fuse\|event\|verb\|xverb\|global\|constant\|property\|synonym)`.

That syntax tells EditPlus to look for any of those words when they
start a line. Then, in the main program, under Search, select Function
List to open up your floating function list window.

**Project Management:** As your game gets larger, it'll likely
consist of more and more files. A text editor's ability to manage
"projects" allows you to pull up other files quickly (or pull up files
from other projects, too). It doesn't take long for it to be an
invaluable feature. Also, "Find in Files" will allow you to search for
specific code by project.

**To use:** Under "Projects", select "Edit Projects" to make a new
project. Projects will then show up in your document-browsing area.

![EditPlus](assets/images/Splitter.jpg)

**Splitter:** The Splitter feature allows you to look at up to four
parts of one file at once. It could be useful when trying to understand
a long routine or see how different routines interact with eachother.

**To use:** Under "Window", select "Splitter" and then "Split".
Configure the distribution of the split windows how you like. To turn it
off, drag the distribution bar to the corner so one window takes up the
entire screen.

![EditPlus](assets/images/Templates.jpg)

**Templates:** Templates are the text editor version of shell files. I
personally have two different versions of Hugo shell file templates (and
some grammar and "general extension" templates, too). If I select one, a
shell file is opened. If I try to save it, it'll prompt me for a name to
save the file, unlike an actual shell file, which would require me to
rename the file or risk overwriting something.

**To use:** Go to Preferances. Go to Templates. Click "Add" and name
your new template. Delete templates you don't use. Now clicking on the
applicable template icon in the User Bar should open up a fresh file for
you.

**User Tools (and Configurable Toolbar):** Also in the "User Bar" are
buttons called "User Tools". You can associate a button to run a
particular command line. For instance, I have mine set up to do the
following:

1.  Compile the game normally.
2.  Compile a debuggable version.
3.  Open the latest compiled game in the regular interpreter.
4.  Open the latest compiled debuggable game in the debugger.
5.  Open the latest compiled game in Gargoyle.
6.  Compile with a spelling dump.
7.  Open the latest .LST file.
8.  Open the latest compiled game with Hugor.

So, yeah, I've found it very useful, especially since I've had problems
with the official Windows compiler frontend (it hates when I switch
directories after having compiled something else). It also helps out to
set up your [environment variables](tips/environment-variables/),
though.

**To use:** Under "Tools", select "Configure User Tools" and set up
each individual action (You can add icons if you'd like, too). That
should be that, but if your tools aren't showing up, under "Tools," go
to "User Tool Group" and make sure the right tool group is selected.

**Autocomplete:** Included in the .ZIP above is a Hugo autocomplete
file that can be used with EditPlus. Autocomplete, as you might guess,
finishes typing certain things for you. You can include it from the
"syntax and settings" page in Preferences. You might find that you don't
like some of the "autocompletions" and will want to modify some to
better suit your style. That is all up to you!
