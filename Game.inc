INCLUDE models.inc
INCLUDE OPLogic.inc
INCLUDE Score.inc

    
    TAKE_INPUT PROC NEAR         ;take the inputs from users
	
IS_KEY_PRESSED:
	
	

	MOV AH, 1
	INT 16H
	JZ TERMINATE                 ;No key presses to handle, return
	cmp ah,FIRST_PLAYER_ROT_LEFT_BTN
	jz NoTerminateGotKey
	cmp ah,FIRST_PLAYER_ROT_RIGHT_BTN
	jz NoTerminateGotKey
	cmp ah,FIRST_PLAYER_INCR_THRUST_BTN
	jz NoTerminateGotKey
	cmp ah,FIRST_PLAYER_DECR_THRUST_BTN
	jz NoTerminateGotKey
	cmp ah,	FIRST_PLAYER_FIRE
	jz NoTerminateGotKey
	JMP TERMINATE
	NoTerminateGotKey:
	;Else, take a look at the pressed key
	MOV AH, 0
	INT 16H
	;And compare pressed key against known keys
	;P1

KEY1:
	CMP AH, FIRST_PLAYER_ROT_LEFT_BTN
	JNZ KEY2
	ROTATE_PLAYER1_ANTICLOCK
	JMP IS_KEY_PRESSED
	
KEY2:
	CMP AH, FIRST_PLAYER_ROT_RIGHT_BTN
	JNZ KEY3
	ROTATE_PLAYER1_CLOCK
	JMP IS_KEY_PRESSED
	
KEY3:
	CMP AH, FIRST_PLAYER_INCR_THRUST_BTN
	JNZ KEY4
	INCR_PLAYER1_THRUST
	JMP IS_KEY_PRESSED
	
KEY4:
	CMP AH, FIRST_PLAYER_DECR_THRUST_BTN
	JNZ KEY9
	DECR_PLAYER1_THRUST
	JMP IS_KEY_PRESSED
	
KEY9:
	CMP AH, FIRST_PLAYER_FIRE
	JNZ key5
	mov si, 0
	mov bx, offset FireIArrP1
LoopCheckFireArrP1:
	cmp bx, offset FireXArrP1
	JZ IS_KEY_PRESSED
	mov al, [bx]
	CMP al, 1
	JZ foundEmptyFireP1
	add bx, 2
	add si, 2
	JMP LoopCheckFireArrP1
foundEmptyFireP1:
	mov [bx], 2
	mov ah, first_player_direction
	MOV [bx + 1], ah
	mov bx, offset FireXArrP1
	mov ax, first_player_X
	MOV [bx + si], ax
	mov bx, offset FireYArrP1
	mov ax, first_player_Y
	MOV [bx + si], ax
	JMP IS_KEY_PRESSED

	
	
	;P2
KEY5:
	CMP AH, SECOND_PLAYER_ROT_LEFT_BTN
	JNZ KEY6
	ROTATE_PLAYER2_ANTICLOCK
	JMP IS_KEY_PRESSED
	
KEY6: CMP AH, SECOND_PLAYER_ROT_RIGHT_BTN
	JNZ KEY7
	ROTATE_PLAYER2_CLOCK
	JMP IS_KEY_PRESSED
	
KEY7: CMP AH, SECOND_PLAYER_INCR_THRUST_BTN
	JNZ KEY8
	INCR_PLAYER2_THRUST
	JMP IS_KEY_PRESSED
	
KEY8: CMP AH, SECOND_PLAYER_DECR_THRUST_BTN
	JNZ KEY10
	DECR_PLAYER2_THRUST
	JMP IS_KEY_PRESSED
	
KEY10:
	CMP AH, SECOND_PLAYER_FIRE
	JNZ IS_KEY_PRESSED
	mov si, 0
	mov bx, offset FireIArrP2
LoopCheckFireArrP2:
	cmp bx, offset FireXArrP2
	JZ IS_KEY_PRESSED
	mov al, [bx]
	CMP al, 1
	JZ foundEmptyFireP2
	add bx, 2
	add si, 2
	JMP LoopCheckFireArrP2
foundEmptyFireP2:
	mov [bx], 2
	mov ah, second_player_direction
	MOV [bx + 1], ah
	mov bx, offset FireXArrP2
	mov ax, second_player_X
	MOV [bx + si], ax
	mov bx, offset FireYArrP2
	mov ax, second_player_Y
	MOV [bx + si], ax
	JMP IS_KEY_PRESSED
	
	
TERMINATE: RET
	TAKE_INPUT ENDP
	
	UPDATE_PLAYERS PROC NEAR     ;updated the thrust and the attitude values to update X, Y positions for the two players
	DETERMINE_THRUST_COMPONENTS
	;P1
	;AL : first player X thrust component
	;AH : first player Y thrust component

	cmp Level2,02
	jne BiCollision
   
	;Checking Collision P1 with wall
	;=============================================================================================================
 	cmp first_player_direction,0
	je Angle0

	cmp first_player_direction,1
	je Angle45

	cmp first_player_direction,2
	je Angle90

	cmp first_player_direction,3
	je Angle135

	cmp first_player_direction,4
	je Angle180

	cmp first_player_direction,0FDH
	je Angle225

	cmp first_player_direction,0FEH
	je Angle270

	cmp first_player_direction,0FFH
	je Angle315
	jne BICollision


	Angle0:
	cmp first_player_y,75
	jl BICollision
	cmp first_player_Y,110
	jg BICollision

	cmp first_player_X,65
	jl BICollision
	cmp first_player_X,235
	jg BICollision
	
	Angle0Y:
	jmp BEGIN_P2X

	Angle45:
	cmp first_player_y,75
	jl BICollision
	cmp first_player_Y,110
	jg BICollision
	cmp first_player_X,65
	jl BICollision
	cmp first_player_X,240
	jg BICollision
	
	Angle45Y:
	jmp BEGIN_P2X

	Angle90:
	cmp first_player_y,75
	jl BICollision
	cmp first_player_Y,107
	jg BICollision
	cmp first_player_X,65
	jl BICollision
	cmp first_player_X,240
	jg BICollision
	
	Angle90Y:
	jmp BEGIN_P2X

	Angle135:
	cmp first_player_y,70
	jl BICollision
	cmp first_player_Y,107
	jg BICollision
	cmp first_player_X,60
	jl BICollision
	cmp first_player_X,235
	jg BICollision
	
	Angle135Y:
	jmp BEGIN_P2X

	Angle180:
	cmp first_player_y,70
	jl BICollision
	cmp first_player_Y,110
	jg BICollision
	cmp first_player_X,65
	jl BICollision
	cmp first_player_X,235
	jg BICollision


	
	Angle180Y:
	jmp BEGIN_P2X

	Angle225:
	cmp first_player_y,70
	jl BICollision
	cmp first_player_Y,107
	jg BICollision
	cmp first_player_X,60
	jl BICollision
	cmp first_player_X,235
	jg BICollision
	
	Angle225Y:
	jmp BEGIN_P2X

	Angle270:
	cmp first_player_y,75
	jl BICollision
	cmp first_player_Y,107
	jg BICollision
	cmp first_player_X,60
	jl BICollision
	cmp first_player_X,235
	jg BICollision
	
	Angle270Y:
	jmp BEGIN_P2X

	
	Angle315:
	cmp first_player_y,75
	jl BICollision
	cmp first_player_Y,110
	jg BICollision
	cmp first_player_X,60
	jl BICollision
	cmp first_player_X,235
	jg BICollision
	
	Angle315Y:
	jmp BEGIN_P2X
	;================================================================================================================================================
	;End Checking Collision P1 with wall


BiCollision:
	MOV CL, AH
	MOV AH, 0
	CMP AX, 3
	JA SUBTRACT_P1X
	ADD first_player_X, AX
	JMP CHECK1_XBOUNDS_OVER
SUBTRACT_P1X: NEG AL
	SUB first_player_X, AX
	JMP CHECK1_XBOUNDS_UNDER
	
CHECK1_XBOUNDS_OVER: CMP first_player_X, 296
	JLE BEGIN_P1Y
	MOV first_player_X, 295
	JMP BEGIN_P1Y
	
CHECK1_XBOUNDS_UNDER:CMP first_player_X, 0
	JGE BEGIN_P1Y
	MOV first_player_X, 0
	JMP BEGIN_P1Y
	
BEGIN_P1Y:
	MOV AL, CL
	CMP AX, 3
	JA SUBTRACT_P1Y
	ADD first_player_Y, AX
	JMP CHECK1_YBOUNDS_OVER
SUBTRACT_P1Y:
	NEG AL
	SUB first_player_Y, AX
	JMP CHECK1_YBOUNDS_UNDER
	
CHECK1_YBOUNDS_OVER: CMP first_player_Y, 160
	JLE BEGIN_P2X
	MOV first_player_Y, 160
	JMP BEGIN_P2X
	
CHECK1_YBOUNDS_UNDER:CMP first_player_Y, 20
	JGE BEGIN_P2X
	MOV first_player_Y, 20
	JMP BEGIN_P2X
	
BEGIN_P2X:
	;P2
	;BL : second player X thrust component
	;BH : second player Y thrust component
	cmp Level2,02
	jne BiCollision_2

	cmp second_player_direction,0
	je Angle0_2

	cmp second_player_direction,1
	je Angle45_2

	cmp second_player_direction,2
	je Angle90_2

	cmp second_player_direction,3
	je Angle135_2

	cmp second_player_direction,4
	je Angle180_2

	cmp second_player_direction,0FDH
	je Angle225_2

	cmp second_player_direction,0FEH
	je Angle270_2

	cmp first_player_direction,0FFH
	je Angle315_2
	jne BiCollision_2


	Angle0_2:
	cmp second_player_y,75
	jl BiCollision_2
	cmp second_player_y,110
	jg BiCollision_2

	cmp second_player_x,65
	jl BiCollision_2
	cmp second_player_x,235
	jg BiCollision_2
	
	Angle0_2Y:
	jmp trr

	Angle45_2:
	cmp second_player_y,75
	jl BiCollision_2
	cmp second_player_y,110
	jg BiCollision_2
	cmp second_player_x,65
	jl BiCollision_2
	cmp second_player_x,240
	jg BiCollision_2
	
	Angle45_2Y:
	jmp trr

	Angle90_2:
	cmp second_player_y,75
	jl BiCollision_2
	cmp second_player_y,107
	jg BiCollision_2
	cmp second_player_x,65
	jl BiCollision_2
	cmp second_player_x,240
	jg BiCollision_2
	
	Angle90_2Y:
	jmp trr

	Angle135_2:
	cmp second_player_y,70
	jl BiCollision_2
	cmp second_player_y,107
	jg BiCollision_2
	cmp second_player_x,60
	jl BiCollision_2
	cmp second_player_x,235
	jg BiCollision_2
	
	Angle135_2Y:
	jmp trr

	Angle180_2:
	cmp second_player_y,70
	jl BiCollision_2
	cmp second_player_y,110
	jg BiCollision_2
	cmp second_player_x,65
	jl BiCollision_2
	cmp second_player_x,235
	jg BiCollision_2


	
	Angle180_2Y:
	jmp trr

	Angle225_2:
	cmp second_player_y,70
	jl BiCollision_2
	cmp second_player_y,107
	jg BiCollision_2
	cmp second_player_x,60
	jl BiCollision_2
	cmp second_player_x,235
	jg BiCollision_2
	
	Angle225_2Y:
	jmp trr

	Angle270_2:
	cmp second_player_y,75
	jl BiCollision_2
	cmp second_player_y,107
	jg BiCollision_2
	cmp second_player_x,60
	jl BiCollision_2
	cmp second_player_x,235
	jg BiCollision_2
	
	Angle270_2Y:
	jmp trr

	
	Angle315_2:
	cmp second_player_y,75
	jl BiCollision_2
	cmp second_player_y,110
	jg BiCollision_2
	cmp second_player_x,60
	jl BiCollision_2
	cmp second_player_x,235
	jg BiCollision_2
	
	Angle315_2Y:
	jmp trr

	;===========================================================================================
	;End Checking Collison p2 with wall

	BiCollision_2:
	MOV CL, BH
	MOV BH, 0
	CMP BX, 3
	JA SUBTRACT_P2X
	ADD second_player_X, BX
	JMP CHECK2_XBOUNDS_OVER
SUBTRACT_P2X:
	NEG BL
	SUB second_player_X, BX
	JMP CHECK2_XBOUNDS_UNDER
	
CHECK2_XBOUNDS_OVER: CMP second_player_X, 296
	JLE BEGIN_P2Y
	MOV second_player_X, 295
	JMP BEGIN_P2Y
	
CHECK2_XBOUNDS_UNDER:CMP second_player_X, 0
	JGE BEGIN_P2Y
	MOV second_player_X, 0
	JMP BEGIN_P2Y
	
BEGIN_P2Y:
	MOV BL, CL
	CMP BX, 3
	JA SUBTRACT_P2Y
	ADD second_player_Y, BX
	JMP CHECK2_YBOUNDS_OVER
SUBTRACT_P2Y:
	NEG BL
	SUB second_player_Y, BX
	JMP CHECK2_YBOUNDS_UNDER
	
CHECK2_YBOUNDS_OVER: CMP second_player_Y, 160
	JLE OVER
	MOV second_player_Y, 160
	JMP OVER
	
CHECK2_YBOUNDS_UNDER:CMP second_player_Y, 20
	JGE OVER
	MOV second_player_Y, 20
	JMP OVER
	
OVER:
	call Check_Collision
	call Check_Fire_Damage_P1
	call Check_Fire_Damage_P2
	Game_Over
	TRR:
	RET
	UPDATE_PLAYERS ENDP
	
	DarwFIRE_P1 proc ;the proc that loops over all the player1 fire to update them
	mov bx, offset FireIArrP1
	mov si, offset FireXArrP1
	mov di, offset FireYArrP1
LoopDarwFireArrP1:
	mov al, [bx]
	CMP al, 1
	JZ NoFireToDrawFireP1
	mov cl, [bx + 1]
	
	push si
	push di
	call drawfire
	pop di
	pop si
	
	mov cl, [bx + 1]
	cmp cl, 0
	jnz Fire1A0
	sub [di], 12
	mov ax, [di]
	cmp ax, 15
	jg NoFireToDrawFireP1
	mov [bx], 1
	;determining if the fire exsists or not
Fire1A0:
	cmp cl, 1
	jnz Fire1A45
	sub [si], 12
	sub [di], 12
	mov ax, [di]
	cmp ax, 15
	jng deleteFire1A45
	mov ax, [si]
	cmp ax, 1
	jg NoFireToDrawFireP1
deleteFire1A45:
	mov [bx], 1
	
Fire1A45:
	cmp cl, 2
	jnz Fire1A90
	sub [si], 12
	mov ax, [si]
	cmp ax, 1
	jg NoFireToDrawFireP1
	mov [bx], 1
	
Fire1A90:
	cmp cl, 3
	jnz Fire1A135
	sub [si], 12
	add [di], 12
	mov ax, [di]
	cmp ax, 165
	jnl deleteFire1A135
	mov ax, [si]
	cmp ax, 1
	jg NoFireToDrawFireP1
deleteFire1A135:
	mov [bx], 1
	
Fire1A135:
	cmp cl, 4
	jnz Fire1A180
	add [di], 12
	mov ax, [di]
	cmp ax, 165
	jl NoFireToDrawFireP1
	mov [bx], 1
	
Fire1A180:
	cmp cl, 0fdh
	jnz Fire1A225
	add [si], 12
	add [di], 12
	mov ax, [di]
	cmp ax, 165
	jnl deleteFire1A225
	mov ax, [si]
	cmp ax, 305
	jl NoFireToDrawFireP1
deleteFire1A225:
	mov [bx], 1
	
Fire1A225:
	cmp cl, 0feh
	jnz Fire1A270
	add [si], 12
	mov ax, [si]
	cmp ax, 305
	jl NoFireToDrawFireP1
	mov [bx], 1
	
Fire1A270:
	cmp cl, 0ffh
	add [si], 12
	sub [di], 12
	mov ax, [di]
	cmp ax, 15
	jng deleteFire1A270
	mov ax, [si]
	cmp ax, 305
	jl NoFireToDrawFireP1
deleteFire1A270:
	mov [bx], 1
	
NoFireToDrawFireP1:
	add bx, 2
	add si, 2
	add di, 2
	cmp bx, offset FireXArrP1
	JNZ LoopDarwFireArrP1
	RET
	DarwFIRE_P1 endp
	
	DarwFIRE_P2 proc
	mov bx, offset FireIArrP2
	mov si, offset FireXArrP2
	mov di, offset FireYArrP2
LoopDarwFireArrP2:
	mov al, [bx]
	cmp al, 1
	JZ NoFireToDrawFireP2
	mov cl, [bx + 1]
	
	push si
	push di
	call drawfire
	pop di
	pop si
	
	mov cl, [bx + 1]
	cmp cl, 0
	jnz Fire2A0
	sub [di], 12
	mov ax, [di]
	cmp ax, 15
	jg NoFireToDrawFireP2
	mov [bx], 1
	
Fire2A0:
	cmp cl, 1
	jnz Fire2A45
	sub [si], 12
	sub [di], 12
	mov ax, [di]
	cmp ax, 15
	jng deleteFire2A45
	mov ax, [si]
	cmp ax, 1
	jg NoFireToDrawFireP2
deleteFire2A45:
	mov [bx], 1
	
Fire2A45:
	cmp cl, 2
	jnz Fire2A90
	sub [si], 12
	mov ax, [si]
	cmp ax, 1
	jg NoFireToDrawFireP2
	mov [bx], 1
	
Fire2A90:
	cmp cl, 3
	jnz Fire2A135
	sub [si], 12
	add [di], 12
	mov ax, [di]
	cmp ax, 165
	jnl deleteFire2A135
	mov ax, [si]
	cmp ax, 1
	jg NoFireToDrawFireP2
deleteFire2A135:
	mov [bx], 1
	
Fire2A135:
	cmp cl, 4
	jnz Fire2A180
	add [di], 12
	mov ax, [di]
	cmp ax, 165
	jl NoFireToDrawFireP2
	mov [bx], 1
	
Fire2A180:
	cmp cl, 0fdh
	jnz Fire2A225
	add [si], 12
	add [di], 12
	mov ax, [di]
	cmp ax, 165
	jnl deleteFire2A225
	mov ax, [si]
	cmp ax, 305
	jl NoFireToDrawFireP2
deleteFire2A225:
	mov [bx], 1
	
Fire2A225:
	cmp cl, 0feh
	jnz Fire2A270
	add [si], 12
	mov ax, [si]
	cmp ax, 305
	jl NoFireToDrawFireP2
	mov [bx], 1
	
Fire2A270:
	cmp cl, 0ffh
	add [si], 12
	sub [di], 12
	mov ax, [di]
	cmp ax, 15
	jng deleteFire2A270
	mov ax, [si]
	cmp ax, 305
	jl NoFireToDrawFireP2
deleteFire2A270:
	mov [bx], 1
	
NoFireToDrawFireP2:
	add bx, 2
	add si, 2
	add di, 2
	cmp bx, offset FireXArrP2
	JNZ LoopDarwFireArrP2
	RET
	DarwFIRE_P2 endp
	
Display PROC NEAR

	call drawScore
	mov si, 1
	call drawBackground          ;drawing the background
	cmp Level2,02
	jne L11
	call drawRect
	
	L11:
	mov si, first_player_X       ;position x choise p1
	mov di, first_player_Y       ;position y choise p1
	mov cl, first_player_direction ;rotation choice p1
	mov bl, 0                    ;color choise
	call drawShip                ;drawing the p1 ship
	
	call Fire1_Barriers_Collision
	call DarwFIRE_P1
	

	mov si, second_player_X      ;position x choise p2
	mov di, second_player_Y      ;position y choise p2
	mov cl, second_player_direction ;rotation choice p2
	mov bl, 1                    ;color choise
	call drawShip                ;drawing the p2 ship
	
	call Fire2_Barriers_Collision
	call DarwFIRE_P2
	
	mov cx, 0                    ;set speed of rendering
	mov dx, 0a120h
	mov ah, 86h
	int 15h
	mov ax, 0600h                ;clear old screen
	mov bh, 00
	mov cx, 0
	mov dx, 184fh
	int 10h

	ret
Display		ENDP


