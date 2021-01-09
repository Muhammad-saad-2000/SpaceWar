Intialize_Lives_scores Macro
		Mov Player1_Hearts, 1000     ;intial health
		Mov Player2_Hearts, 1000     ;intial health

		Mov Player1_Score, 0         ; intial score
		Mov Player2_Score, 0         ;initial score
ENDM

Game_Over Macro
		Local Not_Yet, Check_P2, Print, mess
		mov cx, Player1_Hearts       ;checks if P1 health is zero
		cmp cx, 0
		jg Check_P2                  ; if not, check P2
		jz Print                     ; if yes, go to print

	Check_P2:
		mov cx, Player2_Hearts       ;checks if P2 health is zero
		cmp cx, 0
		jg Not_Yet                   ;if not, go to Not_Yet


	Print:                        ;Prints Game_Over_Mess, a message that says GameOver
		;Game_Over Message
		mov ah, 02                   ;Moves Cursor to nearly center of the screen
		mov dl, 16
		mov dh, 10
		int 10h
		mov di, offset Game_Over_Mess
	mess:
		xor bx, bx
		mov bl, 0ch
		mov ah, 14                   ;Prints chars in Graphics mode
		mov al, [di]
		int 10h

		inc di
		mov al, [di]
		cmp al, '$'
		jnz mess

		;Wait for input key
		MOV AH, 00h
		INT 16H
		;if the user Pressed y
		cmp AH, 15h
		jz Restart                   ;A label in the game proc, to restart

		mov AH, 06H                  ;else (the player didn't press y), Clear screen, then
		mov AL, 00H
		mov BH, 07H
		mov cx, 0000H
		mov dx, 184FH
		int 10h

		;;Terminate the game
		mov ah, 04ch
		int 21h
		;=======================

	Not_Yet:                      ;A label indicating that P1 health and P2 health are both nonzero
ENDM


drawScore Proc

		mov cx, 00                   ;sets the intial pixel of the first line to start at position (00, 20)
		mov dx, 20
	Line_High:
		mov ah, 0ch                  ;draws the line till the end of the screen at position (320, 20)
		mov al, 0Fh
		int 10h
		inc cx
		cmp cx, 320
		jnz Line_High

		mov cx, 00                   ;sets the intial pixel of the first line to start at position (00, 180)
		mov dx, 180
	Line_Low:
		mov ah, 0ch                  ;draws the line till the end of the screen at position (320, 180)
		mov al, 0Fh
		int 10h
		inc cx
		cmp cx, 320
		JNZ Line_Low
		;==========================================================
		mov ah, 02                   ;moves cursor to position (0, 0)
		mov dl, 0
		mov dh, 0
		int 10h
		mov di, offset First_Player_Name ;the name of p1 to apear next to score
		add di, 2
	mess1:
		xor bx, bx
		mov bl, 0ch                  ; Text in red color
		mov ah, 14                   ;Prints chars in the graphica mode
		mov al, [di]
		int 10h

		inc di
		mov al, [di]
		cmp al, '$'
		jnz mess1
		;-----------------------------------------------------------
		push ax
		push bx
		push cx
		push dx

		mov ah, 02                   ;moves cursor to position (0, 0)
		mov dl, 22
		mov dh, 0
		int 10h
		mov di, offset send ;the name of p1 to apear next to score
	messFromMe:
		xor bx, bx
		mov al, [di]
		cmp al, '$'
		jz outMessFromMe
		mov bl, 0ch                  ; Text in red color
		mov ah, 14                   ;Prints chars in the graphica mode
		inc di
		int 10h	
		jmp messFromMe
	outMessFromMe:

		mov ah, 02                   ;moves cursor to position (0, 0)
		mov dl, 22
		mov dh, 24
		int 10h
		mov di, offset resive ;the name of p1 to apear next to score
	messFromOther:
		xor bx, bx
		mov al, [di]
		cmp al, '$'
		jz outMessFromOther
		mov bl, 0ch                  ; Text in red color
		mov ah, 14                   ;Prints chars in the graphica mode
		inc di
		int 10h	
		jmp messFromOther
	outMessFromOther:

		pop dx
		pop cx
		pop bx
		pop ax
		; * * * * * * * * * * * * * * * * * * * * * * 
		mov di, offset Lives_Word    ; DI now carries the offset of Lives_Word
		mov ah, 02                   ; moves the cursor to (00, 02)
		mov dl, 0
		inc dh
		int 10h
		cmp dh, 1
		jz mess1


		;===============================================
		;===============================================
		mov ah, 02                   ;moves the cursor to (00, 24)
		mov dl, 0
		mov dh, 24
		int 10h
		mov di, offset Second_Player_Name
		add di, 2

	mess2:
		xor bx, bx
		mov bl, 0ch
		mov ah, 14
		mov al, [di]
		int 10h

		inc di
		mov al, [di]
		cmp al, '$'
		jnz mess2
		; * * * * * * * * * * * * * * * * * * * * * * 
		; * * * * * * * * * * * * * * * * * * * * * * 
		mov di, offset Lives_Word
		mov ah, 02                   ;moves the cursor to (00, 23)
		mov dl, 0
		dec dh
		int 10h
		cmp dh, 23
		jz mess2
		; * * * * * * * * * * * * * * * * * * * * * * * 
		; * * * * * * * * * * * * * * * * * * * * * * * 


		mov ax, Player1_Score        ;Prints P1 score
		call Printnum
		mov ah, 02
		mov di, offset First_Player_Name
		inc di
		mov dl, [di]
		inc dl
		mov dh, 0
		int 10h
		mov di, offset Score_Num_char

	Num1:
		xor bx, bx
		mov bl, 0ch
		mov ah, 14
		mov al, [di]
		int 10h
		inc di
		mov al, [di]
		cmp al, '$'
		jnz Num1
		;========================================
		;========================================
		mov ax, Player1_Hearts       ;Prints P1 health
		call Printnum
		mov ah, 02
		mov dl, 8
		mov dh, 1
		int 10h
		mov di, offset Score_Num_char

	Num2:
		xor bx, bx
		mov bl, 0ch
		mov ah, 14
		mov al, [di]
		int 10h
		inc di
		mov al, [di]
		cmp al, '$'
		jnz Num2

		mov ax, Player2_Score        ;Prints P2 score
		call Printnum
		mov ah, 02
		mov di, offset Second_Player_Name
		inc di
		mov dl, [di]
		inc dl
		mov dh, 24
		int 10h
		mov di, offset Score_Num_char

	Num3:
		xor bx, bx
		mov bl, 0ch
		mov ah, 14
		mov al, [di]
		int 10h
		inc di
		mov al, [di]
		cmp al, '$'
		jnz Num3
		;========================================
		;========================================
		mov ax, Player2_Hearts       ;Prints P2 health
		call Printnum
		mov ah, 02
		mov dl, 8
		mov dh, 23
		int 10h
		mov di, offset Score_Num_char

	Num4:
		xor bx, bx
		mov bl, 0ch
		mov ah, 14
		mov al, [di]
		int 10h
		inc di
		mov al, [di]
		cmp al, '$'
		jnz Num4

		ret
drawScore ENDP


Check_Collision Proc
	

		mov cx, first_player_X
		sub cx, second_player_X      ;Sub P2_x from P1_x
		cmp cx, 15                   ; checks if they lie within range of 15
		ja No1                       ;if no, then do sub P2_x from P1_x
		mov cx, first_player_Y       ;if yes, compare their Y positions
		sub cx, second_player_Y
		cmp cx, 15
		ja No1                       ;if no, then do sub P2_y from P1_y
		jmp Yes                      ;if they lie within range of 15, go to yes
	No1:
		mov cx, second_player_X
		sub cx, first_player_X
		cmp cx, 15
		ja No2
		mov cx, second_player_Y
		sub cx, first_player_Y
		cmp cx, 15
		ja No2

	Yes: sub Player1_Hearts, 100  ;A collison dec health by 100
		jnc Pos1                     ;checks that health is not negative after sub
		mov Player1_Hearts, 00       ;if health is negative (the carry flag is set, health wrapped arround), put zero

	Pos1: sub Player2_Hearts, 100
		jnc Pos2
		mov Player2_Hearts, 00
	Pos2:
		mov cx, 0                    ;Delay to render the ships while they return to original positions
		mov dx, 0a120h
		mov ah, 86h
		int 15h
		mov first_player_X, 150      ; Reset P1 position
		mov first_player_Y, 20
		mov second_player_X, 150     ;Reset P2 position
		mov second_player_Y, 180

		mov first_player_direction, 00h ;Reset direction
		mov first_player_thrust, 00h ;Reset thrust

		mov second_player_direction, 00h
		mov second_player_thrust, 00h

	No2:
		ret
Check_Collision ENDP



Printnum PROC
		
		; mov Rev_Score_Num_char, 0
		; mov si, offset Rev_Score_Num_char
		; ;initilize count
		;moves four '$' to Score_Num_char, neccessary to print numbers as a string
		; as it prints until '$', so the intial string should always be intialized to "$$$$"
		mov si, offset Score_Num_char
		mov [si], '$'
		inc si
		mov [si], '$'
		inc si
		mov [si], '$'
		inc si
		mov [si], '$'

		mov si, offset Score_Num_char ;moves SI to Score_Num_char to write the number as a character on it

		mov cx, 0
		mov dx, 0
	label1:
		; if ax is zero
		cmp ax, 0
		je print1                    ;the number is zero so cx=0 which means zero digits

		;initilize bx to 10
		mov bx, 10

		; extract the last digit
		div bx

		;push it in the stack
		push dx

		;increment the count
		inc cx

		;set dx to 0
		xor dx, dx
		jmp label1
	print1:
		;check if count
		;is greater than zero
		cmp cx, 0
		je exit                      ;if the number contains zero digits, that is it's zero

		;pop the top of stack
		pop dx

		;add 48 so that it
		;represents the ASCII
		;value of digits
		add dx, 48


		mov [SI], dl
		inc SI
		;decrease the count
		dec cx
		cmp cx, 0
		je Ter                       ;cx=0 (num of digits reached zero)

		jmp print1


	exit:
		mov dl, '0'                  ;if the number was zero, then it will write zero on SI which pints to offset of Score_Num_char
		mov [SI], dl
	Ter:                          ;The number is not zero

		ret
Printnum	ENDP



Check_Fire_Damage_P1 Proc    ;Checks if P1 rockets hits P2 ship or not, then updates the score and health accordingly

		mov bx, offset FireIArrP1    ;points to the state array of first player rockets
		mov SI, offset FireXArrP1    ;points to the x - pos array of first player rockets
		mov DI, offset FireYArrP1    ;points to the y - pos array of first player rockets

	Exists:
		cmp bx, offset FireXArrP1    ;checks if all rockets are processed
		jz Terminate1

		mov al, [bx]
		cmp al, 2                    ;checks if the rocket at [bx] exists or not
		jnz iterate

		mov cx, second_player_X      ;
		mov ax, [SI]                 ;
		sub cx, ax                   ;compares first player x - pos with the bullet x - pos
		jc Wrap_P1_1                 ; if under flow occurs, then we need to switch args and then compare
		cmp cx, 20                   ;Else, check if they lie within a range of 20
		jng noSwapP1_1               ;Check for the Y positions
		jg iterate

	Wrap_P1_1:
		add cx, ax                   ;add the subtracted amount
		sub ax, cx                   ;then compare
		cmp ax, 20                   ;check if they lie within a range of 20
		jng noSwapP1_1               ;if yes, check for the Y positions
		jg iterate                   ;if no, then go to the next rocket

	noSwapP1_1:
		mov cx, second_player_Y
		mov ax, [DI]
		sub cx, ax
		jc Wrap_P1_2
		cmp cx, 10                   ;check if they lie within a range of 10
		jng noSwapP1_2
		jg iterate

	Wrap_P1_2:
		add cx, ax
		sub ax, cx
		cmp ax, 10                   ;Check if they lie within a range of 10
		jng noSwapP1_2
		jg iterate

	noSwapP1_2:
		sub Player2_Hearts, 10       ; if they collide dec P2 health by 10
		add Player1_Score, 10        ;inc P1 score by 10
		mov [bx], 1                  ;rocket should disappear after it hits the ship
		cmp Player2_Hearts, 0        ;if P2 health reaches 0, terminate
		jnz iterate
		jmp Terminate1

	iterate:
		add bx, 2
		add SI, 2
		add DI, 2
		jmp Exists

	Terminate1:

		ret
Check_Fire_Damage_P1 ENDP




Check_Fire_Damage_P2 Proc    ;Checks if P2 rockets hits P1 ship or not, then updates the score and health accordingly, the same logic as above

		mov bx, offset FireIArrP2
		mov SI, offset FireXArrP2
		mov DI, offset FireYArrP2

	Exists2:
		cmp bx, offset FireXArrP2
		jz Terminate2

		mov al, [bx]
		cmp al, 2
		jnz iterate2

		mov cx, first_player_X
		mov ax, [SI]
		sub cx, ax
		jc Wrap_P2_1
		cmp cx, 20
		jng noSwapP2_1
		jg iterate2

	Wrap_P2_1:
		add cx, ax
		sub ax, cx
		cmp ax, 20
		jng noSwapP2_1
		jg iterate2

	noSwapP2_1:
		mov cx, first_player_Y
		mov ax, [DI]
		sub cx, ax
		jc Wrap_P2_2
		cmp cx, 10
		jng noSwapP2_2
		jg iterate2

	Wrap_P2_2:
		add cx, ax
		sub ax, cx
		cmp ax, 10
		jng noSwapP2_2
		jg iterate2

	noSwapP2_2:
		sub Player1_Hearts, 10
		add Player2_Score, 10
		mov [bx], 1
		cmp Player1_Hearts, 0
		jnz iterate2
		jmp Terminate2

	iterate2:
		add bx, 2
		add SI, 2
		add DI, 2
		jmp Exists2
	Terminate2:

		ret
Check_Fire_Damage_P2 ENDP


Fire1_Barriers_Collision	Proc
		mov bx, offset FireIArrP1
		mov SI, offset FireXArrP1
		mov DI, offset FireYArrP1

	while1:
		cmp bx, offset FireXArrP1
		jz Exit1

		mov al, [bx]
		cmp al, 2
		jnz itr1

		mov ax, [SI]
		mov cx,235
		sub cx,ax
		jc 	itr1
		mov cx,65
		sub cx,ax
		jnc itr1

		mov ax,[DI]
		mov cx,110
		sub cx,ax
		jc 	itr1
		mov cx,75
		sub cx,ax
		jnc itr1

		mov [bx],1
		
	itr1:
	add bx,2
	add SI,2
	add DI,2
	jmp while1


	Exit1:

	ret
Fire1_Barriers_Collision	ENDP

Fire2_Barriers_Collision	Proc

	mov bx, offset FireIArrP2
		mov SI, offset FireXArrP2
		mov DI, offset FireYArrP2

	while2:
		cmp bx, offset FireXArrP2
		jz Exit2

		mov al, [bx]
		cmp al, 2
		jnz itr2

		mov ax, [SI]
		mov cx,235
		sub cx,ax
		jc 	itr2
		mov cx,65
		sub cx,ax
		jnc itr2

		mov ax,[DI]
		mov cx,110
		sub cx,ax
		jc 	itr2
		mov cx,75
		sub cx,ax
		jnc itr2

		mov [bx],1
		
	itr2:
	add bx,2
	add SI,2
	add DI,2
	jmp while2

	
	Exit2:
	

	ret
Fire2_Barriers_Collision	ENDP
