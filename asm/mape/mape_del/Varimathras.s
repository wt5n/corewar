.name		"Varimathras"
.comment	"If I have wings, why am I always walking?"

suite:
	ld		%0, r1
	zjmp	%:fin
	and		%0, %0, r16
fin:
