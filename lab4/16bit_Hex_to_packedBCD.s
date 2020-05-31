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
		;convert 16 hex to packed bcd
		ldr r6,=result
		mov r2,#0
		ldr r0,=n
		ldr r1,[r0]
		
	
up		cmp r1,#0xa
		bcc store
		sub r1,#0xa
		add r2,#01
		b up

store	strb r1,[r6],#1
		mov r1,r2
		mov r2,#0
		cmp r1,#0xa
		bcs up
		strb r1,[r6]
		mov r3,r6
		ldr r2,=packed
		ldr r6,=result; r6 holds initial pointer
		sub r4,r3,r6  ; r3 points to last loc r4 has total bytes
		
up1		ldrb r0,[r6],#1
		ldrb r1,[r6],#1
		lsl r1,#4
		orr r1,r0
		strb r1,[r2],#1
		sub r4,#1
		cmp r4,#2
		bcs up
		
stop	b stop
n		dcd 0xfedc ; 16 bit hex
		area mydata,data,readwrite
result		dcd 0,0,0,0,0,0,0,0,0,0
packed		dcd 0
		end
