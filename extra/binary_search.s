		area reset, data, readonly
		export __Vectors
__Vectors
		dcd 0x10001000
		dcd Reset_Handler
        align
		area mycode,CODE,readonly
		entry
		export Reset_Handler
Reset_Handler

		ldr r0,=src
		ldr r1,[r0]
		mov r2,#0     ; low
		mov r3,#9   ; high
		add r4,r3,r2  ; value = r3+r2
		mov r5,#4   ; for mid
		mov r6,#10  ; ele to search
		ldr r7,=pos   ; for ans
		mov r8,#0  ; stores address to be checked
		mov r9,#0  ; for changing address
		mov r10,#0 
		mov r11,#4
		b bin_search
		
bin_search
		push {r5}
		cmp r2,r3
		bhi stop
		mul r9,r5,r11
		add r8,r0,r9
		ldr r10,[r8]
		cmp r6,r10
		beq ans
		bhi update_low_mid
		b update_high_mid
		
update_high_mid
		mov r3,r5
		sub r3,#1
		add r4,r3,r2
		mov r5,#0
		mov r8,#0  ; stores address to be checked
		mov r9,#0  ; for changing address
		mov r10,#0 
		b div
		
update_low_mid
		mov r2,r5
		add r2,#1
		add r4,r3,r2
		mov r5,#0
		mov r8,#0  ; stores address to be checked
		mov r9,#0  ; for changing address
		mov r10,#0 
		b div
		
div	sub r4,#2
		add r5,#1
		cmp r4,#2
		bcs div
		b bin_search
		
ans	str r5,[r7]
		b stop
		
stop
		b stop

src	dcd  1,2,3,4,5,6,7,8,9,10
N		dcd 10
		area mydata,data,readwrite
pos	dcd 0
		end
		
		
