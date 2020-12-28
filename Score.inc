Intialize_Lives_scores Macro
	                       Mov Player1_Hearts,1000
	                       Mov Player2_Hearts,1000

	                       Mov Player1_Score,0
	                       Mov Player2_Score,0
ENDM

Game_Over Macro
	          Local Not_Yet,Check_P2,Print,mess
	          mov   cx,Player1_Hearts
	          cmp   cx,0
	          jg    Check_P2
	          jz    Print
	
	Check_P2: 
	          mov   cx,Player2_Hearts
	          cmp   cx,0
	          jg    Not_Yet
	Print:    
	;	;;; Game_Over Message
	          mov   ah,02
	          mov   dl,16
	          mov   dh,10
	          int   10h
	          mov   di,offset Game_Over_Mess
	mess:     
	          xor   bx,bx
	          mov   bl,0ch
	          mov   ah,14
	          mov   al,[di]

	          int   10h
	          inc   di
	          mov   al,[di]
	          cmp   al,'$'
	          jnz   mess
	;;Wait for input key
	          MOV   AH, 00h
	          INT   16H
	;;The user Pressed y
	          cmp   AH,15h
	          jz    Restart
		  
		  mov	AH,06H
		  mov	AL,00H
		  mov 	BH,07H
		  mov 	cx,0000H
		  mov	dx,184FH
		  int 	10h	
	;;The user choosed to end
	          mov   ah,04ch
	          int   21h
	;;=======================

	Not_Yet:  
ENDM
;drawScore MACRO
drawScore         Proc
	          ;LOCAL Line_High,Line_Low,mess1,mess2
	          mov   cx,00
	          mov   dx,20
	Line_High:
	          mov   ah,0ch
	          mov   al,0Fh
	          int   10h
	          inc   cx
	          cmp   cx,320
	          jnz   Line_High
                  
	          mov   cx,00
	          mov   dx,180
	Line_Low: 
	          mov   ah,0ch
	          mov   al,0Fh
	          int   10h
	          inc   cx
	          cmp   cx,320
	          JNZ   Line_Low
	;;==========================================================
	          mov   ah,02
	          mov   dl,0
	          mov   dh,0
	          int   10h
	          mov   di,offset Score_Word
	mess1:    
	          xor   bx,bx
	          mov   bl,0ch
	          mov   ah,14
	          mov   al,[di]
	          int   10h

	          inc   di
	          mov   al,[di]
	          cmp   al,'$'
	          jnz   mess1
                ;;**********************
                  inc   di
	          mov   ah,02
	          mov   dl,0
	          inc   dh
	          int   10h
                  cmp   dh,1
	          jz    mess1


	    ;;===============================================
            ;;===============================================
                  mov   ah,02
	          mov   dl,0
	          mov   dh,24
	          int   10h
	          mov   di,offset Score_Word

                  
	mess2:    
	          xor   bx,bx
	          mov   bl,0ch
	          mov   ah,14
	          mov   al,[di]
	          int   10h

	          inc   di
	          mov   al,[di]
	          cmp   al,'$'
	          jnz   mess2
                  ;;**********************
                  ;;**********************
                  inc   di
	          mov   ah,02
	          mov   dl,0
	          dec   dh
	          int   10h
                  cmp   dh,23
	          jz    mess2
                  ;;***********************
                  ;;***********************


                mov ax,Player1_Score
                call Printnum
                mov   ah,02
	        mov   dl,8
	        mov   dh,0
	        int   10h
	        mov   di,offset Score_Num_char
        
        Num1:
                  xor   bx,bx
	          mov   bl,0ch
	          mov   ah,14
	          mov   al,[di]
                  int   10h
	          inc   di
	          mov   al,[di]
	          cmp   al,'$'
	          jnz   Num1
                ;;========================================
                ;;========================================
                mov ax,Player1_Hearts
                call Printnum
                mov   ah,02
	        mov   dl,8
	        mov   dh,1
	        int   10h
	        mov   di,offset Score_Num_char
        
        Num2:
                  xor   bx,bx
	          mov   bl,0ch
	          mov   ah,14
	          mov   al,[di]
                  int   10h
                  inc   di
	          mov   al,[di]
	          cmp   al,'$'
	          jnz   Num2
  
                




                mov ax,Player2_Score
                call Printnum
                mov   ah,02
	        mov   dl,8
	        mov   dh,24
	        int   10h
	        mov   di,offset Score_Num_char
        
        Num3:
                  xor   bx,bx
	          mov   bl,0ch
	          mov   ah,14
	          mov   al,[di]
                  int   10h
	          inc   di
	          mov   al,[di]
	          cmp   al,'$'
	          jnz   Num3
                ;;========================================
                ;;========================================
                mov ax,Player2_Hearts
                call Printnum
                mov   ah,02
	        mov   dl,8
	        mov   dh,23
	        int   10h
	        mov   di,offset Score_Num_char
        
        Num4:
                  xor   bx,bx
	          mov   bl,0ch
	          mov   ah,14
	          mov   al,[di]
                  int   10h
	          inc   di
	          mov   al,[di]
	          cmp   al,'$'
	          jnz   Num4
  




;ENDM
                  ret
drawScore ENDP 
;Check_Collision Macro
Check_Collision Proc 
	               ; Local No1,No2,Yes

	                mov   cx,first_player_X
	                sub   cx,second_player_X
	                cmp   cx,15
	                ja    No1
	                mov   cx,first_player_Y
	                sub   cx,second_player_Y
	                cmp   cx,15
	                ja    No1
	                jmp   Yes
	No1:            
	                mov   cx,second_player_X
	                sub   cx,first_player_X
	                cmp   cx,15
	                ja    No2
	                mov   cx,second_player_Y
	                sub   cx,first_player_Y
	                cmp   cx,15
	                ja    No2
	                
        Yes:            sub   Player1_Hearts,100
			jnc   Pos1
			mov   Player1_Hearts,00
	Pos1:           sub   Player2_Hearts,100
			jnc   Pos2
			mov   Player2_Hearts,00
	Pos2:
	                mov   cx, 0                      	;set speed of rendering
	                mov   dx, 0a120h
	                mov   ah, 86h
	                int   15h
	                mov   first_player_X,150
	                mov   first_player_Y,20
	                mov   second_player_X,150
	                mov   second_player_Y,180
        
	                mov   first_player_direction,00h
	                mov   first_player_thrust, 00h

	                mov   second_player_direction,00h
	                mov   second_player_thrust, 00h

;ENDM
			No2:
	      ret      
Check_Collision ENDP 



Printnum PROC            
      
;       mov Rev_Score_Num_char,0
;       mov si, offset Rev_Score_Num_char
;       ;initilize count 
      mov si, offset Score_Num_char
      mov [si],'$'
      inc si
      mov [si],'$'
      inc si
      mov [si],'$'
      inc si
      mov [si],'$'

      mov si, offset Score_Num_char
      
      mov cx,0 
      mov dx,0 
    label1: 
        ; if ax is zero 
        cmp ax,0 
        je print1       
          
        ;initilize bx to 10 
        mov bx,10         
          
        ; extract the last digit 
        div bx                   
          
        ;push it in the stack 
        push dx               
          
        ;increment the count 
        inc cx               
          
        ;set dx to 0  
        xor dx,dx 
        jmp label1 
    print1: 
        ;check if count  
        ;is greater than zero 
	cmp cx,0 
        je exit
          
        ;pop the top of stack 
        pop dx 
          
        ;add 48 so that it  
        ;represents the ASCII 
        ;value of digits 
        add dx,48 
          
        ;interuppt to print a 
        ;character 
        mov [SI],dl
	inc SI         
        ;decrease the count 
        dec cx 
        cmp cx,0 
        je Ter
        
	jmp print1


exit:  
	mov dl,'0'
	mov [SI],dl
 Ter:
     
ret
Printnum  ENDP 



Check_Fire_Damage_P1	Proc

	mov bx,offset FireIArrP1
	mov SI,offset FireXArrP1
	mov DI,offset FireYArrP1

	Exists:
	cmp bx,offset FireXArrP1
	jz Terminate1

	mov al,[bx]
	cmp al,2
	jnz iterate

			mov   cx,second_player_X
			mov   ax,[SI]
			sub   cx,ax
			jc    Wrap_P1_1
	        	cmp   cx,20
			jng   noSwapP1_1
	                jg    iterate
			
		Wrap_P1_1:
			add   cx,ax
			sub   ax,cx
			cmp   ax,20   
			jng   noSwapP1_1
	                jg    iterate

		noSwapP1_1:	
	                mov   cx,second_player_Y
	                mov   ax,[DI]
			sub   cx,ax
	                jc    Wrap_P1_2
	        	cmp   cx,30
			jng   noSwapP1_2
	                jg    iterate
			
		Wrap_P1_2:
			add   cx,ax
			sub   ax,cx
			cmp   ax,30   
			jng   noSwapP1_2
	                jg    iterate

		noSwapP1_2:
   	                sub   Player2_Hearts,10
			add   Player1_Score,10
	                mov   [bx],1
			cmp   Player2_Hearts,0
			jnz   iterate 
	                jmp   Terminate1

	iterate: 
	add bx,2
	add SI,2
	add DI,2
	jmp Exists

	Terminate1:
	
ret
Check_Fire_Damage_P1 ENDP




Check_Fire_Damage_P2	Proc

	mov bx,offset FireIArrP2
	mov SI,offset FireXArrP2
	mov DI,offset FireYArrP2

	Exists2:
	cmp bx,offset FireXArrP2
	jz Terminate2

	mov al,[bx]
	cmp al,2
	jnz iterate2

			mov   cx,first_player_X
			mov   ax,[SI]
			sub   cx,ax
	                jc    Wrap_P2_1
	        	cmp   cx,20
			jng   noSwapP2_1
	                jg    iterate2
			
		Wrap_P2_1:
			add   cx,ax
			sub   ax,cx
			cmp   ax,20   
			jng   noSwapP2_1
	                jg    iterate2

		noSwapP2_1:	
	                mov   cx,first_player_Y
	                mov   ax,[DI]
			sub   cx,ax
			jc    Wrap_P2_2
	        	cmp   cx,30
			jng   noSwapP2_2
	                jg    iterate2

	        Wrap_P2_2:
			add   cx,ax
			sub   ax,cx
			cmp   ax,30   
			jng   noSwapP2_2
	                jg    iterate2

		noSwapP2_2:
   	                sub   Player1_Hearts,10
			add   Player2_Score,10
	               	mov   [bx],1
	              	cmp   Player1_Hearts,0
			jnz   iterate2 
	                jmp   Terminate2

	iterate2: 
	add bx,2
	add SI,2
	add DI,2
	jmp Exists2
	Terminate2:

ret
Check_Fire_Damage_P2 ENDP
