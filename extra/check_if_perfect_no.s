		area reset ,data,readonly
		export __Vectors
__Vectors
		dcd 0x10001000
		dcd Reset_Handler
		align
		area mycode,CODE,readonly
		entry
		export Reset_Handler
Reset_Handler
		ldr r0,=N
		ldr r1,[r0]  ; for remainder
		mov r2,r1  ; for changing divisors from N-1 till 1
		mov r3,#1  ; to store sum
		b store_divisors
		
div	sub r1,r2
		cmp r1,r2
		bcs div
		b after_div
		
store_divisors
		sub r2,#1
		ldr r1,[r0]  ; for remainder / restore after div
		cmp r2,#1
		bhi div
		b ans
		
		
after_div
		cmp r1,#0
		beq store_div
		b store_divisors
		
store_div
		push  {r2}
		add r3,r2
		b store_divisors
		
ans
		ldr r1,[r0]
		cmp r3,r1
		beq  is_perfect
		b not_perfect
		
is_perfect
		mov r6,#1
		b stop
		
not_perfect
		mov r6,#0
		b stop
		
stop
		b stop
		
N		dcd 28
		area mydata,data,readwrite
		end
		
		
		
		
		
		
		
		
		
		
		
		
		
		
