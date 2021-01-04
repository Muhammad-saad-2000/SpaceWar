	;This is a macro to scroll the upper half of the screen when it's compleltely full of charachters
	scrollUpper MACRO

		mov ax,0601h ;scroll by one line
		mov bh,00h ;color
		mov ch,0   ;begin row
		mov cl,0   ;begin col    
		mov dh,11  ;end row
		mov dl,79  ;end col
		int 10h 

	ENDM scrollUpper
	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	;This is a macro to scroll the lower half of the screen when it's compleltely full of charachters
	scrollLower MACRO
	
		mov ax, 0601h  ;scroll by one line
		mov bh, 00h ;color
		mov ch, 13
		mov cl, 0
		mov dh, 24
		mov dl, 79
		int 10h
	
	ENDM scrollLower
	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	;this is a macro to get the cursor position of the send mode
	setCursorSender MACRO

		mov ah, 3h
		mov bh, 0h
		int 10h
		mov XCursorSender, dl
		mov YCursorSender, dh

	ENDM setCursorSender
	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	;this is a macro to get the cursor position of the recieve mode
	setCursorReciever MACRO

		mov ah, 3h
		mov bh, 0h
		int 10h
		mov XCursorReciever, dl
		mov yCursorReciever, dh

	ENDM setCursorReciever
	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	;this is a macro to set the cursor in dx for send or receive mode
	setCursor MACRO x, y

		mov ah, 2
		mov bh, 0
		mov dl, x
		mov dh, y
		int 10h

	ENDM setCursor
	
	; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

.data
	VALUE       db ?	;VALUE which will be sent or recieved by 
	YCursorSender  db 0 ;to store Yposition of cursor in send mode
	XCursorSender db 0 ;to store Xposition of cursor in rec mode
	XCursorReciever      db 0 ;to store Yposition of cursor in send mode
	yCursorReciever db 0Dh ;to store Xposition of cursor in rec mode
.code
chat proc
	          mov         ax, @data
	          mov         ds, ax
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
	
	
	;Split screen
	;======================================================================
	          mov         ah, 0
	          mov         al, 13h
	          int         10h
	
	          mov         ax, 0600h
	          mov         bh, 00
	          mov         cx, 0
	          mov         dx, 184fh
	          int         10h
	
	          mov         ah, 2
	          mov         dx, 0c00h
	          int         10h
	
	          mov         ah, 9
	          mov         bh, 0
	          mov         al, '_'
	          mov         cx, 28h
	          mov         bl, 0Fh
	          int         10h
	;===============================================================
	          xor         dx, dx ;initialize cursor position to 0,0
	input:    
	          mov         ah, 2 ;set cursor at right position , initially at 0,0
	          int         10h
			  CMP VALUE,27
			  JE CLOSES
	          mov         ah, 1 ;check if there's an input
	          int         16h
	          jz          RecieveMode ;if No input , jmp to check if there's a char input in receive mode
	
	read:     mov         ah, 0 ;read char from buffer
	          int         16h
	          mov         VALUE, al ;mov char ascii to VALUE

	;check if backspace key is pressed
	          cmp         VALUE, 08h
	          je          bcs

	;check if enter key is pressed
	          cmp         VALUE, 0dh
	          je          enter

	; check if esc key is pressed
		     cmp VALUE,27
			 JE SendMode
			 JNE KEY
	         
	CLOSES:
	MOV VALUE,00
	JMP ChoosingMenu
	
	
	bcs:      
	          cmp         XCursorSender, 0 ;check if cursor at begin of row
	          je          begin ; if yes,jmp to check y
	          jne         ordinary ;if not,decrease xpos only

	begin:    cmp         YCursorSender, 0 ;check if cursor at 0,0
	          je          ptspc ; if yes,put space only

	decline:  
	          dec         YCursorSender ;if x at 0 and y not,decrease line and mov x to end of new row
	          mov         XCursorSender, 27h
	          jmp         ptspc
	
	ordinary: dec         XCursorSender
	        
	
	ptspc:    
	          setCursor   XCursorSender, YCursorSender ;put cursor at right position now
	          mov         ah, 2                  	; printing the space
	          mov         dl, ' ' ;print empty space instead of current char
	          int         21h
	          jmp         SendMode  ;jmp to send this value 



	
	enter:    
	          cmp         YCursorSender,11;check if cursor at the end of your half
	          JZ          NewLineWithScroll ;if yes,jmp to scroll
	          jnz         NewLine
	NewLineWithScroll:       
	          scrollUpper
	          mov         XCursorSender,0
	          mov         YCursorSender,0bh
	          setCursor   XCursorSender,YCursorSender
	          mov         ah, 2                  	; printing the char
	          mov         dl, VALUE
	          int         21h
	          jmp         SendMode ;jmp to send this value 

	NewLine:       
	          inc         YCursorSender ;mov cursor to new row
	          mov         XCursorSender,0 ;put cursor at the beginning of the row
	          setCursor   XCursorSender, YCursorSender
	          mov         ah, 2                  	; printing the char
	          mov         dl, VALUE
	          int         21h
	          jmp         SendMode ;jmp to send this value 
	
	key:      
	          setCursor   XCursorSender, YCursorSender
	          mov         ah, 2                  	; printing the char
	          mov         dl, VALUE
	          int         21h
	
	          add         XCursorSender, 1 ;mov cusor to right
              
	          cmp         XCursorSender, 40 ;check if cursor at the end of the row
	          jne         SendMode ;jmp to send this value 
	          add         YCursorSender, 1 ;mov to new line
	          mov         XCursorSender, 0 
	          cmp         YCursorSender, 0ch ;check if at the end of your half
             
	          jne         SendMode
	          scrollUpper ;scroll if yes
	          mov         XCursorSender,0
	          mov         YCursorSender,0bh
	          setCursor   XCursorSender,YCursorSender	    
	
	
	SendMode:    
	          mov         dx, 3fdh

	          in          al, dx
	          test        al, 00100000b
	          jz          RecieveMode ;if busy , jmp to receive mode
	          mov         dx, 3f8h ;sending value
	          mov         al, VALUE
	          out         dx, al
	          jmp         input ;jmp to check if there's another input
	
	
	RecieveMode:      
	          mov         ah,1                   	;check if there is key pressed 
	          int         16h
	          jnz         read                      ; if key pressed , jmp to be sender

	          mov         dx , 3FDH              	; Line Status Register
	          in          al , dx
	          test        al , 1
	          JZ          RecieveMode


	          mov         dx , 03F8H
	          in          al , dx
	          mov         VALUE,al ;Recieving value

	          setCursor   XCursorReciever,yCursorReciever 


			; make same checks as send mode
	          CMP         VALUE,0Dh              	;check if the key is enter
	          JZ          newlineR

	          cmp         VALUE, 08h
	          je          bcsR

			  cmp VALUE,27
			  JE CLOSE
			  JNE CONTR            

	bcsR:     
	          cmp         XCursorReciever, 0
	          je          beginR
	          jne         ordinaryR

	beginR:   cmp         yCursorReciever, 0dh
	          je          ptspcR
	declineR: 
	          dec         yCursorReciever
	          mov         XCursorReciever, 27h
	          jmp         ptspcR
	
	ordinaryR:dec         XCursorReciever
	        
	
	ptspcR:   
	;mov         VALUE, ' '
	          setCursor   XCursorReciever, yCursorReciever
	          mov         ah, 2                  	; printing the char
	          mov         dl, ' '
	          int         21h
	          jmp         input

	newlineR: 
	          cmp         yCursorReciever,24
	          JZ          XR
	          jnz         YR
	XR:       
	          scrollLower
	          mov         XCursorReciever,0
	          mov         yCursorReciever,24
	          setCursor   XCursorReciever,yCursorReciever
	          jmp         printR

	YR:       
	          inc         yCursorReciever
	          mov         XCursorReciever,0

	contR:    
	          CMP         XCursorReciever,79
	          JZ          checkYR
	          jnz         printR

	checkYR:  cmp         yCursorReciever,24
	          jnz         printR
	          scrollLower
	          mov         XCursorReciever,0
	          mov         yCursorReciever,24
	          setCursor   XCursorReciever,yCursorReciever
	printR:   
	          setCursor   XCursorReciever,yCursorReciever

	          mov         ah,2
	          mov         dl,VALUE
	          int         21h

	          setCursorReciever
	          jmp         input
	
	
	
	CLOSE:
	MOV VALUE,00
	JMP ChoosingMenu
	
	
	chat endp