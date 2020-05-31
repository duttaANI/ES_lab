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
;after ith iteration ith max element will be in its place
		mov r0,#3
		mov r1,#5
		mov r2,#1
		mov r3,#2
		mov r4,#4
		
		stm r13!,{r0-r4}
		mov r5,#4
		mov r6,#1
		mov r12,r13
		mov r2,r12
		
ab		cmp r6,r5
		bhi last
		mov r7,r2
		mov r10,r2
		movs r8,#5
		add r9,r6,#1
up		cmp r9,r8
		bhi l2
		sub r10,r10,#4
		ldmdb r7,{r0}
		ldmdb r10,{r1}
		cmp r1,r0
		movcs r7,r10
		add r9,#1
		b up
l2		ldmdb r7!,{r3}
		ldmdb r2!,{r4}
		stm r2,{r3}
		stm r7,{r4}
		add r6,#1
		b ab
last	b last
		area mydata,data,readwrite

result	dcd 0
		end	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
