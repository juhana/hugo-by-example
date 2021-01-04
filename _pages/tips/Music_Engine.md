---
title: Music Engine
permalink: /tips/music-engine/
categories: 
  - Tips
---

This is an example of the music manager I wrote for my upcoming game
Cryptozookeeper.

The way it works is that it loads the amount of time a song should play,
in seconds. It then keeps track of what the time is in seconds. If the
time in seconds has passed the amount of time the game thinks the song's
length is, it fetches and plays another song. It can only check after
the player takes a turn. I also have it set to play a new song if a new
hour, day, month or year has occurred, to simplify the math. So a song
could be cut off and replaced with another if the hour changes.

You will need the following constants and variables in your game's code:

    constant MAXSONGS=5 !An integer that is one more than the number of songs your game has)
    global  music_volume = 80 ! For volume control


    MusicManager() ! Call this right before runevents()

    ! This xverb gives you information on the song being played, in case the player wants the name,
    ! but is set up below to help debugging by also giving the start and end time.
    xverb "musicstats"
        *                           DoMusicStats

The resource file itself, along with the number of seconds that each
song is:

    array TempTimeArray[5] = 0,0,0,0,0
    array LastTimeArray[5] = 0,0,0,0,0

    array MusicArray[MAXSONGS] = "beekeeper", "countsarebetter", "backinthehouse", "dropintheuniverse"
    array MusicArrayTime[MAXSONGS] = 241, 233, 209, 267

And then the resource file itself:

    resource "GAMEMUS"
    {
        ".\mp3\beekeeper.mp3"
        ".\mp3\countsarebetter.mp3"
        ".\mp3\backinthehouse.mp3"
        ".\mp3\dropintheuniverse.mp3"

    }

From here, include a file called MusicManager.hug or such. Here are the
contents of the MusicManager.hug that I used:

    routine MusicManager
    {
    local x, currentTime

    TempTimeArray[0] = GetSystemTimeValue(TIME_MONTH)
    TempTimeArray[1] = GetSystemTimeValue(TIME_DAY)
    TempTimeArray[2] = GetSystemTimeValue(TIME_HOURS)
    TempTimeArray[3] = GetSystemTimeValue(TIME_MINUTES)
    TempTimeArray[4] = GetSystemTimeValue(TIME_SECONDS)


    ! If we go to a different month, day or hour, play a new song.
    if ((LastTimeArray[0] ~= TempTimeArray[0]) or (LastTimeArray[1] ~= TempTimeArray[1]) or (LastTimeArray[2] ~= TempTimeArray[2]))
    {
        PlayNewSong
        for (x=0; x < 5; x++)
        {
            LastTimeArray[x] = TempTimeArray[x]
        }
        return
    }

    currentTime = GetCurrentTime()

    if currentTime > LastTimeAsNumber + MusicArrayTime[LastSongPlayed]
    {
        PlayNewSong()
        for (x=0; x < 5; x++)
        {
            LastTimeArray[x] = TempTimeArray[x]
        }
        return
    }

    return
    }


    routine GetCurrentTime()
    {
    local y

        y = TempTimeArray[3] ! y contains total number of minutes
        y = y * 60 ! minutes in seconds
        y = y + TempTimeArray[4]

        return y
    }


    routine GrabFirstRandomSong
    {
    local x

        x = random(MAXSONGS)
        x--

        ! To get a certain song to play for testing:
        !x = 53

        PlayMusic("GAMEMUS", MusicArray[x], music_volume, false, true)
        LastSongPlayed = x

        LastTimeArray[0] = GetSystemTimeValue(TIME_MONTH)
        LastTimeArray[1] = GetSystemTimeValue(TIME_DAY)
        LastTimeArray[2] = GetSystemTimeValue(TIME_HOURS)
        LastTimeArray[3] = GetSystemTimeValue(TIME_MINUTES)
        LastTimeArray[4] = GetSystemTimeValue(TIME_SECONDS)

        TempTimeArray[0] = GetSystemTimeValue(TIME_MONTH)
        TempTimeArray[1] = GetSystemTimeValue(TIME_DAY)
        TempTimeArray[2] = GetSystemTimeValue(TIME_HOURS)
        TempTimeArray[3] = GetSystemTimeValue(TIME_MINUTES)
        TempTimeArray[4] = GetSystemTimeValue(TIME_SECONDS)

        LastTimeAsNumber = GetCurrentTime()
    }

    routine PlayNewSong
    {
    local y,x, z
    x = LastSongPlayed

        while (x = LastSongPlayed)
        {
            y = random(MAXSONGS)
            y--

            x = y
        }

        PlayMusic("GAMEMUS", MusicArray[x], music_volume, false, true)
        LastSongPlayed = x

        LastTimeArray[0] = GetSystemTimeValue(TIME_MONTH)
        LastTimeArray[1] = GetSystemTimeValue(TIME_DAY)
        LastTimeArray[2] = GetSystemTimeValue(TIME_HOURS)
        LastTimeArray[3] = GetSystemTimeValue(TIME_MINUTES)
        LastTimeArray[4] = GetSystemTimeValue(TIME_SECONDS)

        TempTimeArray[0] = GetSystemTimeValue(TIME_MONTH)
        TempTimeArray[1] = GetSystemTimeValue(TIME_DAY)
        TempTimeArray[2] = GetSystemTimeValue(TIME_HOURS)
        TempTimeArray[3] = GetSystemTimeValue(TIME_MINUTES)
        TempTimeArray[4] = GetSystemTimeValue(TIME_SECONDS)

        LastTimeAsNumber = GetCurrentTime()
    }


    routine DoMusicStats
    {
    local currentTime, nextSongTime

    TempTimeArray[0] = GetSystemTimeValue(TIME_MONTH)
    TempTimeArray[1] = GetSystemTimeValue(TIME_DAY)
    TempTimeArray[2] = GetSystemTimeValue(TIME_HOURS)
    TempTimeArray[3] = GetSystemTimeValue(TIME_MINUTES)
    TempTimeArray[4] = GetSystemTimeValue(TIME_SECONDS)


    currentTime=GetCurrentTime

    "LastSongPlayed is ";
    print number LastSongPlayed

    ""

    "song id is ";
    print MusicArray[LastSongPlayed]

    ""

    "currentTime is ";
    print number currentTime

    ""

    "LastTimeAsNumber is ";
    print number LastTimeAsNumber

    ""

    "Current Song Length is ";
    print number MusicArrayTime[LastSongPlayed]

    ""

    "New song plays at ";
    nextSongTime = LastTimeAsNumber + MusicArrayTime[LastSongPlayed]
    print number nextSongTime

    }
