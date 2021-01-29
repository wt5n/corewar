.name "z"
.comment "j"
		

fork_live:	live	%42
		fork	%:live100
		live	%42	
		fork	%:fork_live
		live	%42
		zjmp	%:fork_live
live100:	live	%42
