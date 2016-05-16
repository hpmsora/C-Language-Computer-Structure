	.text
	.syntax unified
	.thumb
	.global	abs	
	.type abs, %function
abs:
	push {r4-r7}
/*
	Your implementation goes here. 
*/

/*	
	int abs_c(int num) {
	  if (num>=0) return num ;
	  else return -num	 ;
	}	
*/
	//if (num >=0 )
	cmp r0, #0
	//Bigger or equal
	bge conseq
	//smaller
	blo alt
	
//return num
conseq:
	b final_state
//return -num
alt:
	//register 0 to r1
	movs r1, #0
	subs r0, r1, r0
	b final_state
	//r0 -> return valriable
final_state:	
	pop {r4-r7}	
	bx	lr
