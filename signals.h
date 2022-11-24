#include "microcode.h"

class CONTROL_UNIT {
    private:
        uint64_t _default ;
        uint64_t _prev_cw ;

    public:
        // 1
        output<1> X_s, X_e, Y_s, Y_e, ACC_s, ACC_e ;
        // 2
        output<1> SP_down, SP_s, SP_e, EAl_s, EAl_e, PC_up, PCl_s, PC_e ;
        // 3
        output<4> ALU_op ; 
        output<1> A_s, ALU_e, B_s ;
        // 4
        output<1> Ah2D_e, INST_s, RAM_s, RAM_e, Al2D_e, EAh_s, EAh_e, PCh_s ;
        // 5
        output<1> ST_e, ST_src, ST_NZ_s, ST_V_s, ST_C_s, ST_ALU_C_s, ST_ALU_C_from_C, ST_s ;

    CONTROL_UNIT() :    X_e(1), Y_e(1), ACC_e(1), 
                        SP_down(1), SP_e(1), EAl_e(1), PC_up(1), PC_e(1), 
                        ALU_e(1),
                        Ah2D_e(1), RAM_e(1), Al2D_e(1), EAh_e(1),
                        ST_e(1){

        _default = make_cw() ;
        _prev_cw = _default ;
    }

    uint64_t get_default_cw(){
        return _default ; 
    }

    uint64_t get_cw(uint8_t inst, uint8_t flags, uint8_t step, uint8_t phase){
        return microcode[inst << 10 | flags << 6 | step << 2 | phase] ;
    }

    void apply_cw(uint64_t cw){
        uint64_t prev = make_cw() ;

        #define set_signal_1(output, bit) if (((cw >> bit) & 0x1) != ((prev >> bit) & 0x1)){ output = cw >> bit ; }
        #define set_signal_4(output, bit) if (((cw >> bit) & 0xF) != ((prev >> bit) & 0xF)){ output = cw >> bit ; }

        set_signal_1(X_s, 0) ;
        set_signal_1(X_e, 1) ;
        set_signal_1(Y_s, 2) ;
        set_signal_1(Y_e, 3) ;
        set_signal_1(ACC_s, 4) ;
        set_signal_1(ACC_e, 5) ;
        // 6
        // 7
        // Chip 2
        set_signal_1(SP_down, 8) ;
        set_signal_1(SP_s, 9) ;
        set_signal_1(SP_e, 10) ;
        set_signal_1(EAl_s, 11) ;
        set_signal_1(EAl_e, 12) ;
        set_signal_1(PC_up, 13) ;
        set_signal_1(PCl_s, 14) ;
        set_signal_1(PC_e , 15) ;
        // Chip 3
        set_signal_4(ALU_op, 16) ; 
        set_signal_1(A_s, 20) ;
        set_signal_1(ALU_e, 21) ; 
        set_signal_1(B_s, 22) ;
        // 23
        // Chip 4
        set_signal_1(Ah2D_e, 24) ;
        set_signal_1(INST_s, 25) ;
        set_signal_1(RAM_s, 26) ;
        set_signal_1(RAM_e, 27) ;
        set_signal_1(Al2D_e, 28) ;
        set_signal_1(EAh_s, 29) ;
        set_signal_1(EAh_e, 30) ;
        set_signal_1(PCh_s, 31) ;
        // Chip 5
        set_signal_1(ST_e, 32) ;
        set_signal_1(ST_src, 33) ;
        set_signal_1(ST_NZ_s, 34) ;
        set_signal_1(ST_V_s, 35) ;
        set_signal_1(ST_C_s, 36) ;
        set_signal_1(ST_ALU_C_s, 37) ;
        set_signal_1(ST_ALU_C_from_C, 38) ;
        set_signal_1(ST_s, 39) ;
    }

    uint64_t make_cw(){
        return 
            // Chip 1
            X_s << 0 |
            X_e << 1 |
            Y_s << 2 |
            Y_e << 3 |
            ACC_s << 4 |
            ACC_e << 5 |
            // 6
            // 7
            // Chip 2
            SP_down << 8 |
            SP_s << 9 |
            SP_e << 10 |
            EAl_s << 11 |
            EAl_e << 12 |
            PC_up << 13 |
            PCl_s << 14 |
            PC_e  << 15 |
            // Chip 3
            ALU_op << 16 | 
            A_s << 20 |
            ALU_e << 21 | 
            B_s << 22 |
            // 23
            // Chip 4
            Ah2D_e << 24 |
            INST_s << 25 |
            RAM_s << 26 |
            RAM_e << 27 |
            Al2D_e << 28 |
            EAh_s << 29 |
            EAh_e << 30 |
            PCh_s << 31 |
            // Chip 5
            (uint64_t)ST_e << 32 |
            (uint64_t)ST_src << 33 |
            (uint64_t)ST_NZ_s << 34 |
            (uint64_t)ST_V_s << 35 |
            (uint64_t)ST_C_s << 36 |
            (uint64_t)ST_ALU_C_s << 37 |
            (uint64_t)ST_ALU_C_from_C << 38 |
            (uint64_t)ST_s << 39 ;
    }
} ;