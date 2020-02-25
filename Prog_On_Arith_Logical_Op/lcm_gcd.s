		area reset,data,readonly
		export __Vectors
__Vectors
		dcd 0x10001000
		dcd Reset_Handler
		area mycode,code,readonly
		align
		entry
		export Reset_Handler
Reset_Handler
		ldr r0,=val1
		ldr r1,=val2
		ldr r6,=lcm
		ldr r2,[r0]
		ldr r3,[r1]
		mov r7,r2
		mov r8,r3
back	cmp r2,r3 ; if r2=r3=>Z=1 , if r2>r3 Z=0 and C=1
		beq exit ; if r2 and r3 are equal => Z=1
		bcs down ; if C=1 =>( after above steps that)  r2>r3
		sub r3,r2
		b back
down	sub r2,r3
		b back
exit	ldr r0,=gcd
		strb r2,[r0]
		mov r5,#1
		mul r7,r8
		ldr r4,[r0]; load gcd to r4
up		sub r7,r4
		add r5,#1
		cmp r7,r4
		bhi up
		str r5,[r6]
here
		b here
		

val2 	dcd 6
val1	dcd 2
		area mydata,data,readwrite
lcm		dcd 0
gcd		dcd 0
		end
