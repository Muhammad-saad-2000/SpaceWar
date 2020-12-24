ROTATE_PLAYER1_ANTICLOCK MACRO 
    LOCAL DONT_ADD_ONE, ENDD

    CMP first_player_direction, DOWN
    JZ  DONT_ADD_ONE
    INC first_player_direction
    JMP ENDD

    DONT_ADD_ONE:
    MOV first_player_direction, LOWER_RIGHT
    ENDD:
ENDM

ROTATE_PLAYER1_CLOCK MACRO
    LOCAL DONT_SUBTRACT_ONE, ENDD
    
    CMP first_player_direction, LOWER_RIGHT
    JZ  DONT_SUBTRACT_ONE
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
    JZ  DONT_ADD_ONE
    INC second_player_direction
    JMP ENDD

    DONT_ADD_ONE:
    MOV second_player_direction, LOWER_RIGHT
    ENDD:
ENDM

ROTATE_PLAYER2_CLOCK MACRO
    LOCAL DONT_SUBTRACT_ONE, ENDD
    
    CMP second_player_direction, LOWER_RIGHT
    JZ  DONT_SUBTRACT_ONE
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
    LOCAL FIRST_PLAYER_THRUST__ , SECOND_PLAYER_THRUST__

    FIRST_PLAYER_THRUST__:
    CMP first_player_direction, RIGHT
    JZ  R_P1
    CMP first_player_direction, UPPER_RIGHT
    JZ  UR_P1
    CMP first_player_direction, LOWER_RIGHT
    JZ  LR_P1
    CMP first_player_direction, LEFT
    JZ  L_P1
    CMP first_player_direction, UPPER_LEFT
    JZ  UL_P1
    CMP first_player_direction, LOWER_LEFT
    JZ  LL_P1 
    CMP first_player_direction, UP 
    JZ  U_P1
    CMP first_player_direction, DOWN
    JZ  D_P1

    SECOND_PLAYER_THRUST__:
    CMP second_player_direction, RIGHT
    JZ  R_P2
    CMP second_player_direction, UPPER_RIGHT
    JZ  UR_P2
    CMP second_player_direction, LOWER_RIGHT
    JZ  LR_P2
    CMP second_player_direction, LEFT
    JZ  L_P2
    CMP second_player_direction, UPPER_LEFT
    JZ  UL_P2
    CMP second_player_direction, LOWER_LEFT
    JZ  LL_P2
    CMP second_player_direction, UP 
    JZ  U_P2
    CMP second_player_direction, DOWN
    JZ  D_P2

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
FIRE_P1 MACRO
    QQ:CMP LAUNCHED_P1,01
    JE cm1
    JNE REND
    cm1:
        cmp FIRED_P1_DIREC,0
        je cm11
        jne cm2
    
    cm2:
        cmp FIRED_P1_DIREC,1
        je cm22
        jne cm3
    
    cm3:
        cmp FIRED_P1_DIREC,2
        je cm33
        jne cm4
    cm4:
        cmp FIRED_P1_DIREC,3
        je cm44
        jne cm5

    cm5:
        cmp FIRED_P1_DIREC,4
        je cm55
        jne cm6

    cm6:
        cmp FIRED_P1_DIREC,0fdh
        je cm66
        jne cm7
   
    cm7:
        cmp FIRED_P1_DIREC,0feh
        je cm77
        jne cm8
    
    cm8:
        cmp FIRED_P1_DIREC,0ffh
        je cm88
        mov LAUNCHED_P1,00
        jne REND

    cm11:
        cmp FIRED_P1_POSY,0
        jg df1
        mov LAUNCHED_P1,00
        jle REND
    cm22:
        cmp FIRED_P1_POSY,0
        jg cm222
        mov LAUNCHED_P1,00
        jle REND
    cm33:
        cmp FIRED_P1_POSx,0
        jg df3
        mov LAUNCHED_P1,00
        jle REND
    cm44:
        cmp FIRED_P1_POSY,180
        jl cm444
        mov LAUNCHED_P1,00
        jge REND
    cm55:
        cmp FIRED_P1_POSY,180
        jl df5
        mov LAUNCHED_P1,00
        jge REND

    cm66:
        cmp FIRED_P1_POSY,180
        jl cm666
        mov LAUNCHED_P1,00
        jge REND

    cm77:
        cmp FIRED_P1_POSx,300
        jl df7
        mov LAUNCHED_P1,00
        jge REND    

    cm88:
         cmp FIRED_P1_POSy,0
        jg cm888
        mov LAUNCHED_P1,00
        jle REND 

    cm222:
        cmp FIRED_P1_POSx,0
        jg df2
        mov LAUNCHED_P1,00
        jle REND

     cm444:
        cmp FIRED_P1_POSx,0
        jg df4
        mov LAUNCHED_P1,00
        jle REND
     cm666:
        cmp FIRED_P1_POSx,300
        jl df6
        mov LAUNCHED_P1,00
        jge REND

    cm888:
        cmp FIRED_P1_POSx,300
        jl df8
        mov LAUNCHED_P1,00
        jge REND
        
    DF1:
        mov si,FIRED_P1_POSX;position x choise p1
        mov di,FIRED_P1_POSY;position y choise p1
        mov cl,FIRED_P1_DIREC;rotation choice p1
        mov bl,0;color choise
        call drawfire;drawing the ship 
        sub FIRED_P1_POSY,15 
        jmp REND
    DF2:
        mov si,FIRED_P1_POSX;position x choise p1
        mov di,FIRED_P1_POSY;position y choise p1
        mov cl,FIRED_P1_DIREC;rotation choice p1
        mov bl,0;color choise
        call drawfire;drawing the ship 
        sub FIRED_P1_POSY,15 
        sub FIRED_P1_POSX,15 
        JMP REND

    DF3:
        mov si,FIRED_P1_POSX;position x choise p1
        mov di,FIRED_P1_POSY;position y choise p1
        mov cl,FIRED_P1_DIREC;rotation choice p1
        mov bl,0;color choise
        call drawfire;drawing the ship 
        sub FIRED_P1_POSX,15 
        jmp REND

    DF4:
        mov si,FIRED_P1_POSX;position x choise p1
        mov di,FIRED_P1_POSY;position y choise p1
        mov cl,FIRED_P1_DIREC;rotation choice p1
        mov bl,0;color choise
        call drawfire;drawing the ship 
        add FIRED_P1_POSY,15 
        sub FIRED_P1_POSX,15 
        jmp REND
    DF5:
        mov si,FIRED_P1_POSX;position x choise p1
        mov di,FIRED_P1_POSY;position y choise p1
        mov cl,FIRED_P1_DIREC;rotation choice p1
        mov bl,0;color choise
        call drawfire;drawing the ship 
        add FIRED_P1_POSY,15 
        jmp REND

    DF6:
        mov si,FIRED_P1_POSX;position x choise p1
        mov di,FIRED_P1_POSY;position y choise p1
        mov cl,FIRED_P1_DIREC;rotation choice p1
        mov bl,0;color choise
        call drawfire;drawing the ship 
        add FIRED_P1_POSY,15 
        add FIRED_P1_POSx,15 
        jmp REND

    DF7:
        mov si,FIRED_P1_POSX;position x choise p1
        mov di,FIRED_P1_POSY;position y choise p1
        mov cl,FIRED_P1_DIREC;rotation choice p1
        mov bl,0;color choise
        call drawfire;drawing the ship 
        add FIRED_P1_POSx,15 
        jmp REND
    
    DF8:
        mov si,FIRED_P1_POSX;position x choise p1
        mov di,FIRED_P1_POSY;position y choise p1
        mov cl,FIRED_P1_DIREC;rotation choice p1
        mov bl,0;color choise
        call drawfire;drawing the ship 
        add FIRED_P1_POSx,15 
        sub FIRED_P1_POSY,15 

ENDM

FIRE_P2 MACRO
   CMP LAUNCHED_P2,01
    JE F1
    JNE QQ


    F1:
        cmp FIRED_P2_DIREC,0
        je F11
        jne F2
    
    F2:
        cmp FIRED_P2_DIREC,1
        je F22
        jne F3
    
    F3:
        cmp FIRED_P2_DIREC,2
        je F33
        jne F4
    F4:
        cmp FIRED_P2_DIREC,3
        je F44
        jne F5

    F5:
        cmp FIRED_P2_DIREC,4
        je F55
        jne F6

    F6:
        cmp FIRED_P2_DIREC,0fdh
        je F66
        jne F7
   
    F7:
        cmp FIRED_P2_DIREC,0feh
        je F77
        jne F8
    
    F8:
        cmp FIRED_P2_DIREC,0ffh
        je F88
        mov LAUNCHED_P2,00
        jne QQ

    F11:
        cmp FIRED_P2_POSY,0
        jg DFF1
        mov LAUNCHED_P2,00
        jle QQ
    F22:
        cmp FIRED_P2_POSY,0
        jg F222
        mov LAUNCHED_P2,00
        jle QQ
    F33:
        cmp FIRED_P2_POSx,0
        jg DFF3
        mov LAUNCHED_P2,00
        jle QQ
    F44:
        cmp FIRED_P2_POSY,180
        jl F444
        mov LAUNCHED_P2,00
        jge REND
    F55:
        cmp FIRED_P2_POSY,180
        jl DFF5
        mov LAUNCHED_P2,00
        jge QQ

    F66:
        cmp FIRED_P2_POSY,180
        jl F666
        mov LAUNCHED_P2,00
        jge QQ

    F77:
        cmp FIRED_P2_POSx,300
        jl DFF7
        mov LAUNCHED_P2,00
        jge QQ    

    F88:
         cmp FIRED_P2_POSy,0
        jg F888
        mov LAUNCHED_P2,00
        jle QQ 

    F222:
        cmp FIRED_P2_POSx,0
        jg DFF2
        mov LAUNCHED_P2,00
        jle QQ

     F444:
        cmp FIRED_P2_POSx,0
        jg DFF4
        mov LAUNCHED_P2,00
        jle QQ
     F666:
        cmp FIRED_P2_POSx,300
        jl DFF6
        mov LAUNCHED_P2,00
        jge QQ

    F888:
        cmp FIRED_P2_POSx,300
        jl DFF8
        mov LAUNCHED_P2,00
        jge QQ
        
    DFF1:
        mov si,FIRED_P2_POSX;position x choise P2
        mov di,FIRED_P2_POSY;position y choise P2
        mov cl,FIRED_P2_DIREC;rotation choice P2
        mov bl,0;color choise
        call drawfire;drawing the ship 
        sub FIRED_P2_POSY,15
        jmp QQ
    DFF2:
        mov si,FIRED_P2_POSX;position x choise P2
        mov di,FIRED_P2_POSY;position y choise P2
        mov cl,FIRED_P2_DIREC;rotation choice P2
        mov bl,0;color choise
        call drawfire;drawing the ship 
        sub FIRED_P2_POSY,15 
        sub FIRED_P2_POSX,15 
        JMP QQ

    DFF3:
        mov si,FIRED_P2_POSX;position x choise P2
        mov di,FIRED_P2_POSY;position y choise P2
        mov cl,FIRED_P2_DIREC;rotation choice P2
        mov bl,0;color choise
        call drawfire;drawing the ship 
        sub FIRED_P2_POSX,15 
        jmp QQ

    DFF4:
        mov si,FIRED_P2_POSX;position x choise P2
        mov di,FIRED_P2_POSY;position y choise P2
        mov cl,FIRED_P2_DIREC;rotation choice P2
        mov bl,0;color choise
        call drawfire;drawing the ship 
        add FIRED_P2_POSY,15 
        sub FIRED_P2_POSX,15 
        jmp QQ
    DFF5:
        mov si,FIRED_P2_POSX;position x choise P2
        mov di,FIRED_P2_POSY;position y choise P2
        mov cl,FIRED_P2_DIREC;rotation choice P2
        mov bl,0;color choise
        call drawfire;drawing the ship 
        add FIRED_P2_POSY,15 
        jmp QQ

    DFF6:
        mov si,FIRED_P2_POSX;position x choise P2
        mov di,FIRED_P2_POSY;position y choise P2
        mov cl,FIRED_P2_DIREC;rotation choice P2
        mov bl,0;color choise
        call drawfire;drawing the ship 
        add FIRED_P2_POSY,15 
        add FIRED_P2_POSx,15 
        jmp QQ

    DFF7:
        mov si,FIRED_P2_POSX;position x choise P2
        mov di,FIRED_P2_POSY;position y choise P2
        mov cl,FIRED_P2_DIREC;rotation choice P2
        mov bl,0;color choise
        call drawfire;drawing the ship 
        add FIRED_P2_POSx,15 
        jmp QQ
    
    DFF8:
        mov si,FIRED_P2_POSX;position x choise P2
        mov di,FIRED_P2_POSY;position y choise P2
        mov cl,FIRED_P2_DIREC;rotation choice P2
        mov bl,0;color choise
        call drawfire;drawing the ship 
        add FIRED_P2_POSx,15 
        sub FIRED_P2_POSY,15 


ENDM