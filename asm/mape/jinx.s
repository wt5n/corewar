.name "Jinx"
.comment "Stay still, I'm trying to shoot you..!"

init:
	st		r1, :replic1
	st		r6, -4
	ld		:replic1, r1

stuff1:
	live	%66
	ldi		%-5, r3, r1
	sti		r1, %-173, r3
	add		r3, r4, r3
	xor		r5, r3, r6
	zjmp	%:stuff2

stuff2:
	xor		r3, r3, r3
	zjmp	%-207

replic1:
	st		r1, r1
