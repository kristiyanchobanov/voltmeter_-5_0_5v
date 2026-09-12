#ifndef DISPLAYBUFFER_H
#define DISPLAYBUFFER_H

#include <Arduino.h>

#define bit_mask_seg_dp 0b00000001
#define bit_mask_seg_a  0b00000010
#define bit_mask_seg_b  0b00000100
#define bit_mask_seg_c  0b00001000
#define bit_mask_seg_d  0b00010000
#define bit_mask_seg_e  0b00100000
#define bit_mask_seg_f  0b01000000
#define bit_mask_seg_g  0b10000000

#define DISPLAY_BLANK 10
#define DISPLAY_MINUS 11

// Буфер за четирите разряда на дисплея.
// Всеки елемент съдържа информация кои сегменти трябва да светят.
extern unsigned char DisplayBuff[4];



// Преобразува число 0..9999 в данни за четирите разряда.
bool DisplayBufferPrint(int input, unsigned char dp_position);

// Преобразува цифра 0..9 в код за сегментите.
//unsigned char get_digit_segments(unsigned char digit1);


#endif
