.comment "Give me my:
#----
oo

 wallets"		;---------
   .name".namePuhlyash"
 	# -----
			# ------
	st r16,89

	zjmp %:deb1
	live %00001

	live %3

	live %6
	live %1

	lldi r7,r5,r1

	live %:op
	live %1
toto:
deb1:
	zjmp %:deb
	live%1 #------
	live %1
	live%1
	live %1
; -----
	live%1

	live %1 ;---------
	live %:toto
	xor r2,r2,r2
	live %1
add r4,r11,r77
	live %1
	live %1
deb:fork %155
	ld %4, r1
	ld :op,r1
	live %1
	aff r3
	st r12,4
op:
vv:
