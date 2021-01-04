!\-----------------------------------------------------------------------------------------------------
!	Multikey.h v 1.0, by Jason McWright
!
!	This is a replacement for the verb routines DoLock and DoUnLock. It allows the verb routines 
!	DoLock and DoUnLock to recognize multiple key objects in a door's key_object property. With
!	this extension you can give a door as many key objects an you like.
!	It also provides additional messages that tell the player the conditions that need to be met
!	in order to lock/unlock a door (open/closed, locked/unlocked, no key, wrong key).
!
!	Note that these versions of DoLock/DoUnLock use some standard VMessages and some new messages
!	found in this file, called "MultiKeyMessages". Nothing in this file will interfere with existing
!	library messages or replacement messages.
!
!	To use this extension simply include it after verblib.h.
-------------------------------------------------------------------------------------------------------\!

replace DoLock
{
	local a, test_key, flag, not_xobject, not_in_player, xobject_flag

	if not CheckReach(object): return false

	if object is open
	{
		VMessage(&DoLock, 2)             ! "Have to close it first..."

		if xobject: if not InList(object, key_object, xobject): MultiKeyMessage(&DoLock, 5)
		else: if not SearchKey(object): MultiKeyMessage(&DoLock, 6)

		return true
	}

	if object is locked
	{
		VMessage(&DoLock, 1)             ! already locked

		if xobject: if not InList(object, key_object, xobject): MultiKeyMessage(&DoLock, 5)
		else: if not SearchKey(object): MultiKeyMessage(&DoLock, 6)

		return true
	}

	while object.#key_object > a and flag = false
	{
		a++
		test_key = object.key_object #a

		if xobject
		{
			if xobject = test_key
			{
				flag = true
				not_xobject = false
				xobject_flag = true
			}
			else: not_xobject = true
		}

		if not xobject
		{
			if Contains(player, test_key)
			{
				xobject = test_key
				flag = true
				not_in_player = false
			}
			else: not_in_player = true
		}
	}

	if not_xobject = true
	{
			VMessage(&DoUnlock, 1)  ! "Doesn't seem to work..."
			return true
	}
	if not_in_player = true
	{
		VMessage(&DoUnlock, 2)           ! no key that fits
		return true
	}

	object is locked
	if not object.after
	{
		if not xobject.after
		{
			if xobject_flag = true: MultiKeyMessage(&DoLock, 3)	! "Locked."
			else: MultiKeyMessage(&DoLock, 3, xobject)     	! "(with the...) Locked."
		}
	}
	return true
}

replace DoUnLock
{
	local a, z, test_key, flag, not_xobject, not_in_player, xobject_flag

	if not CheckReach(object): return false

	if object is open
	{
		MultiKeyMessage(&DoUnLock, 4)             ! "The door is open."

		if object is not locked
		{
			MultiKeyMessage(&DoUnLock, 7)
			z = 1
		}

		if xobject: if not InList(object, key_object, xobject): MultiKeyMessage(&DoUnLock, 5, z)
		else: if not SearchKey(object): MultiKeyMessage(&DoUnLock, 6, z)

		return true
	}

	if object is not locked
	{
		VMessage(&DoUnLock, 3)             ! already unlocked

		if xobject: if not InList(object, key_object, xobject): MultiKeyMessage(&DoUnLock, 5)
		else: if not SearchKey(object): MultiKeyMessage(&DoUnLock, 6)

		return true
	}

	while object.#key_object > a and flag = false
	{
		a++
		test_key = object.key_object #a

		if xobject
		{
			if xobject = test_key
			{
				flag = true
				not_xobject = false
				xobject_flag = true
			}
			else: not_xobject = true
		}

		if not xobject
		{
			if Contains(player, test_key)
			{
				xobject = test_key
				flag = true
				not_in_player = false
			}
			else: not_in_player = true
		}
	}

	if not_xobject = true
	{
			VMessage(&DoUnlock, 1)  ! "Doesn't seem to do the trick..."
			return true
	}
	if not_in_player = true
	{
		VMessage(&DoUnlock, 2)           ! no key that fits
		return true
	}

	object is not locked
	if not object.after
	{
		if not xobject.after
		{
			if xobject_flag = true: MultiKeyMessage(&DoUnLock, 3)		! "Unlocked."
			else: MultiKeyMessage(&DoUnLock, 3, xobject)     		! "(with the...) Unlocked."
		}
	}
	return true
}


routine SearchKey(door_obj)
{
	local i, test_key

	while door_obj.#key_object > i
	{
		i++
		test_key = door_obj.key_object #i

		if Contains(player, test_key): return true
	}

	return false
}


routine MultiKeyMessage(r, num, a, b)
{
	if NewMultiKeyMessages(r, num, a, b):  return

	select r

	case &Dolock
	{
		select num
		case 3
		{
			if a
			print "(with "; The(a); ")"
			print "Locked."
			return true
		}
		case 5
		{
			"(";
			CThe(xobject)
			" doesn't work anyway.)"
		}

		case 6
		{
			"(You'll have to find the right key anyway.)"
		}
	}

	case &DoUnLock
	{
		select num
		case 3
		{
			if a
			print "(with "; The(a); ")"
			print "Unlocked."
			return true
		}
		case 4
		{
			print CThe(object); IsorAre(object); " open."
			return true
		}
		case 5
		{
			if a = 1
			{
				" and ";
				The(xobject)
			}
			else
			{
				"(";
				CThe(xobject)
			}
			" doesn't work anyway.)"
		}
		case 6
		{
			if a = 1
			{
				" and you'll ";
			}
			else
			{
			"(You'll ";
			}
			"have to find the right key anyway.)"
		}
		case 7
		{
			"(It's already unlocked";
		}

	}
}

routine NewMultiKeyMessages(r, num, a, b)	! For replacement messages
{
	return false				! Be sure to have replaced messages return true.
}
