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
		ldr r0,=list
		ldr r2,=result
		mov r3,#5
up		ldr r1,[r0],#4
		str r1,[r2],#4
		subs r3,r3,#1
		bne up
		ldr r2,=result
		ldr r4,[r2]
		mov r5,#1
		mov r6,#4
above	cmp r5,r6
		bhi last
		mov r7,r2
		mov r8,#5
		add r9,r5,#1
		mov r3,r7
l3		cmp r9,r8
		bhi l2
		ldr r10,[r7]
		add r3,r3,#4
		ldr r11,[r3]
		cmp r10,r11
		movcs r7,r3
		add r9,#1
		b l3
l2		ldr r0,[r7]
		ldr r1,[r2]
		str r0,[r2]
		str r1,[r7]
		add r2,#4
		add r5,#1
		b above
		
last	b last
list	dcd 1,6,2,9,3	
		area mydata,data,readwrite

result	dcd 0
		end	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
