---
title: Resources
permalink: /basics/resources/
categories: 
  - Basics
---

There may come a time when your story/game could use a little more
*oomph* than what can be provided by a text-only experience. Perhaps
images of the rooms would help the player remember where they are, or
some mood music would help make your story creepier. Or your PC gets
instructions on a video display, and you'd like to show the video
itself.

The Hugo system makes this relatively simple by setting up a **resource
file**. A resource file packages up all your pictures, music/sound
files, and videos in a cross-platform, compatible format.

Creating a resource file is much easier than creating the resources
(unless you're more artistic than me). Currently Hugo supports **JPEG**
images, **WAV**/**RIFF** audio files, **MOD**/**S3M**/**XM** music
modules, **MIDI**/**MP3** music files and **AVI** video files.

There is a limit of 255 resources per resource file, but your game can
use more than one resource file.

### Creating the resource file

    resource "resource_file_name"
    {
       "path\to\file.jpg"
       "path\to\file2.avi"
       "path\to\file3.mpg"
    }

**Sample code for Windows based development systems.**

    resource "MSTRYHS1"
    {
      "C:\HugoDevel\Mystery House\graphics\exterior.jpg"
      "C:\HugoDevel\Mystery House\graphics\interior.jpg"
      "C:\HugoDevel\Mystery House\graphics\note.jpg"
    ! Some more pictures here

      "C:\HugoDevel\Mystery House\music\spooky1.mp3"
      "C:\HugoDevel\Mystery House\music\spooky2.mid"
      "C:\HugoDevel\Mystery House\music\scream1.wav"

    ! Some more music and sounds
      "C:\HugoDevel\Mystery House\video\epi_lose.avi"
      "C:\HugoDevel\Mystery House\video\epi_win.avi"
    }

**Sample code for Linux, OS X and other Unix-like systems**

    resource "MSTRYHS1"
    {
      "/home/Gerynar/HugoDev/MysteryHouse/graphics/exterior.jpg"
      "/home/Gerynar/HugoDevel/MysteryHouse/graphics/interior.jpg"
      "/home/Gerynar/HugoDevel/MysteryHouse/graphics/note.jpg"
    ! Some more pictures here

      "/home/Gerynar/HugoDevel/MysteryHouse/music/spooky1.mpg"
      "/home/Gerynar/HugoDevel/MysteryHouse/music/spooky2.mid"
      "/home/Gerynar/HugoDevel/MysteryHouse/music/scream1.wav"

    ! Some more music and sounds
      "/home/Gerynar/HugoDevel/MysteryHouse/video/epi_lose.avi"
      "/home/Gerynar/HugoDevel/MysteryHouse/video/epi_win.avi"
    }

### Using resources in your game

#### Pictures

A picture can be displayed with the **picture** command

    picture "<resource_file>", "<picture>"

So, using our example resource file from above, if you need to display
the *exterior.jpg* file, the command would be:

    picture "MSTRYHS1", "exterior"

If the Hugo interpreter does not support graphics (such as the **he**
text-based Hugo Engine) the `picture` command will have no effect. If
the picture is not found, or a recoverable error occurs during loading
of the pictures, the game will continue running (without the picture
being displayed).

the **resource.h** [header](definitions/headers/) file has a couple of
useful routines for managing graphics.

    LoadPicture("resource_file", "picture_file_name")
    LoadPicture("picture_file_name)

    PictureinText("resource_file", "picture_file_name", width, height, preserve)
    PictureinText("picture_file_name", width, height, preserve)

''The versions of the routines that don't include a
*resource_file_name* in them will attempt to find the resource file
that was accessed. It is recommended to use the version that specifies a
resource file name to help keep the system from getting confused if
there is more than one resource file used in the game.''

**LoadPicture()** is basically a simple wrapper for the picture
statement, providing the additional service of checking
`display.hasgraphics` to ensure that the interpreter can display
pictures.

**PictureinText()** is a little more complex (behind the scenes). It
allows a picture to be displayed in the normal flow of text in the main
window. Most games that use graphics use a separate
[window](input-output/window/) so that it does not interrupt the flow of
the main text of the game.

-   The **width** and **height** arguments give the fixed-width
    character dimensions of the display area. Due to the fact that
    different displays have different width/height possibilities, it is
    recommended to calculate these based on `display.screenwidth` and
    `display.screenheight` instead of passing fixed values.

<!-- -->

-   The **preserve** argument specifies the number of lines (one or
    more) at the top of the screen are protected from scrolling off.

#### Sounds/Music

Sound and music are played with the following commands

    sound [repeat] <resource_file_name>, <sound_file_name>[, <vol>]
    music [repeat] <resource_file_name>, <music_file_name>[, <vol>]

The **repeat** keyword is optional. If used, the sound/music will loop
continuously until either you stop it yourself, or until another
song/sound is started.

The `<resource_file_name>` argument is the name of the resource
file containing the sound or music you're wanting to play, the
`<sound_resource_name>` or `<music_resource_name>` is the name
of the sound or song you want to play.

`<vol>` is an optional volume setting (0% - 100%) for the resource to
be played at.

To stop any currently playing sound or song use:

    sound 0
    music 0

The **resource.h** header file provides a set of wrapper functions to
manage the playing of audio resources.

    PlaySound(resource_file_name, sound_resource_name, loop, force)
    PlayMusic(resource_file_name, song_resource_name, loop, force)
    PlaySound(SOUND_STOP)
    PlayMusic(MUSIC_STOP)

If the **loop** is set to *true*, it would be the same as using the
`repeat` keyword. Set it to *false* if you want the audio only played
once.

If **force** is set to *true* the song will be restarted even if the
resource is already playing.

The last two functions listed above stop the sound or song respectively.

Using the resource file we set up above, playing sounds and music would
work as follows:

    ! somewhere near the top of the source code
    #include "resource.h"

    routine init
    {
    ! Normal init stuff here

       ! Play our intro song 'spooky1.mp3'
       PlayMusic("MSTRYHS1", "spooky1", false, true)
    }

    ! in a routine, where we want a sound played
    object small_box "small box"
    {
    ! other stuff

       after
       {
          object DoOpen
          {
            ! play a scream when the small_box is opened
            PlaySound("MSTRYHS1", "scream1", false, false)
            ! do other stuff for the game
          }
       }
    }

#### Videos

Currently, there is no wrapper function in **resource.h** for playing
videos, but like the other multimedia commands, it is not all that
difficult to play a movie file.

    video [repeat] <resource_file_name>, <video_name>[, <vol>, <bkground>]

Like the *sound* and *music* command, the optional **repeat** keyword
will cause the video to loop. The optional parameters *vol* controls
volume and *bkground* is a true/false option. If it's set to *true* the
video will play as a background process and the player can still enter
commands. If it is set to *false* or not used, most interpreters that
support video will play the video and wait until it is finished before
it lets the player type anything.

Code Sample: An video epilogue for the end of a game.

    ! our routine to replace the end
    replace EndGame(end_type)
    {
       cls                    ! clear the screen
       select end_type
          case 1
          {
             video "MSTRYHS1", "epi_win"
          }
          case 2
          {
             video "MSTRYHS1", "epi_lose"
          }

    ! rest of the code to allow the player a chance to restart/restore/quit/etc...

    }
