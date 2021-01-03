	ROTATE_PLAYER1_ANTICLOCK MACRO
	LOCAL DONT_ADD_ONE, ENDD
	
	CMP first_player_direction, DOWN
	JZ DONT_ADD_ONE
	INC first_player_direction
	JMP ENDD
	
DONT_ADD_ONE:
	MOV first_player_direction, LOWER_RIGHT
ENDD:
	ENDM
	
	ROTATE_PLAYER1_CLOCK MACRO
	LOCAL DONT_SUBTRACT_ONE, ENDD
	
	CMP first_player_direction, LOWER_RIGHT
	JZ DONT_SUBTRACT_ONE
	DEC first_player_direction
	JMP ENDD
	
DONT_SUBTRACT_ONE:
	MOV first_player_direction, DOWN
ENDD:
	ENDM
	
	INCR_PLAYER1_THRUST MACRO
	LOCAL UPPER_REACHED
	
	CMP first_player_thrust, 3
	JZ UPPER_REACHED
	INC first_player_thrust
UPPER_REACHED:
	ENDM
	
	DECR_PLAYER1_THRUST MACRO
	LOCAL LOWER_REACHED
	
	CMP first_player_thrust, 0
	JZ LOWER_REACHED
	DEC first_player_thrust
LOWER_REACHED:
	ENDM
	
	ROTATE_PLAYER2_ANTICLOCK MACRO
	LOCAL DONT_ADD_ONE, ENDD
	
	CMP second_player_direction, DOWN
	JZ DONT_ADD_ONE
	INC second_player_direction
	JMP ENDD
	
DONT_ADD_ONE:
	MOV second_player_direction, LOWER_RIGHT
ENDD:
	ENDM
	
	ROTATE_PLAYER2_CLOCK MACRO
	LOCAL DONT_SUBTRACT_ONE, ENDD
	
	CMP second_player_direction, LOWER_RIGHT
	JZ DONT_SUBTRACT_ONE
	DEC second_player_direction
	JMP ENDD
	
DONT_SUBTRACT_ONE:
	MOV second_player_direction, DOWN
ENDD:
	ENDM
	
	INCR_PLAYER2_THRUST MACRO
	LOCAL UPPER_REACHED
	
	CMP second_player_thrust, 3
	JZ UPPER_REACHED
	INC second_player_thrust
UPPER_REACHED:
	ENDM
	
	DECR_PLAYER2_THRUST MACRO
	LOCAL LOWER_REACHED
	
	CMP second_player_thrust, 0
	JZ LOWER_REACHED
	DEC second_player_thrust
LOWER_REACHED:
	ENDM
	
	DETERMINE_THRUST_COMPONENTS MACRO
	LOCAL FIRST_PLAYER_THRUST__, SECOND_PLAYER_THRUST__
	
FIRST_PLAYER_THRUST__:
	CMP first_player_direction, RIGHT
	JZ R_P1
	CMP first_player_direction, UPPER_RIGHT
	JZ UR_P1
	CMP first_player_direction, LOWER_RIGHT
	JZ LR_P1
	CMP first_player_direction, LEFT
	JZ L_P1
	CMP first_player_direction, UPPER_LEFT
	JZ UL_P1
	CMP first_player_direction, LOWER_LEFT
	JZ LL_P1
	CMP first_player_direction, UP
	JZ U_P1
	CMP first_player_direction, DOWN
	JZ D_P1
	
SECOND_PLAYER_THRUST__:
	CMP second_player_direction, RIGHT
	JZ R_P2
	CMP second_player_direction, UPPER_RIGHT
	JZ UR_P2
	CMP second_player_direction, LOWER_RIGHT
	JZ LR_P2
	CMP second_player_direction, LEFT
	JZ L_P2
	CMP second_player_direction, UPPER_LEFT
	JZ UL_P2
	CMP second_player_direction, LOWER_LEFT
	JZ LL_P2
	CMP second_player_direction, UP
	JZ U_P2
	CMP second_player_direction, DOWN
	JZ D_P2
	
R_P1:
	MOV AL, first_player_thrust
	MOV AH, 0
	JMP SECOND_PLAYER_THRUST__
UR_P1:
	MOV AL, first_player_thrust
	MOV AH, first_player_thrust
	NEG AH
	JMP SECOND_PLAYER_THRUST__
LR_P1:
	MOV AL, first_player_thrust
	MOV AH, first_player_thrust
	JMP SECOND_PLAYER_THRUST__
L_P1:
	MOV AL, first_player_thrust
	NEG AL
	MOV AH, 0
	JMP SECOND_PLAYER_THRUST__
UL_P1:
	MOV AL, first_player_thrust
	MOV AH, first_player_thrust
	NEG AL
	NEG AH
	JMP SECOND_PLAYER_THRUST__
LL_P1:
	MOV AL, first_player_thrust
	NEG AL
	MOV AH, first_player_thrust
	JMP SECOND_PLAYER_THRUST__
U_P1:
	MOV AL, 0
	MOV AH, first_player_thrust
	NEG AH
	JMP SECOND_PLAYER_THRUST__
D_P1:
	MOV AL, 0
	MOV AH, first_player_thrust
	JMP SECOND_PLAYER_THRUST__
	
	
R_P2:
	MOV BL, second_player_thrust
	MOV BH, 0
	JMP ENDD
UR_P2:
	MOV BL, second_player_thrust
	MOV BH, second_player_thrust
	NEG BH
	JMP ENDD
LR_P2:
	MOV BL, second_player_thrust
	MOV BH, second_player_thrust
	JMP ENDD
L_P2:
	MOV BL, second_player_thrust
	NEG BL
	MOV BH, 0
	JMP ENDD
UL_P2:
	MOV BL, second_player_thrust
	MOV BH, second_player_thrust
	NEG BL
	NEG BH
	JMP ENDD
LL_P2:
	MOV BL, second_player_thrust
	NEG BL
	MOV BH, second_player_thrust
	JMP ENDD
U_P2:
	MOV BL, 0
	MOV BH, second_player_thrust
	NEG BH
	JMP ENDD
D_P2:
	MOV BL, 0
	MOV BH, second_player_thrust
ENDD:
	ENDM
	
	ShowMSG MACRO MSG
	MOV AH, 9
	MOV DX, OFFSET MSG
	INT 21H
	ENDM ShowMSG
	
	GetInput MACRO INPUT
	MOV AH, 0AH
	MOV DX, OFFSET INPUT
	INT 21H
	ENDM GetInput
	
	
	Menu macro
	
	
	
P1_NAME:
	mov ax, 0600h
	mov bh, 00
	mov cx, 0
	mov dx, 184FH
	int 10h
	
	
	
	mov ah, 2
	mov dx, 0A80H
	int 10h
	ShowMSG msg
	
	
	
	mov ah, 2
	mov dx, 1080H
	int 10h
	ShowMSG MSG2
	mov ah, 2
	mov dx, 0c80H
	int 10h
	GetInput First_Player_Name
	

	cmp First_Player_Name [2],65
	jl P1_NAME

	cmp First_Player_Name [2],90
	jle p2_name

	cmp First_Player_Name[2],97
	jl P1_NAME

	cmp First_Player_Name[2],122
	jg P1_NAME


	
	p2_name:
	mov ax, 0600h
	mov bh, 00
	mov cx, 0
	mov dx, 184FH
	int 10h
	
	
	
	mov ah, 2
	mov dx, 0A80H
	int 10h
	ShowMSG msg3
	
	
	
	mov ah, 2
	mov dx, 1080H
	int 10h
	ShowMSG MSG2
	mov ah, 2
	mov dx, 0c80H
	int 10h
	GetInput Second_Player_Name

	cmp Second_Player_Name [2],65
	jl P2_NAME

	cmp Second_Player_Name [2],90
	jle ex

	cmp Second_Player_Name[2],97
	jl ex

	cmp Second_Player_Name[2],122
	jg P2_NAME


	ex:
	endm
	
	Choose macro
	
	mov ax, 0600h
	mov bh, 00
	mov cx, 0
	mov dx, 184FH
	int 10h
	
	mov ah, 2
	mov dx, 0505h
	int 10h
	ShowMSG GameLevel
	
	mov ah, 2
	mov dx, 1200h
	int 10h
	
	mov ah, 9
	mov bh, 0
	mov al, '_'
	mov cx, 28h
	mov bl, 0Fh
	int 10h
	
	
INP: mov ah, 1
	int 16H
	jz INP
	
	mov ah, 0
	int 16H
	
	cmp ah, 3cH
	jne INP
	je Restart
	
	
	
	endm
