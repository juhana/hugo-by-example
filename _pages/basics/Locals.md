---
title: Locals
permalink: /basics/locals/
categories: 
  - Basics
---

The **local** command defines a private variable which may be used only
within the routine where it is declared. A local overrides a
[global](/basics/global/) of the same name within that routine. It is
a kind of [declaration](/declarations/) and is not executable
[code](/definitions/code/).

        ! Local variable to store the number of chocolate cake slices.
        local  cake_slice_count

        local  table, chair
        local  car= "Ford", gas, pickup ="Chevy"  ! same as car="Ford", gas=0, pickup="Chevy"
        local  batteries = 5        ! number started with
        local  color="Viridian"
        local  primes = 2, 3 ,5 ,7 ,9
        local ingredients = "flour", "water", "concrete"

        ! Local variable to store the number of chocolate cake slices,
        ! with a starting value defined right at the start.

        local cake_slice_count = 10

We'll show the difference between a local and a global.

    global color = blue
    global xyzzy

    ! out here, color = "blue" and xyzzy = 0

    routine test1
    {
     local color = "viridian"
     local xyzzy = 5

    ! in here, color="viridian" and xyzzy = 5   ! changes to either are not seen outside this routine
    }

    routine test2
    {

     local xyzzy = 9

    ! in here, color="blue" and xyzzy = 9   ! changes to xyzzy are not seen outside this routine, but changes
    ! to the variable color are
    }

If a local is not given a value, it defaults to 0. Changes to a local do
not affect a global of the same name if one exists or a local of the
same name that may exist in any other routine.

See Also: [global](/basics/global/)