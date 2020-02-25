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
		ldr r1,[r0]
		ldr r3,[r0]
		mov r2,#0x10  ; just stores ten       ////////////////==============> JUST CHANGE IT TO #0xa :decimal ,, #0x10 to check palindrome in hexadecimal
		mov r6,#0      ; to check palindrome 
		mov r4,#0      ; to store reverse 
		mov r7,#1
		mov r5,#1      ; to store no. of ele in stack
		
		cmp r1,r2
		bcc one
		b stacked
		
		
		
		
div	
		mov r3,#0   ; ensure r1 > r2 while calling div r3=quotient & r1=remainder
loop	
		;cmp r1,r2
		;bhi 
		sub r1,r2
		add r3,#1
		cmp r1,r2
		bcs loop
		;ldr r1,r3
		bcc stacked
		
stacked
		push {r1}
		add r5,#1
		;push {r1,lr}   ; push r1=remainder ,lr in stack , for first time r1 = N and valueable lr
		cmp r3,r2
		mov r1,r3
		bcs div
		push {r3}
		b reverse
		
reverse
		
		pop {r1}
		;mul r7,r2
		mul r1,r1,r7
		add r4,r1
		mul r7,r2
		sub r5,#1
		cmp r5,#1
		beq compare
		b reverse
		
compare
		ldr r1,[r0]
		cmp r4,r1
		beq one 
		b stop
	

one
		add r6,#1
		b stop
		
stop
		b stop

N		dcd 0x66
		area mydata,data,readwrite
		end











		
		
