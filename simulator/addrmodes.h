uint8_t fetch(uint8_t step) { // 1 cycle
    switch (step){
        case    0:  C1.STEP_clr = 1 ; C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    1:  C2.INST_s.toggle() ; break ;
        case    2:  C2.INST_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    3:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t imp(uint8_t step) { //implied
    switch (step){
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t acc(uint8_t step) { // 1 cycle
    switch (step){
        case    0:  C1.ACC_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; break ;
        case    3:  C1.ACC_e.toggle() ; break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t imm(uint8_t step) { // 1 cycle
    switch (step){
        case    0:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    3:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ;  break ;
        default:    return 0 ;
    }
    return 1 ;
}


uint8_t zp(uint8_t step) { // 3 cycles
    switch (step){
        case    0:  break ;
        case    1:  C4.EAh_s.toggle() ; break ;
        case    2:  C4.EAh_s.toggle() ; break ;
        case    3:  break ;

        case    4:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    5:  C4.EAl_s.toggle() ; break ;
        case    6:  C4.EAl_s.toggle() ; break ;
        case    7:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; break ;

        case    8:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    9:  C3.B_s.toggle() ; break ;
        case   10:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case   11:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; C2.PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpx(uint8_t step) { // 5 cycles
    switch (step){
        case    0:  break ;
        case    1:  C4.EAh_s.toggle() ; break ; 
        case    2:  C4.EAh_s.toggle() ; break ;
        case    3:  break ;

        case    4:  C1.X_e.toggle() ; break ; 
        case    5:  C3.A_s.toggle() ; break ;
        case    6:  C3.A_s.toggle() ; break ;
        case    7:  C1.X_e.toggle() ; break ;
    
        case    8:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    9:  C3.B_s.toggle() ; break ;
        case   10:  C3.B_s.toggle() ; break ;
        case   11:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; break ;
    
        case   12:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; break ;
        case   13:  C4.EAl_s.toggle() ; break ;
        case   14:  C4.EAl_s.toggle() ; break ;
        case   15:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
    
        case   16:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ; 
        case   17:  C3.B_s.toggle() ; break ;
        case   18:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case   19:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; C2.PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t zpy(uint8_t step) { // 5 cycles
    switch (step){
        case    0:  break ;
        case    1:  C4.EAh_s.toggle() ; break ; 
        case    2:  C4.EAh_s.toggle() ; break ;
        case    3:  break ;

        case    4:  C1.Y_e.toggle() ; break ; 
        case    5:  C3.A_s.toggle() ; break ;
        case    6:  C3.A_s.toggle() ; break ;
        case    7:  C1.Y_e.toggle() ; break ;
    
        case    8:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    9:  C3.B_s.toggle() ; break ;
        case   10:  C3.B_s.toggle() ; break ;
        case   11:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; break ;
    
        case   12:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; break ;
        case   13:  C4.EAl_s.toggle() ; break ;
        case   14:  C4.EAl_s.toggle() ; break ;
        case   15:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
    
        case   16:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ; 
        case   17:  C3.B_s.toggle() ; break ;
        case   18:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case   19:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; C2.PC_up.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t rel(uint8_t step){ // 7 cycles
    switch (step){
        case    0:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; C3.B_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    3:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;

        case    4:  C3.ALU_op = ALU_SXT ; 
                    C3.ALU_e.toggle() ; break ;
        case    5:  C4.EAh_s.toggle() ; break ;
        case    6:  C4.EAh_s.toggle() ; break ;
        case    7:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
    
        case    8:  C2.PC_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case    9:  C3.B_s.toggle() ; break ;
        case   10:  C3.B_s.toggle() ; break ;
        case   11:  C4.Al2D_e.toggle() ; C2.PC_e.toggle() ; break ;
    
        case   12:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case   13:  C4.EAl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   14:  C4.EAl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   15:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
    
        case   16:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
        case   17:  C3.A_s.toggle() ; break ;
        case   18:  C3.A_s.toggle() ; break ;
        case   19:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;
    
        case   20:  C2.PC_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
        case   21:  C3.B_s.toggle() ; break ;
        case   22:  C3.B_s.toggle() ; break ;
        case   23:  C4.Ah2D_e.toggle() ; C2.PC_e.toggle() ; break ;
    
        case   24:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; break ;
        case   25:  C4.EAh_s.toggle() ; break ;
        case   26:  C4.EAh_s.toggle() ; break ;
        case   27:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t abso(uint8_t step) { // 3 cycles
    switch(step) {
        case    0:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ; 
        case    1:  C4.EAl_s.toggle() ; break ; 
        case    2:  C4.EAl_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    3:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case    4:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    5:  C4.EAh_s.toggle() ; break ;
        case    6:  C4.EAh_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    7:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;

        case    8:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    9:  C3.B_s.toggle() ; break ;
        case   10:  C3.B_s.toggle() ; break ;
        case   11:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absx(uint8_t step) { // 7 cycles
    switch(step) {
        case    0:  C1.X_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; break ;
        case    3:  C1.X_e.toggle() ; break ;
        
        case    4:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    5:  C3.B_s.toggle() ; break ;
        case    6:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    7:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case    8:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case    9:  C4.EAl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   10:  C4.EAl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   11:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        
        case   12:  break ;
        case   13:  C3.A_s.toggle() ; break ;
        case   14:  C3.A_s.toggle() ; break ;
        case   15:  break ;

        case   16:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ; 
        case   17:  C3.B_s.toggle() ; break ;
        case   18:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case   19:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case   20:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; break ;
        case   21:  C4.EAh_s.toggle() ; break ;
        case   22:  C4.EAh_s.toggle() ; break ;
        case   23:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case   24:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   25:  C3.B_s.toggle() ; break ;
        case   26:  C3.B_s.toggle() ; break ;
        case   27:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t absy(uint8_t step) { // 7 cycles
    switch(step) {
        case    0:  C1.Y_e.toggle() ; break ;
        case    1:  C3.A_s.toggle() ; break ;
        case    2:  C3.A_s.toggle() ; break ;
        case    3:  C1.Y_e.toggle() ; break ;
        
        case    4:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    5:  C3.B_s.toggle() ; break ;
        case    6:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    7:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case    8:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case    9:  C4.EAl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   10:  C4.EAl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   11:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        
        case   12:  break ;
        case   13:  C3.A_s.toggle() ; break ;
        case   14:  C3.A_s.toggle() ; break ;
        case   15:  break ;

        case   16:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ; 
        case   17:  C3.B_s.toggle() ; break ;
        case   18:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case   19:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case   20:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; break ;
        case   21:  C4.EAh_s.toggle() ; break ;
        case   22:  C4.EAh_s.toggle() ; break ;
        case   23:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case   24:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   25:  C3.B_s.toggle() ; break ;
        case   26:  C3.B_s.toggle() ; break ;
        case   27:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t ind(uint8_t step) { // 8 cycles
    switch(step) {
        case    0:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    1:  C4.EAl_s.toggle() ; C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; C4.EAl_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    3:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ; 
        
        case    4:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    5:  C4.EAh_s.toggle() ; break ;
        case    6:  C4.EAh_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    7:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case    8:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    9:  C3.A_s.toggle() ; break ;
        case   10:  C3.A_s.toggle() ; break ;
        case   11:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ;break ;
        
        case   12:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case   13:  C4.EAl_s.toggle() ; break ;
        case   14:  C4.EAl_s.toggle() ; break ;
        case   15:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case   16:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   17:  C3.B_s.toggle() ; break ;
        case   18:  C3.B_s.toggle() ; break ;
        case   19:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;
        
        case   20:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; break ;
        case   21:  C4.EAh_s.toggle() ; break ;
        case   22:  C4.EAh_s.toggle() ; break ;
        case   23:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;
        
        case   24:  break ;
        case   25:  C3.B_s.toggle() ; break ;
        case   26:  C3.B_s.toggle() ; break ; 
        case   27:  break ;

        case   28:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; break ;
        case   29:  C4.EAl_s.toggle() ; break ;
        case   30:  C4.EAl_s.toggle() ; break ;
        case   31:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indx(uint8_t step) { // 10 cycles
    switch(step) {
        case    0:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    3:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case    4:  C1.X_e.toggle() ; break ;
        case    5:  C3.A_s.toggle() ; break ;
        case    6:  C3.A_s.toggle() ; break ;
        case    7:  C1.X_e.toggle() ; break ;

        case    8:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; break ;
        case    9:  C4.EAl_s.toggle() ; break ;
        case   10:  C4.EAl_s.toggle() ; break ;
        case   11:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case   12:  C4.EAl_e.toggle() ; C4.Al2D_e.toggle() ; break ;
        case   13:  C3.B_s.toggle() ; break ;
        case   14:  C3.B_s.toggle() ; break ;
        case   15:  C4.Al2D_e.toggle() ; C4.EAl_e.toggle() ; break ;

        case   16:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case   17:  C4.EAl_s.toggle() ; break ;
        case   18:  C4.EAl_s.toggle() ; break ;
        case   19:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case   20:  C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   21:  C4.EAh_s.toggle() ; break ;
        case   22:  C4.EAh_s.toggle() ; break ;
        case   23:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; break ;
        
        case   24:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; break ;
        case   25:  C4.EAl_s.toggle() ; break ;
        case   26:  C4.EAl_s.toggle() ; break ;
        case   27:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case   28:  C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   29:  C3.B_s.toggle() ; break ;
        case   30:  C3.B_s.toggle() ; break ;
        case   31:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; break ;
        
        case   32:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; break ;
        case   33:  C4.EAl_s.toggle() ; break ;
        case   34:  C4.EAl_s.toggle() ; break ;
        case   35:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case   36:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   37:  C3.B_s.toggle() ; break ;
        case   38:  C3.B_s.toggle() ; break ;
        case   39:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}


uint8_t indy(uint8_t step) { // 10 cycles
    switch(step) {
        case    0:  C2.PC_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case    1:  C3.B_s.toggle() ; break ;
        case    2:  C3.B_s.toggle() ; C2.PC_up.toggle() ; break ;
        case    3:  C2.RAM_e.toggle() ; C2.PC_e.toggle() ; C2.PC_up.toggle() ; break ;
        
        case    4:  C1.Y_e.toggle() ; break ;
        case    5:  C3.A_s.toggle() ; break ;
        case    6:  C3.A_s.toggle() ; break ;
        case    7:  C1.Y_e.toggle() ; break ;

        case    8:  C3.ALU_op = ALU_INC ; 
                    C3.ALU_e.toggle() ; break ;
        case    9:  C4.EAl_s.toggle() ; break ;
        case   10:  C4.EAl_s.toggle() ; break ;
        case   11:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case   12:  C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   13:  C4.EAh_s.toggle() ; break ;
        case   14:  C4.EAh_s.toggle() ; break ;
        case   15:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; break ;

        case   16:  C3.ALU_op = ALU_PASS ; 
                    C3.ALU_e.toggle() ; break ;
        case   17:  C4.EAl_s.toggle() ; break ;
        case   18:  C4.EAl_s.toggle() ; break ;
        case   19:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ; 
        
        case   20:  C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   21:  C3.B_s.toggle() ; break ;
        case   22:  C3.B_s.toggle() ; break ;
        case   23:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; break ;
        
        case   24:  C3.ALU_op = ALU_ADD ; 
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        case   25:  C4.EAl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   26:  C4.EAl_s.toggle() ; C5.ST_s.toggle() ; break ;
        case   27:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; C5.ST_ALU_C_s.toggle() ; break ;
        
        case   28:  break ;
        case   29:  C3.A_s.toggle() ; break ;
        case   30:  C3.A_s.toggle() ; break ;
        case   31:  break ;
        
        case   32:  C4.EAh_e.toggle() ; C4.Ah2D_e.toggle() ; break ;
        case   33:  C3.B_s.toggle() ; break ;
        case   34:  C3.B_s.toggle() ; break ;
        case   35:  C4.Ah2D_e.toggle() ; C4.EAh_e.toggle() ; break ;

        case   36:  C3.ALU_op = ALU_ADC ; 
                    C3.ALU_e.toggle() ; break ;
        case   37:  C4.EAh_s.toggle() ; break ;
        case   38:  C4.EAh_s.toggle() ; break ;
        case   39:  C3.ALU_op = 0 ;
                    C3.ALU_e.toggle() ; break ;

        case   40:  C4.EAh_e.toggle() ; C4.EAl_e.toggle() ; C2.RAM_e.toggle() ; break ;
        case   41:  C3.B_s.toggle() ; break ;
        case   42:  C3.B_s.toggle() ; break ;
        case   43:  C2.RAM_e.toggle() ; C4.EAl_e.toggle() ; C4.EAh_e.toggle() ; break ;

        default:    return 0 ;
    } 
    return 1 ;
}