	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=N1
	LDR R1,=N2
	LDR R9,=DST
	LDR R2,[R0]
	LDR R3,[R1]
	SUB R4,R3,R2
	STR R4,[R9]
HERE
	B HERE
N1 DCD 2
N2 DCD 7
	AREA mydata,DATA,READWRITE
DST DCD 0
	END
