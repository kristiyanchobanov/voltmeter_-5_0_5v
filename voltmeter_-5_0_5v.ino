#include "voltmeter_display.h"

unsigned long time = 1;

const char seg_a = 10; 
const char seg_b = 8;
const char seg_c = 6;
const char seg_d = 4;
const char seg_e = 13;
const char seg_f = 9;
const char seg_g = 7;
const char seg_dp = 5;

unsigned char DigitIndex = 0;

unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;

const unsigned long interval = 4;
const unsigned long interval1 = 400;


const char Anode1 = A4; 
const char Anode2 = A2;
const char Anode3 = A3;
const char Anode4 = A5;

char AnodeArray[] = {Anode1, Anode2, Anode3, Anode4}; 

void SetDisplaySegments(unsigned char segments)
{
  // Проверяваме дали сегмент G трябва да свети
  if  (  (segments & bit_mask_seg_g ) == bit_mask_seg_g)
  { // Да
    digitalWrite(seg_g, LOW); // Палим сегмент g
  } else {  // Не
    digitalWrite(seg_g, HIGH);  // Гасим сегмент g
  }

  // Проверяваме дали сегмент F трябва да свети
  if  (  (segments & bit_mask_seg_f ) == bit_mask_seg_f)
  { // Да
    digitalWrite(seg_f, LOW); // Палим сегмент f
  } else {  // Не
    digitalWrite(seg_f, HIGH);  // Гасим сегмент f
  }


  // Проверяваме дали сегмент E трябва да свети
  if  (  (segments & bit_mask_seg_e) == bit_mask_seg_e)
  { // Да
    digitalWrite(seg_e, LOW); // Палим сегмент e
  } else {  // Не
    digitalWrite(seg_e, HIGH);  // Гасим сегмент e
  }


  // Проверяваме дали сегмент D трябва да свети
  if  (  (segments & bit_mask_seg_d) == bit_mask_seg_d)
  { // Да
    digitalWrite(seg_d, LOW); // Палим сегмент d
  } else {  // Не
    digitalWrite(seg_d, HIGH);  // Гасим сегмент d
  }


  // Проверяваме дали сегмент C трябва да свети
  if  (  (segments & bit_mask_seg_c ) == bit_mask_seg_c)
  { // Да
    digitalWrite(seg_c, LOW); // Палим сегмент c
  } else {  // Не
    digitalWrite(seg_c, HIGH);  // Гасим сегмент c
  }


  // Проверяваме дали сегмент B трябва да свети
  if  (  (segments & bit_mask_seg_b ) == bit_mask_seg_b)
  { // Да
    digitalWrite(seg_b, LOW); // Палим сегмент b
  } else {  // Не
    digitalWrite(seg_b, HIGH);  // Гасим сегмент b
  }


  // Проверяваме дали сегмент A трябва да свети
  if  (  (segments & bit_mask_seg_a ) == bit_mask_seg_a)
  { // Да
    digitalWrite(seg_a, LOW); // Палим сегмент a
  } else {  // Не
    digitalWrite(seg_a, HIGH);  // Гасим сегмент a
  }


  // Проверяваме дали сегмент DP трябва да свети
  if  (  (segments & bit_mask_seg_dp ) == bit_mask_seg_dp)
  { // Да
    digitalWrite(seg_dp, LOW); // Палим сегмент dp
  } else {  // Не
    digitalWrite(seg_dp, HIGH);  // Гасим сегмент dp
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(seg_a, OUTPUT);
  pinMode(seg_b, OUTPUT);
  pinMode(seg_c, OUTPUT);
  pinMode(seg_d, OUTPUT);
  pinMode(seg_e, OUTPUT);
  pinMode(seg_f, OUTPUT);
  pinMode(seg_g, OUTPUT);
  pinMode(seg_dp, OUTPUT);

  pinMode(Anode1, OUTPUT);
  pinMode(Anode2, OUTPUT);
  pinMode(Anode3, OUTPUT);
  pinMode(Anode4, OUTPUT);

  DisplayBuff[0] = 0b00001100;
  DisplayBuff[1] = 0b01111111;
  DisplayBuff[2] = 0b00001100;
  DisplayBuff[3] = 0b00001100;
}


void loop()
{

  unsigned long currentMillis = millis(); //  Дефинираме локална променлива в която записваме текущото време в милисекунди

  // Дойде ли време за опресняване на следващия разряд
  if (currentMillis - previousMillis >= interval)
  { //Да
    previousMillis += interval; //  Изчисляваме 

    // Опресняване на поредния разряд ---------------------

    digitalWrite(AnodeArray[DigitIndex], LOW);  // Гасим текущия разряд

    // Исчисляваме индекса на следващия разряд, който става текущ

    DigitIndex++; 

    if (DigitIndex > 3)
    {
      DigitIndex = 0;
    }
    // Извикваме функция на която не се интересуваме от крайният и резултат на която като входен параметър подаваме бинарно число, записано в
    // текущият елемент на масива. 
    SetDisplaySegments( DisplayBuff[DigitIndex] );  // Дисплейваме текущия разряд от дисплай буффер,
                                                    // като сетваме или клирваме пиновете към които са свързани
                                                    // съответните сегменти съгласно битоввете на дислей буфер в текущия разряд

    // Палим текущия разряд
    digitalWrite(AnodeArray[DigitIndex], HIGH);
  }

  currentMillis = millis(); //  четем текущото време в милисекунди отново

  //  
  if (currentMillis - previousMillis1 >= interval1)  
  {
    previousMillis1 += interval1;

    //long adc_state = analogRead(voltage_pin);
    int adc_state = analogRead(A1);

    int voltage   = map(adc_state, 0, 1023, -500 , 500);

    bool a = DisplayBufferPrint (voltage , 2 );

    if (a == false)
    {
      DisplayBuff[0] = bit_mask_seg_a | bit_mask_seg_d | bit_mask_seg_e | bit_mask_seg_f | bit_mask_seg_g;
      DisplayBuff[1] = bit_mask_seg_e | bit_mask_seg_g;
      DisplayBuff[2] = bit_mask_seg_e | bit_mask_seg_g;
      DisplayBuff[3] = 0;
    }

  }

}

