#ifndef BIT_CALC_H
#define BIT_CALC_H

#define Set_Bit(var,Bit_Num) var|=(1<<Bit_Num)

#define Clear_Bit(var,Bit_Num) var&=~(1<<Bit_Num)

#define Toggle_Bit(var,Bit_Num) var ^= (1 << Bit_Num)

#define Get_Bit(var,Bit_Num) ((var>>Bit_Num)&1)


#endif

