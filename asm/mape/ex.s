.name "z"
.comment "j"
		
l2:	ld	%276, r1
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
