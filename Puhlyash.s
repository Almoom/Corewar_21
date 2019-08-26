.comment "Give me my:
#----
oo

 wallets";---------
   .name ".namePuhlyash"
 	# -----
			# ------
	xor r0,r0,r0
	zjmp %:deb1
	live %0000001

	live %1

	live %1
	live %1
	live %1
	live %1
	toto:
deb1:

zjmp %:deb
	live %1 #------
	live %1
	live %1
	live %1
; -----
	live %1

	live %1 ;---------
	live %1

	live %1

	live %1
	live %1
deb:

fork %12
	ld %0x70000004,r0
.code 03 FF FF
	ld %0x08030003,r0
	live %1
	st r0,4
#----------
