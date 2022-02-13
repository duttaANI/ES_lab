	area reset,data,readonly
	export __Vectors
__Vectors
	dcd 0x10001000
	dcd Reset_Handler
	area mycode,CODE,readonly
	align
	export Reset_Handler
	entry
Reset_Handler
	ldr r0,=src
	
	mov r2,#4  ; ele to search
	mov r3,#7    ; length of arr
	ldr r4,=dst
	mov r5,#0     ; to store position
	bl lin_search
	
lin_search
	push {r1,lr}
	ldr r1,[r0],#4
	sub r3,#1
	add r5,#1
	cmp r3,#0
	;bhi lin_search
	b search_in_stack

	
search_in_stack
	mov r3,#7   ; length of arr
	cmp r1,r2
	pop{r1,lr}
	beq store
	bx lr
	
store
	str r5,[r4]
	b stop
	
stop

	b stop
	

src	dcd	1,2,3,4,5,6,7
	area mydata,data,readwrite
dst	dcd 0
	end
	