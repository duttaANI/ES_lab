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
		;convert 32 bit packed to equilvalent hexadecimal
		ldr r0,=n
		ldr r1,=dst
		ldr r2,[r0]
		mov r7,#0xf
		mov r4,#0xa
		mov r5,#0
		mov r3,#1
up		mov r6,r2
		and r6,r7
		mla r5,r6,r3,r5 ; mla => multiply and add
		mul r3,r4
		lsr r2,#4 ; lsr => left shift register
		cmp r2,#0
		bne up
		
        str		r5,[r1]	
		
stop	b stop
n		dcd 0x1234a67f ; or keep 0x99999999
		area mydata,data,readwrite

dst		dcd 0
		end
