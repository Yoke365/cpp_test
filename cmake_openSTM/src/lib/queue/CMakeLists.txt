
px4_add_module(
	MODULE lib__queue
	SRCS
		dq_addafter.c 
		dq_addfirst.c   
		dq_rem.c 
		dq_remlast.c 
		sq_addafter.c 
		sq_addlast.c  
		sq_rem.c   
		sq_remlast.c 
		dq_addbefore.c 
		dq_addlast.c 
		dq_remfirst.c 
		sq_addfirst.c 
		sq_remafter.c 
		sq_remfirst.c
	)
