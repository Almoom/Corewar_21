.comment "Give me my:
#----
oo

 wallets"		;---------
   .name".namePuhlyash"
 	# -----
			# ------
	xor r0,r0,r0
	zjmp %:deb1
	live %00001

	live %1

	live %1
	live %1
	live %:op
	live %1
	toto:live%1111
deb1:
zjmp %:deb
	live%1 #------
	live %1
	live%1
	live %1
; -----
	live%1

	live %1 ;---------
	live %1

	live %1

	live %1
	live %1
deb:fork %12
	ld %4, r0
	ld :op,r0
	live %1
	aff r3
	st r0,4
op:
