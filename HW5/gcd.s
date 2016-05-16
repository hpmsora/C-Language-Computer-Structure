	.text
	.syntax unified
	.thumb
	.global	gcd	
	.type gcd, %function
gcd:
	push {r4-r7}
/*
	Your implementation goes here. 
*/

/*
	int gcd_c(int a, int b) {
	  int d = 0		;

	  while (!(a & 1) && !(b & 1)) {
	    a >>= 1		;
	    b >>= 1		;
	    d += 1		;
	  }
	  while (a != b) {
	    if (!(a & 1)) a >>= 1 ;
	    else if (!(b & 1)) b >>= 1 ;
	    else if (a > b) a = ((a-b) >> 1) ;
	    else b = ((b-a) >> 1)	     ;
	  }
	  return a << d		;
	}
*/

	//int d = 0;
	movs r7, #0

//(a & 1)
while_1_cond_1:
	movs r5, #1
	//(a & 1)
	ands r5, r0, r5
	//delare 0
	movs r3, #0
	//!
	cmp r5, r3
	beq while_1_cond_2
//	bne final_state
	bne while_2_cond

while_1_cond_2:
	movs r5, #1
	//(b & 1)
	ands r5, r1, r5
	//declare 0
	movs r3, #0
	//!
	cmp r5, r3
	beq while_1_loop
//	bne final_state
	bne while_2_cond

while_1_loop:
	//declare 1
	movs r5, #1
	//a >>= 1;
	asrs r0, r0, r5
	//b >>= 1;
	asrs r1, r1, r5
	//d += 1
	adds r7, r7, r5
	b while_1_cond_1
	
while_2_cond:	
	//(a != b)
	cmp r0, r1
	beq final_state
	bne while_2_loop

while_2_loop:
	b while_2_loop_if_cond_1

while_2_loop_if_cond_1:
	//declare 1
	movs r5, #1
	//(a & 1)
	ands r5, r0, r5
	movs r3, #0
	cmp r3, r5
	beq while_2_loop_if_cond_1_true
	bne while_2_loop_if_cond_2

while_2_loop_if_cond_1_true:	
	movs r5, #1
	asrs r0, r0, r5
	b while_2_cond
	
while_2_loop_if_cond_2:	
	movs r5, #1
	ands r5, r1, r5
	movs r3, #0
	cmp r5, r3
	beq while_2_loop_if_cond_2_true
	bne while_2_loop_if_cond_3

while_2_loop_if_cond_2_true:	
	movs r5, #1
	asrs r1, r1, r5
	b while_2_cond

while_2_loop_if_cond_3:
	cmp r0, r1
	bge while_2_loop_if_cond_3_true
	bls while_2_loop_if_cond_4_final

while_2_loop_if_cond_3_true:
	movs r5, #1
	subs r0, r0, r1
	asrs r0, r0, r5
	b while_2_cond

while_2_loop_if_cond_4_final:	
	movs r5, #1
	subs r1, r1, r0
	asrs r1, r1, r5
	b while_2_cond
	
final_state:
	lsls r0, r0, r7
	
	pop {r4-r7}
	bx	lr
