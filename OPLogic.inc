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
	endm


;Send character through serial port
SendChar MACRO MyChar
    LOCAL Send
    Send:
       mov         dx, 3fdh

		in          al, dx
		test        al, 00100000b
		jz          Send 
		mov         dx, 3f8h ;sending value
		mov         al, MyChar
		out         dx, al
ENDM 

;Receive a character from the serial port into AL
ReceiveChar MACRO
    LOCAL Return
    MOV AL, 0
     mov         dx , 3FDH              	; Line Status Register
	in          al , dx
	test        al , 1
	JZ          RETURN
	mov         dx , 03F8H
	in          al , dx
	RETURN:

ENDM 

ProcessInput MACRO Char, Player
    LOCAL CheckChat, StartChatting, GameChk, StartGame,ee,chatRecv,GameRecv,fin
    ;Check if Chat (F3) is pressed
    CheckChat:
    CMP Char, 3dH
    JNE GameChk
    

    MOV AL, invite
    OR  AL, Player
    CMP AL, 3               ;Only equals 3 when the other player accept the invitation
    JE StartChatting
    
    ;Send invitation
    MOV invite, Player

	;Display Messages In Notification Bar

	cmp invite,1
	jne chatRecv
	mov dx,1300h
	mov ah,2
	int 10h
	ShowMSG ChatInvite
	mov dl,26
	mov dh,13h
	mov ah,2
	int 10h
	ShowMSG Second_Player_Name+2
	jmp ee

	chatRecv:
	cmp invite,2
	jne ee
	mov dx,1400h
	mov ah,2
	int 10h
	ShowMSG First_Player_Name+2
	mov dl,First_Player_Name+1
	mov dh,14h
	mov ah,2
	int 10h
	ShowMSG ChatRecvd
	RET
    
    ;Accept invitation
    StartChatting:
    MOV invite, 0
    CALL chat
	ee:
    RET

	;Check if (F2) is pressed
	GameChk:
	CMP Char,3ch
	jne ee


	MOV AL, GInvite
    OR  AL, Player
    CMP AL, 3               ;Only equals 3 when the other player accept the invitation
    JE StartGame
    
    ;Send invitation
    MOV GInvite, Player

	;Display Messages In Notification Bar
	cmp GInvite,1
	jne GameRecv
	mov dx,1500h
	mov ah,2
	int 10h
	ShowMSG GameInvite
	mov dl,26
	mov dh,15h
	mov ah,2
	int 10h
	ShowMSG Second_Player_Name+2
	jmp ee

	GameRecv:
	cmp GInvite,2
	jne ee
	mov dx,1600h
	mov ah,2
	int 10h
	ShowMSG First_Player_Name+2
	mov dl,First_Player_Name+1
	mov dh,16h
	mov ah,2
	int 10h
	ShowMSG GameRecvd
	    RET
    
    ;Accept invitation
    StartGame:
    MOV GInvite, 0
	mov is_master,1
	CALL PLAY

fin:
	endm


ChooseM macro

	;Clear Screen
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
	mov dx, 0705h
	int 10h
	ShowMSG ChatMsg
	
	mov ah, 2
	mov dx, 1200h
	int 10h
	

	;Draw Notification Region
	mov ah, 9
	mov bh, 0
	mov al, '_'
	mov cx, 28h
	mov bl, 0Fh
	int 10h

;============================================
	;Port Initialization
	
	          mov         dx, 3fbh
	          mov         al, 10000000b
	          out         dx, al
	
	          mov         dx, 3f8h
	          mov         al, 0ch
	          out         dx, al
	
	
	          mov         dx, 3f9h
	          mov         al, 00h
	          out         dx, al
	
	          mov         dx, 3fbh
	          mov         al, 00011011b
	          out         dx, al
	
	;End of port Initialization

	;Display Previous Invitation if any
	cmp invite,1
	jne chatRecvS
	mov dx,1300h
	mov ah,2
	int 10h
	ShowMSG ChatInvite
	mov dl,26
	mov dh,13h
	mov ah,2
	int 10h
	ShowMSG Second_Player_Name+2
	JMP GM

	chatRecvS:
	cmp invite,2
	jne GM
	mov dx,1400h
	mov ah,2
	int 10h
	ShowMSG First_Player_Name+2
	mov dl,First_Player_Name+1
	mov dh,14h
	mov ah,2
	int 10h
	ShowMSG ChatRecvd

	GM:
	cmp GInvite,1
	jne GameRecvS
	mov dx,1500h
	mov ah,2
	int 10h
	ShowMSG GameInvite
	mov dl,26
	mov dh,15h
	mov ah,2
	int 10h
	ShowMSG Second_Player_Name+2
	jmp SENDER

	GameRecvS:
	cmp GInvite,2
	jne SENDER
	mov dx,1600h
	mov ah,2
	int 10h
	ShowMSG First_Player_Name+2
	mov dl,First_Player_Name+1
	mov dh,16h
	mov ah,2
	int 10h
	ShowMSG GameRecvd
	

SENDER:

	mov ah, 1                    ;check if there's an input
	int 16h
	jz Receiver           ;if No input, jmp to check if there's a char input in receive mode
		
	mov ah, 0                    ;read char from buffer
	int 16h
	mov Pressed, ah              ;mov char scancode to Pressed
	SendChar Pressed
	CALL ProcessPrimaryInput ;send pressed and player 1 to proces Input

Receiver:
	ReceiveChar
	JZ SENDER
	MOV PressedR,AL
	CALL ProcessSecondaryInput ;send pressed and player 2 to proces Input
	JMP SENDER
endm


ProcessPrimaryInput PROC
    ProcessInput Pressed, 1
    RET
ProcessPrimaryInput ENDP
;===============================================================

;Process secondary user input
ProcessSecondaryInput PROC
    ProcessInput PressedR, 2
    RET
ProcessSecondaryInput ENDP


