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
	FIRST_PLAYER_FIRE EQU 25h;kKey
	
	
	SECOND_PLAYER_ROT_LEFT_BTN EQU 1EH;aKey
	SECOND_PLAYER_ROT_RIGHT_BTN EQU 20H;dKey
	SECOND_PLAYER_INCR_THRUST_BTN EQU 11H;wKey
	SECOND_PLAYER_DECR_THRUST_BTN EQU 1FH;sKey
	SECOND_PLAYER_FIRE EQU 39H   ;spaceKey
	
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
	First_Player_Name DB 15, ?, 50 DUP("$")
	Second_Player_Name DB 15, ?, 50 DUP("$")

	ChatInvite db  'You Sents Chat Invite. to ','$'
	ChatRecvd db  ' Sents chat Invite.,F3 to accept','$'


	GameInvite db  'You Sents Game Invite. to ','$'
	GameRecvd db  ' Sents Game Invite.,F2 to accept','$'

	pressed db 00h
	pressedR db 00h
	;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	send	db 30 dup('$')
	resive 	db 30 dup('$')
	; * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	
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
	call Play
	ChoosingMenu: ChooseM
	
	hlt
	main endp
	; * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	
end main
