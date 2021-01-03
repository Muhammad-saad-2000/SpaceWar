INCLUDE Game.inc

Play    Proc                        ;;;Proc for starting the game
Restart:                            ;;; Checks if the player wants to restart (play again)
    Intialize_Lives_scores          ;;; Intializes the health and score for each player
drawingLoop:
	call TAKE_INPUT
	call UPDATE_PLAYERS
    call Display
jmp drawingLoop

Play ENDP



