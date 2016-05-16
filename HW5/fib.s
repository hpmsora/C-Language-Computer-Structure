	.text
	.syntax unified
	.thumb
	.global	fib	
	.type fib, %function
fib:
	push {r4-r7}
/*
	Your implementation goes here. 
*/
//	mov r4, r0

	//prev2
	movs r5, #1
	//prev1
	movs r4, #1
	//val
	movs r6, #1
	//0
	movs r2, #0
	//1
	movs r3, #1
	//i
	movs r7, #0
	b fib_cond_1
	
fib_cond_1:	
	cmp r0, r2
	beq fib_first_true
	bne fib_cond_2
	
fib_first_true:
	movs r6, #0
	b final_state

fib_cond_2:
	cmp r0, r3
	beq fib_second_true
	bne fib_loop

fib_second_true:
	movs r6, #1
	b final_state
	
fib_loop:
	b fib_loop_cond

fib_loop_cond:
	movs r1, #0
	subs r1, r0, #2
	cmp r7, r1
	blo fib_loop_cal
	bhs final_state

fib_loop_cal:
	adds r6, r4, r5
	movs r5, r4
	movs r4, r6
	adds r7, r7, #1
//	movs r0, r1
//	b final_state
	b fib_loop_cond

final_state:
	movs r0, r6
	pop {r4-r7}
	bx	lr
