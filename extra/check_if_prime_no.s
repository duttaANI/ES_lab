		area reset,data,readonly
		export __Vectors
__Vectors
		dcd 10001000
		dcd Reset_Handler
		align
		area mycode,CODE,readonly
		entry
		export Reset_Handler
Reset_Handler
		
		ldr r0,=N
		ldr r1,[r0]              
		mov r2,r1             ;  copy r1 to r2
		
		b check_prime
		
div	
		sub r1,r2
		cmp r1,r2
		bcs div
		b after_div
		
check_prime
		sub r2,#1             ;  we will check from 2 till N-1  cmp r2,#1  used as divisor
		ldr r1,[r0]              ; will be used for remainder
		cmp r2,#1
		beq is_prime
		b div

after_div
		cmp r1,#0             ; see if remainder is zero
		beq not_prime
		b check_prime
		
not_prime
		mov r6,#0
		b stop
		
is_prime
		mov r6,#1
		b stop
		
stop
		b stop
		
N		dcd 38
		area mydata,data,readwrite
		end
