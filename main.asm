	.MODEL MEDIUM
	.STACK 64
	.DATA
	;DIRECTION CONSTANTS
	;0 DEG
	UP EQU 00H
	;180 DEG
	DOWN EQU 04H
	;90 DEG
	LEFT EQU 02H
	; - 90 DEG
	RIGHT EQU 0FEH
	;45 DEG
	UPPER_LEFT EQU 01H
	; - 45 DEG
	UPPER_RIGHT EQU 0FFH
	;135 DEG
	LOWER_LEFT EQU 03H
	; - 135
	LOWER_RIGHT EQU 0FDH
	
	;SCAN CODES
	FIRST_PLAYER_ROT_LEFT_BTN EQU 75 ;leftArowKey
	FIRST_PLAYER_ROT_RIGHT_BTN EQU 77 ;rightArowKey
	FIRST_PLAYER_INCR_THRUST_BTN EQU 72;upArowKey
	FIRST_PLAYER_DECR_THRUST_BTN EQU 80;downArowKey
	FIRST_PLAYER_FIRE EQU 	52H;0Key
	
	
	SECOND_PLAYER_ROT_LEFT_BTN EQU 1EH;aKey
	SECOND_PLAYER_ROT_RIGHT_BTN EQU 20H;dKey
	SECOND_PLAYER_INCR_THRUST_BTN EQU 11H;wKey
	SECOND_PLAYER_DECR_THRUST_BTN EQU 1FH;sKey
	SECOND_PLAYER_FIRE EQU 47h;homekey
	
	first_player_direction DB 00h
	first_player_thrust DB 00h
	first_player_X DW 150
	first_player_Y DW 20
	second_player_direction DB 00h
	second_player_thrust DB 00h
	second_player_X DW 150
	second_player_Y DW 180
	
	FireIArrP1 DB 3 dup(2 dup(1)) ;appear 1 - >no Fire | 2 - >there is fire, dir
	FireXArrP1 DW 3 dup(0)
	FireYArrP1 DW 3 dup(0)
	
	FireIArrP2 DB 3 dup(2 dup(1)) ;appear 1 - >no Fire | 2 - >there is fire, dir
	FireXArrP2 DW 3 dup(0)
	FireYArrP2 DW 3 dup(0)
	; * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	Player1_Score DW 00
	Player2_Score DW 00
	
	Player1_Hearts DW 00
	Player2_Hearts DW 00
	; * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	Game_Over_Mess DB 'Game Over!', 10, 13, 09, 32, 32, ' Press [y] to retart.', 10, 13, 09, 32, 32, 32, 'Press other key to quit.$$'
	Lives_Word DB 'Lives : $'
	
	temp_var DB 0

	invite db 00000000b

	GInvite db 00
	
	Score_Num_char DB 10 dup('$')
	
	MSG DB 'First Player Name:', 10, 13, "$"
	MSG2 DB 'Press Enter Key To Continue...', 10, 13, "$"
	MSG3 DB 'Second Player Name:', 10, 13, "$"
	GameLevel DB 'To Start Space War Game Press F2', '$'
	ChatMsg                       DB  'To Start Chatting Press F3', '$'
	First_Player_Name DB 50, ?, 50 DUP("$")
	Second_Player_Name DB 50, ?, 50 DUP("$")

	ChatInvite db  'You Sents Chat Invite. to ','$'
	ChatRecvd db  ' Sents chat Invite.,F3 to accept','$'


	GameInvite db  'You Sents Game Invite. to ','$'
	GameRecvd db  ' Sents Game Invite.,F2 to accept','$'

	Level1MSG db '- Press 1 to Enter Level 1 ','$'
	Level2Msg db '- Press 2 to Enter Level 2 ','$'

	pressed db 00h
	pressedR db 00h
	is_master db 00h
	Level2 db '?'
	;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	send	db 30 dup('$')
	resive 	db 30 dup('$')
	endresive db 0
	; * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	write_flag db 0
	resive_flag db 0
	Send_buffer_index dw 0
	write_buffer_index dw 0
	;;__________________________________________________________________________________________________________;;
	Write_flag_on_Key_ctrl	equ 9
	Write_flag_off_Key_enter	equ 0Dh
	Max_len_Chat_Mess	equ 18
	;;__________________________________________________________________________________________________________;;

	.CODE
	INCLUDE Play.INC
	INCLUDE Chat.INC
	main proc far
	mov ax, @data
	mov ds, ax
	mov ah, 0                    ;set screen 320width * 200height
	mov al, 13h
	int 10h

	Menu
	ChoosingMenu: ChooseM
	
	hlt
	main endp
	; * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

	sendIngameCharacter proc
		mov ah,1
		int 16h
		jz	exitSendIngameCharacter
		cmp ah,FIRST_PLAYER_ROT_LEFT_BTN
		jz exitSendIngameCharacter
		cmp ah,FIRST_PLAYER_ROT_RIGHT_BTN
		jz exitSendIngameCharacter
		cmp ah,FIRST_PLAYER_INCR_THRUST_BTN
		jz exitSendIngameCharacter
		cmp ah,FIRST_PLAYER_DECR_THRUST_BTN
		jz exitSendIngameCharacter
		cmp ah,	FIRST_PLAYER_FIRE
		jz exitSendIngameCharacter
		cmp al,27
		mov is_master,00
		mov GInvite,00
		jz ChoosingMenu
		mov ah,0
		int 16h

		cmp al,8
		jnz notBackSpaceInGameSend
			dec Send_buffer_index
			mov al,'$'
		notBackSpaceInGameSend:

		mov bl,al
		sendModeIngame:    
			mov dx, 3fdh
			in  al, dx
			and al, 00100000b
			jz  sendModeIngame
			mov dx, 03f8h
			mov al, bl
			out dx, al

		cmp al,Write_flag_off_Key_enter		
		jz enterKeyState

		mov bx,Send_buffer_index
		cmp bx,Max_len_Chat_Mess
		jz fullSendMode

		mov bl,write_flag
		cmp bl,0
		jnz addSendChar

		fullSendMode:
		cmp al,Write_flag_on_Key_ctrl
		jnz	exitSendIngameCharacter
		mov Send_buffer_index,0
		mov si,offset send
		clearSendBuffer:
			mov ch,'$'
			mov [si],ch
			inc si
			cmp si,offset resive
		jnz clearSendBuffer
		mov write_flag,1
		jmp	exitSendIngameCharacter

		addSendChar:
			mov si,offset send
			add si,Send_buffer_index
			mov [si],al
			cmp al,'$'
			jz noIncrementSend
			inc Send_buffer_index
			noIncrementSend:
		jmp exitSendIngameCharacter

		enterKeyState:
			mov write_flag,0
		
	exitSendIngameCharacter:
	ret
	sendIngameCharacter endp

	resiveIngameCharacter proc
		mov         dx, 3FDH     ;Line Status Register
		in          al, dx
		and        	al, 1
		JZ          exitResiveIngameCharacter
		mov         dx, 03F8H
		in          al, dx

		cmp al,'$'
		jnz notBackSpaceInGameResive
			dec write_buffer_index
		notBackSpaceInGameResive:

		cmp al,Write_flag_off_Key_enter		
		jz enterKeyStateInResive

		mov bx,write_buffer_index
		cmp bx,Max_len_Chat_Mess
		jz fullRecieveMode	

		mov bl,resive_flag
		cmp bl,0
		jnz addResiveChar

		fullRecieveMode:
		cmp al,Write_flag_on_Key_ctrl
		jnz	exitResiveIngameCharacter
		mov write_buffer_index,0
		mov si,offset resive
		clearRecieveBuffer:
			mov ch,'$'
			mov [si],ch
			inc si
			cmp si,offset endresive
		jnz clearRecieveBuffer
		mov resive_flag,1
		jmp	exitResiveIngameCharacter

		addResiveChar:
			mov si,offset resive
			add si,write_buffer_index
			mov [si],al
			cmp al,'$'
			jz noIncrementResive
			inc write_buffer_index
			noIncrementResive:
		jmp exitResiveIngameCharacter

		enterKeyStateInResive:
			mov resive_flag,0

	exitResiveIngameCharacter:
	ret
	resiveIngameCharacter endp

end main
