#include "voltmeter_display.h"


unsigned char DisplayBuff[4];

unsigned char get_digit_segments(unsigned char digit1);


bool DisplayBufferPrint(int input, unsigned char dp_position)
{
  unsigned char TempBuff[4];
  bool negative = false;

  if ((input > 9999) || (input < -999) || (dp_position > 3))
  {
    return false;
  }

  if (input >= 0)
  {
    TempBuff[0] = input / 1000;
    TempBuff[1] = (input / 100) % 10;
    TempBuff[2] = (input / 10) % 10;
    TempBuff[3] = input % 10;

    switch (dp_position)
    {
      case 0:

        if (TempBuff[0] == 0)
          TempBuff[0] = 10;

        if ((TempBuff[1] == 0) && (TempBuff[0] == 10))
          TempBuff[1] = 10;

        if ((TempBuff[2] == 0) && (TempBuff[1] == 10) && (TempBuff[0] == 10))
          TempBuff[2] = 10;

        break;

      case 1:

        if (TempBuff[0] == 0)
        TempBuff[0] = 10;

        if (TempBuff[1] == 0 && TempBuff[0] == 10)
          TempBuff[1] = 10;

        break;

      case 2:

        if (TempBuff[0] == 0)
          TempBuff[0] = 10;

        break;

      case 3:

        break;
    }
  }
  else
  {
    negative = true;

    unsigned int value = -input;

    TempBuff[0] = DISPLAY_BLANK;
    TempBuff[1] = DISPLAY_BLANK;
    TempBuff[2] = DISPLAY_BLANK;
    TempBuff[3] = DISPLAY_BLANK;

    TempBuff[3] = value % 10;
    value = value / 10;

    if (value > 0)
    {
      TempBuff[2] = value % 10;
      value = value / 10;
    }

    if (value > 0)
    {
      TempBuff[1] = value % 10;
    }

    if (TempBuff[1] != DISPLAY_BLANK)
    {
      TempBuff[0] = DISPLAY_MINUS;
    }
    else if (TempBuff[2] != DISPLAY_BLANK)
    {
      TempBuff[1] = DISPLAY_MINUS;
    }
    else
    {
      TempBuff[2] = DISPLAY_MINUS;
    }
  }

  TempBuff[0] = get_digit_segments(TempBuff[0]);
  TempBuff[1] = get_digit_segments(TempBuff[1]);
  TempBuff[2] = get_digit_segments(TempBuff[2]);
  TempBuff[3] = get_digit_segments(TempBuff[3]);

  if (negative == false)
  {
    if (dp_position == 1)
    {
      TempBuff[2] |= bit_mask_seg_dp;
    }
    else if (dp_position == 2)
    {
      TempBuff[1] |= bit_mask_seg_dp;
    }
    else if (dp_position == 3)
    {
      TempBuff[0] |= bit_mask_seg_dp;
    }
  }
  else
  {
    if (dp_position == 1)
    {
      TempBuff[2] |= bit_mask_seg_dp;
    }
    else if (dp_position == 2)
    {
      TempBuff[1] |= bit_mask_seg_dp;
    }
  }

  DisplayBuff[0] = TempBuff[0];
  DisplayBuff[1] = TempBuff[1];
  DisplayBuff[2] = TempBuff[2];
  DisplayBuff[3] = TempBuff[3];

  return true;
}


unsigned char get_digit_segments(unsigned char digit1)
{
  unsigned char segments = 0;

  switch (digit1)
  {
    case 0:

      segments = bit_mask_seg_a |
                 bit_mask_seg_b |
                 bit_mask_seg_c |
                 bit_mask_seg_d |
                 bit_mask_seg_e |
                 bit_mask_seg_f;

      break;

    case 1:

      segments = bit_mask_seg_b |
                 bit_mask_seg_c;

      break;

    case 2:

      segments = bit_mask_seg_a |
                 bit_mask_seg_b |
                 bit_mask_seg_g |
                 bit_mask_seg_d |
                 bit_mask_seg_e;

      break;

    case 3:

      segments = bit_mask_seg_a |
                 bit_mask_seg_b |
                 bit_mask_seg_g |
                 bit_mask_seg_d |
                 bit_mask_seg_c;

      break;

    case 4:

      segments = bit_mask_seg_f |
                 bit_mask_seg_b |
                 bit_mask_seg_g |
                 bit_mask_seg_c;

      break;

    case 5:

      segments = bit_mask_seg_f |
                 bit_mask_seg_a |
                 bit_mask_seg_g |
                 bit_mask_seg_c |
                 bit_mask_seg_d;

      break;

    case 6:

      segments = bit_mask_seg_f |
                 bit_mask_seg_a |
                 bit_mask_seg_g |
                 bit_mask_seg_c |
                 bit_mask_seg_d |
                 bit_mask_seg_e;

      break;

    case 7:

      segments = bit_mask_seg_a |
                 bit_mask_seg_b |
                 bit_mask_seg_c;

      break;

    case 8:

      segments = bit_mask_seg_f |
                 bit_mask_seg_a |
                 bit_mask_seg_g |
                 bit_mask_seg_c |
                 bit_mask_seg_d |
                 bit_mask_seg_e |
                 bit_mask_seg_b;

      break;

    case 9:

      segments = bit_mask_seg_f |
                 bit_mask_seg_a |
                 bit_mask_seg_g |
                 bit_mask_seg_c |
                 bit_mask_seg_d |
                 bit_mask_seg_b;

      break;

    case DISPLAY_BLANK:

      segments = 0;

      break;

    case DISPLAY_MINUS:

      segments = bit_mask_seg_g;

      break;

    default:

      segments = 0;

      break;
  }

  return segments;
}