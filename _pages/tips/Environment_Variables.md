---
title: Environment Variables
permalink: /tips/environment-variables/
categories: 
  - Tips
---

Now, I imagine all sorts of programming languages have support for
"environment variables", but Hugo was my first exposure to it.
Basically, it's a nice way to instruct Hugo where you keep your files or
want them to go without having messy compilation commands or keeping
everything in one directory.

### Windows

First, look up how to set up environment variables for your version of
Windows. In Windows 7, right-click on the computer icon on your desktop
and select Properties. Click on "Advanced System Settings" on the side
of the window. Click on the "environment variables" button.

## Setting the Variables

Then, set the following environment variables:
**HUGO_SOURCE** - directory where you'll be keeping your source files
**HUGO_OBJECT** - directory where you want new compiles to show up
**HUGO_LIB** - directory where you have the Hugo library files

Those are the most important, but you can also have the following if you
want:
**HUGO_LIST** - where you want .lst files to show up (files that list
compilation statistics)
**HUGO_RESOURCE** - where to look for resource files
**HUGO_TEMP** - temporary compilation files

### Linux

**Note:** These instructions assume that you're using bash as your
shell.

Using your favorite editor, open up the .bashrc file in your /home
directory. Near the end, add the following line(s)

    # Hugo environment variables
    export HUGO_LIB="/path/to/hugo/library"
    export HUGO_OBJECT="/path/to/new/compiles"
    export HUGO_SOURCE="/path/to/hugo/source"

These variables won't take affect until the next time you log into a
terminal.

## Now you're set

Now, unless your command line or game source tells Hugo to look
specifically somewhere else for necessary files, it'll look in those
preset directories.

Anyhow, for me, it helps keep my command lines and directories a lot
prettier and more organized.
