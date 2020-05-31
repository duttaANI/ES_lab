AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
    LDR R6,=RESULT
	MOV R2,#00
	LDR R0,=VAL1
	LDR R1,[R0]
UP 
    CMP R1,#0x0A    ; if R1<A then C=0
	BCC STORE       ; bcc implies C=0
	SUB R1,#0x0A    
	ADD R2,#0x01
	B UP
STORE 
    ADD R1,#0x30    ; 0x30 is 48 in hexadecimal
	STRB R1,[R6],#1
	MOV R1,R2
	MOV R2,#0
	CMP R1,#0x0A
	BCS UP
	ADD R1,#0x30
	STRB R1,[R6]
STOP
    B STOP

VAL1	dcd 0x00000037
		area mydata,data,readwrite
RESULT		dcd 0

	
 END
