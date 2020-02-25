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
		ldr r0,=src
		ldr r1,=dst
		ldr r2,[r0]
		mov r3,0xf
		mov r5,#8
up
		and r4,r2,r3
		lsr r2,#4
		add r4,#0x30
		strb r4,[r1],#1
		subs r5,#1
		bne up
stop
		b stop
src		dcd 0x24159237
		area mydata,data,readwrite

dst		dcd 0
		end
