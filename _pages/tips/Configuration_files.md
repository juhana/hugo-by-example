---
title: Configuration Files
permalink: /tips/configuration-files/
categories: 
  - Tips
---

This page cover's Hugo's ability to write individual values to file
(from which it can be read later). Games like Future Boy! and
Cryptozookeeper use this to save game options such as color schemes and
verbosity, but this is yet another feature where one is only limited by
his or her imagination. One of the more obvious uses would be to write a
couple games that use the same configuration file so that player stats
or inventory carry over from one to the next.

# writefile

The first thing one needs to do is to create the configuration file. For
interpreters that support it, it'll appear in the working directory (in
Windows 7, for instance, it's
C:\\Users\\USER_NAME\\AppData\\Local\\VirtualStore\\Program Files
(x86)\\Hugo).

    writefile "configuration_filename"
    {
        ! we'll get to this next
    }

#### writeval

Now, inside the block, we'll save our values using the `writeval`
statement. `writeval` can be used to save variables, property values,
etc.

    writefile "hugo_revenge_config"
    {
        writeval verbosity ! writes current verbosity value
        writeval (dwarf_treasure is known) ! writes true (1) if statement in parentheses is true, otherwise writes false (0)
    }

# readfile

To read from the previously created file, we use the `readfile`
statement:

    readfile "configuration_filename"
    {
         ! Bet you can't guess what goes here
    }

#### readval

The `readfile` block will have the same number of `readval`s as there
were `writeval`s. Using the `writefile` as a guide, we can reset all of
our global values or settings:

    readfile "hugo_revenge_config"
    {
         verbosity = readval ! sets verbosity to the first readval value
         if readval
              dwarf_treasure is known ! since there is a value in the second slot, we know that the dwarf_treasure object was known
         else
              dwarf_treasure is not known
    }

# FILE_CHECK

As the number of values in the configuration file increases, the easier
it'll be to make mistakes. There isn't any way for `writeval` and
`readval` to report errors, so it is recommended to use the
[hugolib.h](library/hugolib.h/)-defined
[constant](basics/constants/) `FILE_CHECK`, like such:

    routine SaveConfig
    {
         local test
         writefile "hugo_revenge_config"
         {
              writeval verbosity
              writeval (dwarf_treasure is known)
              test = FILE_CHECK
              writeval test
         }
         if test ~= FILE_CHECK  ! if the program didn't get this far, we know something is wrong
              print "An error as occurred."
    }

    routine LoadConfig
    {
          local test
          readfile "hugo_revenge_config"
          {
               verbosity = readval
               if readval
                    dwarf_treasure is known
               else
                    dwarf_treasure is not known
               test = readval
          }
          if test ~= FILE_CHECK
              print "Error reading file."
    }

We make sure to use `FILE_CHECK` for the last read and write value, so
if we accidentally skip a value somewhere along the way, the `test`
variable will have the wrong value and we'll know something is wrong.

# More Help

Roodylib has a "configuration file helper" extension that attempts to make some aspects of using configuration files easier.

# Sharing Strings Between Two Games (Hugo Homework)

The Hugo Book lists dictionary entries among the things that `writeval`
can save. The important thing to remember, though, is that it saves the
dictionary entry *address*, not the string itself. What this means is
that if you wrote two games that shared the same configuration file,
something like **writeval "apple"** will not be helpful, as "apple" will
almost certainly have a different address in each game.

The question is, how do we get around this?
<spoiler text="HINT"> Think [ASCII values](strings/ascii-values/)!
</spoiler> <spoiler text="CLICK FOR THE ANSWER"> First off, we'll have
to break "apple" down into its individual letters (whose values will be
the same in each game) and recreate it into a string array on the other
side. The second thing to be aware of is that we'll have to use the
[`dict`](strings/dict/) function in the second game to make sure it is
added to the dictionary table.

In the first game (the one saving the string), we'd have something like
this:

    array name_array[50]

    routine SaveConfig
    {
         local test2
         writefile "savefile"
         {
             local a
             text to name_array
             print "apple";
             text to 0
             for (a=0;a<49;a++)    ! this loop saves 49 characters, a bit of overkill
             {
                writeval name_array[a]
             }
             test2 = FILE_CHECK
             writeval test2
         }
         if test2 ~= FILE_CHECK  ! if the program didn't get this far, we know something is wrong
              print "An error as occurred."
    }

The second game would have something like this:

    $MAXDICTEXTEND = 512

    array name_array[50]

    routine LoadConfig
    {
          local test2
          readfile "savefile"
          {
             local a
             for (a=0;a<49;a++)
             {
                name_array[a] = readval
             }
             object_to_be_named.name = dict(name_array, 49)
             test2 = readval
          }
          if test2 ~= FILE_CHECK
          {
             print "Error reading file."
          }
    }

Of course, a real game would also need also need to fill `noun`
properties, and character names would need proper capitalization. Go
check out the [string manipulation](strings/string-manipulation/)
pages for that, man. </spoiler>
