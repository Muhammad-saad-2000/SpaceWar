.MODEL MEDIUM
.STACK 64
.DATA
;DIRECTION CONSTANTS
;0 DEG 
UP                                EQU 00H  
;180 DEG
DOWN                              EQU 04H
;90 DEG
LEFT                              EQU 02H    
;-90 DEG
RIGHT                             EQU 0FEH
;45 DEG
UPPER_LEFT                        EQU 01H 
;-45 DEG
UPPER_RIGHT                       EQU 0FFH
;135 DEG
LOWER_LEFT                        EQU 03H
;-135
LOWER_RIGHT                       EQU 0FDH  

;SCAN CODES                                    
FIRST_PLAYER_ROT_LEFT_BTN         EQU 75
FIRST_PLAYER_ROT_RIGHT_BTN        EQU 77
FIRST_PLAYER_INCR_THRUST_BTN      EQU 72 
FIRST_PLAYER_DECR_THRUST_BTN      EQU 80  
 
SECOND_PLAYER_ROT_LEFT_BTN        EQU 1EH
SECOND_PLAYER_ROT_RIGHT_BTN       EQU 20H
SECOND_PLAYER_INCR_THRUST_BTN     EQU 11H
SECOND_PLAYER_DECR_THRUST_BTN     EQU 1FH

first_player_direction   DB 00h
first_player_thrust      DB 00h 
first_player_X           DW 150
first_player_Y           DW 000
second_player_direction  DB 00h
second_player_thrust     DB 00h
second_player_X          DW 150
second_player_Y          DW 100
;***************************************************************************************************************************************************************
.CODE
INCLUDE OPLogic.INC
INCLUDE models.INC
main proc far
mov ax,@data
mov ds,ax

mov ah,0;set screen 320width*200height
mov al,13h 
int 10h

drawingLoop:
	call TAKE_INPUT
	call UPDATE_PLAYERS
    mov si,1
    call drawBackground ;drawing the background
	mov si,first_player_X;position x choise p1
	mov di,first_player_Y;position y choise p1
	mov cl,first_player_direction;rotation choice p1
    mov bl,0;color choise
	call drawShip;drawing the ship
    mov si,second_player_X;position x choise p2
	mov di,second_player_Y;position y choise p2
	mov cl,second_player_direction;rotation choice p2
    mov bl,1;color choise
	call drawShip;drawing the ship
	mov cx, 0;set speed of rendering
	mov dx, 0a120h
	mov ah, 86h
	int 15h

	mov ax,0600h;clear old screen
	mov bh,00    
	mov cx,0     
	mov dx,184fh
	int 10h
jmp drawingLoop

hlt
main endp
;***************************************************************************************************************************************************************
;procedures that requires data access
TAKE_INPUT       PROC NEAR  ;take the inputs from users

    IS_KEY_PRESSED:    
        MOV AH, 1                     
        INT 16H  
        JZ TERMINATE ;No key presses to handle, return
    ;Else, take a look at the pressed key
    MOV AH, 0
    INT 16H
    ;And compare pressed key against known keys 
    ;P1              
    KEY1:   CMP AH, FIRST_PLAYER_ROT_LEFT_BTN
    JNZ KEY2  
        ROTATE_PLAYER1_ANTICLOCK
    JMP IS_KEY_PRESSED  
                                         
    KEY2:   CMP AH, FIRST_PLAYER_ROT_RIGHT_BTN    
    JNZ KEY3
        ROTATE_PLAYER1_CLOCK 
    JMP IS_KEY_PRESSED  
              
    KEY3:   CMP AH, FIRST_PLAYER_INCR_THRUST_BTN
    JNZ KEY4
        INCR_PLAYER1_THRUST
    JMP IS_KEY_PRESSED  
                             
    KEY4:   CMP AH, FIRST_PLAYER_DECR_THRUST_BTN
    JNZ KEY5    
        DECR_PLAYER1_THRUST
    JMP IS_KEY_PRESSED
             
    ;P2   
    KEY5:   CMP AH, SECOND_PLAYER_ROT_LEFT_BTN   
    JNZ KEY6
        ROTATE_PLAYER2_ANTICLOCK        
    JMP IS_KEY_PRESSED   
             
    KEY6:   CMP AH, SECOND_PLAYER_ROT_RIGHT_BTN 
    JNZ KEY7
        ROTATE_PLAYER2_CLOCK                     
    JMP IS_KEY_PRESSED  
              
    KEY7:   CMP AH, SECOND_PLAYER_INCR_THRUST_BTN
    JNZ KEY8
        INCR_PLAYER2_THRUST
    JMP IS_KEY_PRESSED 
                                
    KEY8:   CMP AH, SECOND_PLAYER_DECR_THRUST_BTN
    JNZ IS_KEY_PRESSED   
        DECR_PLAYER2_THRUST
    JMP IS_KEY_PRESSED
    
    TERMINATE:   RET
TAKE_INPUT       ENDP

UPDATE_PLAYERS   PROC NEAR  ;updated the thrust and the attitude values to update X,Y positions for the two players
    DETERMINE_THRUST_COMPONENTS
    ;P1
    ;AL : first player X thrust component
    ;AH : first player Y thrust component      
    MOV CL, AH 
    MOV AH, 0
    CMP AX, 3
    JA  SUBTRACT_P1X
    ADD first_player_X, AX
    JMP CHECK1_XBOUNDS_OVER
    SUBTRACT_P1X: NEG AL
    SUB first_player_X, AX 
    JMP CHECK1_XBOUNDS_UNDER
    
    CHECK1_XBOUNDS_OVER:    CMP first_player_X, 296
    JLE BEGIN_P1Y
    MOV first_player_X, 295
    JMP BEGIN_P1Y
                         
    CHECK1_XBOUNDS_UNDER:   CMP first_player_X, 0
    JGE BEGIN_P1Y
    MOV first_player_X, 0
    JMP BEGIN_P1Y
    
    BEGIN_P1Y: 
        MOV AL, CL
        CMP AX, 3
    JA  SUBTRACT_P1Y
    ADD first_player_Y, AX
    JMP CHECK1_YBOUNDS_OVER
    SUBTRACT_P1Y: 
        NEG AL
        SUB first_player_Y, AX 
    JMP CHECK1_YBOUNDS_UNDER
    
    CHECK1_YBOUNDS_OVER:    CMP first_player_Y, 176
    JLE BEGIN_P2X
    MOV first_player_Y, 175
    JMP BEGIN_P2X
                         
    CHECK1_YBOUNDS_UNDER:   CMP first_player_Y, 0
    JGE BEGIN_P2X
    MOV first_player_Y, 0 
    JMP BEGIN_P2X
                        
    BEGIN_P2X:
    ;P2
    ;BL : second player X thrust component
    ;BH : second player Y thrust component
    MOV CL, BH 
    MOV BH, 0
    CMP BX, 3
    JA  SUBTRACT_P2X
    ADD second_player_X, BX
    JMP CHECK2_XBOUNDS_OVER
    SUBTRACT_P2X: 
        NEG BL
        SUB second_player_X, BX 
    JMP CHECK2_XBOUNDS_UNDER
    
    CHECK2_XBOUNDS_OVER:    CMP second_player_X, 296
    JLE BEGIN_P2Y
    MOV second_player_X, 295
    JMP BEGIN_P2Y
                         
    CHECK2_XBOUNDS_UNDER:   CMP second_player_X, 0
    JGE BEGIN_P2Y
    MOV second_player_X, 0
    JMP BEGIN_P2Y
    
    BEGIN_P2Y: 
        MOV BL, CL
        CMP BX, 3
    JA  SUBTRACT_P2Y
    ADD second_player_Y, BX
    JMP CHECK2_YBOUNDS_OVER
    SUBTRACT_P2Y:
        NEG BL
        SUB second_player_Y, BX 
    JMP CHECK2_YBOUNDS_UNDER
    
    CHECK2_YBOUNDS_OVER:    CMP second_player_Y, 176
    JLE OVER
    MOV second_player_Y, 175
    JMP OVER
                         
    CHECK2_YBOUNDS_UNDER:   CMP second_player_Y, 0
    JGE OVER
    MOV second_player_Y, 0 
    JMP OVER
    
    OVER: RET
UPDATE_PLAYERS   ENDP


end main