---
title: Selection Sort
permalink: /tips/selection-sort/
categories: 
  - Tips
---

This is a [routine](routines/) to perform a selection sort on
an [array](basics/array/) in descending order. Please feel free to
modify and improve. [Here](http://en.wikipedia.org/wiki/Selection_sort)
is the Wiki entry for Selection Sort.

*See also: [Sort.h](contributions/sort.h/) (a selection sorting library
contribution)*

<!-- -->

    routine SelectionSort(sourceArray, n, reversable)
    {
    ! Defaults to descending sort order.
    ! The argument 'reversable' should be true or false. True will initiate an ascending search.
    ! n is the arrayLength. If 0, it will obtain the arrayLength automatically.
    ! Currently does not handle capital letters and lower case letters equally.

    local iPos, iMin, swap, i

        if n = 0
        {
            n = array sourceArray[]
        }

        for (iPos = 0; iPos < n; iPos++)
        {
            iMin = iPos

            for (i = iPos+1; i < n; i++)
            {
                if reversable = true
                {
                    string(_temp_stringExtra, array sourceArray[i], 255)
                    if ~(StringDictCompare(_temp_stringExtra,array sourceArray[iMin]))
                    {
                        iMin = i
                    }
                }
                else
                {
                    string(_temp_stringExtra, array sourceArray[iMin], 255)
                    if ~(StringDictCompare(_temp_stringExtra,array sourceArray[i]))
                    {
                        iMin = i
                    }

                }
            }
            if ( iMin ~= iPos )
            {
                !swap(a, iPos, iMin);
                swap = array sourceArray[iPos]
                array sourceArray[iPos] = array sourceArray[iMin]
                array sourceArray[iMin] = swap
            }
        }
    }
