INCLUDE Game.inc

Play    Proc                        ;;;Proc for starting the game
Restart:                            ;;; Checks if the player wants to restart (play again)
    Intialize_Lives_scores          ;;; Intializes the health and score for each player
drawingLoop:
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
	call sendIngameCharacter
	call resiveIngameCharacter
	call TAKE_INPUT
	call UPDATE_PLAYERS
    call Display	
jmp drawingLoop
Play ENDP



