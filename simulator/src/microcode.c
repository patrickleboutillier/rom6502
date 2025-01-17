#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "STATUS.h"
#include "CTRL_OUT.h"
#include "CONTROL_ROMS.h"
#include "ALU.h"
#include "inst.h"

CONTROL_1_ROM C1 ;
CONTROL_2_ROM C2 ;
CONTROL_3_ROM C3 ;
CONTROL_4_ROM C4 ;
CONTROL_5_ROM C5 ;
CONTROL_UNIT CU(&C1, &C2, &C3, &C4, &C5) ;

output<1> ctrl_PC_e(1) ;
output<3> ctrl_out_cmd ;
CTRL_OUT CTRL_OUT(&ctrl_out_cmd) ;

STATUS STATUS ;
uint8_t INST ;

#include "addrmodes.h"
#include "ops.h"


static uint8_t (*addrtable[256])(uint8_t tick) = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |    */
/* 0 */     imp, indx,  imp, imp,    zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, imp, /* 0 */
/* 1 */     rel, indy,  imp, imp,   imp,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, imp, /* 1 */
/* 2 */    abso, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, imp, /* 2 */
/* 3 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, imp, /* 3 */
/* 4 */     imp, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, imp, /* 4 */
/* 5 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, imp, /* 5 */
/* 6 */     imp, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm,  ind, abso, abso, imp, /* 6 */
/* 7 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, imp, /* 7 */
/* 8 */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, imp, /* 8 */
/* 9 */     rel, indy,  imp, indy,  zpx,  zpx,  zpy,  zpy,  imp, absy,  imp, absy, absx, absx, absy, imp, /* 9 */
/* A */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, imp, /* A */
/* B */     rel, indy,  imp, indy,  zpx,  zpx,  zpy,  zpy,  imp, absy,  imp, absy, absx, absx, absy, imp, /* B */
/* C */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, imp, /* C */
/* D */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, imp, /* D */
/* E */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, imp, /* E */
/* F */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp,  imp, absx, absx, absx, imp  /* F */
} ;

static uint8_t (*optable[256])(uint8_t tick) = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |       */
/* 0 */      brk,  ora,  nop,  nop,  nop,  ora,  asl,  nop,  php,  ora,  asl,  nop,  nop,  ora,  asl,  pc,   /* 0 */
/* 1 */      bpl,  ora,  nop,  nop,  nop,  ora,  asl,  nop,  clc,  ora,  nop,  nop,  nop,  ora,  asl,  mon,  /* 1 */
/* 2 */      jsr,  and_, nop,  nop,  bit_, and_, rol,  nop,  plp,  and_, rol,  nop,  bit_, and_, rol,  rst1, /* 2 */
/* 3 */      bmi,  and_, nop,  nop,  nop,  and_, rol,  nop,  sec,  and_, nop,  nop,  nop,  and_, rol,  rst2, /* 3 */
/* 4 */      rti,  eor,  nop,  nop,  nop,  eor,  lsr,  nop,  pha,  eor,  lsr,  nop,  jmp,  eor,  lsr,  nop,  /* 4 */
/* 5 */      bvc,  eor,  nop,  nop,  nop,  eor,  lsr,  nop,  cli_, eor,  nop,  nop,  nop,  eor,  lsr,  nop,  /* 5 */
/* 6 */      rts,  adc,  nop,  nop,  nop,  adc,  ror,  nop,  pla,  adc,  ror,  nop,  jmp,  adc,  ror,  nop,  /* 6 */
/* 7 */      bvs,  adc,  nop,  nop,  nop,  adc,  ror,  nop,  sei_, adc,  nop,  nop,  nop,  adc,  ror,  nop,  /* 7 */
/* 8 */      nop,  sta,  nop,  nop,  sty,  sta,  stx,  nop,  dey,  nop,  txa,  nop,  sty,  sta,  stx,  nop,  /* 8 */
/* 9 */      bcc,  sta,  nop,  nop,  sty,  sta,  stx,  nop,  tya,  sta,  txs,  nop,  nop,  sta,  nop,  nop,  /* 9 */
/* A */      ldy,  lda,  ldx,  nop,  ldy,  lda,  ldx,  nop,  tay,  lda,  tax,  nop,  ldy,  lda,  ldx,  nop,  /* A */
/* B */      bcs,  lda,  nop,  nop,  ldy,  lda,  ldx,  nop,  clv,  lda,  tsx,  nop,  ldy,  lda,  ldx,  nop,  /* B */
/* C */      cpy,  cmp,  nop,  nop,  cpy,  cmp,  dec,  nop,  iny,  cmp,  dex,  nop,  cpy,  cmp,  dec,  nop,  /* C */
/* D */      bne,  cmp,  nop,  nop,  nop,  cmp,  dec,  nop,  cld,  cmp,  nop,  nop,  nop,  cmp,  dec,  nop,  /* D */
/* E */      cpx,  sbc,  nop,  nop,  cpx,  sbc,  inc,  nop,  inx,  sbc,  nop,  sbc,  cpx,  sbc,  inc,  nop,  /* E */
/* F */      beq,  sbc,  nop,  nop,  nop,  sbc,  inc,  nop,  sed,  sbc,  nop,  nmi,  nop,  sbc,  inc,  irq   /* F */
} ;


FILE *rom1, *rom2, *rom3, *rom4, *rom5 ;

void write_mc(uint8_t inst, uint8_t flags, uint8_t step, uint64_t cw){
    printf("  /* INST:0x%02X FLAGS:0x%X STEP:%2d */ 0x%010lX,\n", inst, flags, step, cw) ;
    uint8_t data = (cw >> 0) & 0xFF ;
    fwrite(&data, 1, 1, rom1) ;
    data = (cw >> 8) & 0xFF ;
    fwrite(&data, 1, 1, rom2) ;
    data = (cw >> 16) & 0xFF ;
    fwrite(&data, 1, 1, rom3) ;
    data = (cw >> 24) & 0xFF ;
    fwrite(&data, 1, 1, rom4) ;
    data = (cw >> 32) & 0xFF ;
    fwrite(&data, 1, 1, rom5) ;
}


void generate_microcode(){
    CTRL_OUT.PC_up.connect(C2.n) ;
    ctrl_PC_e.connect(C2.v) ;
    CTRL_OUT.INST_s.connect(C2.z) ;
    CTRL_OUT.RAM_s.connect(C2.c) ;

    assert(CU.make_cw() == CU.get_default_cw()) ;
    
    printf("uint64_t microcode[] = {\n") ;
    for (uint16_t i = 0 ; i < 4096 ; i++){
        uint8_t flags = i & 0b1111 ;
        uint8_t inst = i >> 4 ;
        
        // Set INST and FLAGS       
        INST = inst ;
        STATUS.N = (flags >> 3) & 1 ;
        STATUS.V = (flags >> 2) & 1 ;
        STATUS.Z = (flags >> 1) & 1 ;
        STATUS.C = (flags >> 0) & 1 ;
        CTRL_OUT.PC_up = (flags >> 3) & 1 ;
        ctrl_PC_e = (flags >> 2) & 1 ;
        CTRL_OUT.INST_s = (flags >> 1) & 1 ;
        CTRL_OUT.RAM_s = (flags >> 0) & 1 ;

        uint8_t addr_start = 0, op_start = 0 ;
        bool fetch_done = false, addr_done = false ;
        for (int step = 0 ; step < 64 ; step++){
            assert(INST == inst) ;
            assert(STATUS.N == ((flags >> 3) & 1)) ;
            assert(STATUS.V == ((flags >> 2) & 1)) ;
            assert(STATUS.Z == ((flags >> 1) & 1)) ;
            assert(STATUS.C == ((flags >> 0) & 1)) ;
            assert(CTRL_OUT.PC_up == ((flags >> 3) & 1)) ;
            assert(ctrl_PC_e == ((flags >> 2) & 1)) ;
            assert(CTRL_OUT.INST_s == ((flags >> 1) & 1)) ;
            assert(CTRL_OUT.RAM_s == ((flags >> 0) & 1)) ;

            if (! fetch_done){
                if (fetch(step)){
                    write_mc(inst, flags, step, CU.make_cw()) ;
                    continue ;
                } 
                fetch_done = true ;
                addr_start = step ;
            }
            if (! addr_done){
                if ((*addrtable[inst])(step - addr_start)){
                    write_mc(inst, flags, step, CU.make_cw()) ;
                    continue ;
                }
                addr_done = true ;
                op_start = step ;
            }
            
            uint8_t more = (*optable[inst])(step - op_start) ;
            write_mc(inst, flags, step, (more ? CU.make_cw() : CU.get_default_cw())) ;
        }
    }
    printf("} ;\n") ;
}


int main(int argc, char *argv[]){
    rom1 = fopen("CONTROL_1_ROM.bin","wb") ;
    rom2 = fopen("CONTROL_2_ROM.bin","wb") ;
    rom3 = fopen("CONTROL_3_ROM.bin","wb") ;
    rom4 = fopen("CONTROL_4_ROM.bin","wb") ;
    rom5 = fopen("CONTROL_5_ROM.bin","wb") ;
 
    generate_microcode() ;
}