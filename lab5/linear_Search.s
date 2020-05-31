		area reset,data,readonly
		export __Vectors
__Vectors
		dcd 0x10001000   ; initial value of stack pointer
		dcd Reset_Handler  ;label Reset_Handler is declared somewhere down the code
		area mycode,code,readonly
		align
		entry ;marks first instruction to be executed
		export Reset_Handler
Reset_Handler
		ldr r0,=input
		ldr r1,=position
		mov r2,#10
		mov r4,#76
		mov r6,#1
		mov r7,#0
loop	ldr r5,[r0],#4
		add r7,#1
		cmp r5,r4
		beq label1
		subs r2,#1
		bne loop
		b here
;key		equ #76
label1
		str r6,[r1],#4
		str r7,[r1]
here	b here

input	dcd 1,2,4,76,56,3,4,9,5,7
		area mydata,data,readwrite

position		dcd 0
		end

		
	
