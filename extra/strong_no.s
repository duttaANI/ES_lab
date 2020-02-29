		area reset,data,readonly
		export __Vectors
__Vectors
		dcd 0x10001000
		dcd Reset_Handler
		area mycode,CODE,readonly
		align
		entry
		export Reset_Handler
Reset_Handler
		ldr r0,=N
		ldr r1,[r0]
		mov r2,r1 ; to get digit
		mov r3,#0 ; to store quotient // not needed
		mov r4,#10
		mov r5,#0  ; to store fact sum
		mov r6,#1 ; to store factorial
		b strong_no
		
strong_no
		mov r3,#0
		cmp r2,R4
		bcs div
		mov r7,r2
		mov r6,#1
		b fact
up
		add r5,r6
		mov r2,r3
		cmp r3,#0
		bhi strong_no
		cmp r1,r5
		beq is_strong
		b not_strong
		
div	
		sub r2,r4
		add r3,#1
		cmp r2,r4
		bcs div
		mov r7,r2
		mov r6,#1
		b fact
		
fact
		
		mul r6,r6,r7
		sub r7,#1
		cmp r7,#2
		bcs fact
		push {r6}
		b up
		
is_strong
		mov r8,#1
		b stop
		
not_strong
		mov r8,#0
		b stop
		
stop
		b stop
		
N		dcd 145
		area mydata,data,readwrite
		end
		
