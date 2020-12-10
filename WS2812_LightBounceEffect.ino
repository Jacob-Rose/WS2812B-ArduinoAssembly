// Program 11.2
// Arduino Uno Blink Program in AVR Assembly
// Copyright (c) 2017 Hall & Slonka

#define LEDPort PORTB           // Arduino pin 13 is bit 5 of port B
#define LEDPort_Direction DDRB  // DDRB is the port B direction register (0=input, 1=output)
#define LEDBit 5                // Constant for bit 5
//#define Clock_MHz 16
//#define MilliSec 1000000
//#define DelayTime (uint32_t)((Clock_MHz * MilliSec / 5))  // set to any rate desired

#define LEDStripLength 26
#define LEDPortNum 5
#define LEDPortDir DDRB
#define LEDPort PORTB
#define LEDBit

struct Color
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

//https://github.com/bigjosh/SimpleNeoPixelDemo/blob/master/SimpleNeopixelDemo/SimpleNeopixelDemo.ino
void setup() {         // same as pinMode(13, OUTPUT)
  //Serial.begin(9600);

  asm volatile (       // shows default parameter use instead of our defines/names
    "sbi %0, %1 \n\t"  // sets port and bit direction
    : : "I" (_SFR_IO_ADDR(DDRB)), "I" (DDB5) // I: 6-bit positive integer constant
  );
  
}

void writeOne()
{
  asm volatile(
  "sbi %0, %1 \n"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "cbi %0, %1 \n"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  : : "I" (_SFR_IO_ADDR(PORTB)),"I" (PORTB5)
  );
}

void writeZero()
{

  asm volatile(
  "sbi %0, %1 \n"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "cbi %0, %1 \n"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"
  "nop\n\t"

  : : "I" (_SFR_IO_ADDR(PORTB)),"I" (PORTB5)
  );
}
int currentLED = 0;
bool movingForward = true;
//https://forum.arduino.cc/index.php?topic=317481.0
void loop() {
  if(movingForward)
  {
     currentLED++;
     if(currentLED >= LEDStripLength)
     {
        //currentLED = 0;
       movingForward = false;
     }
  }
  else
  {
    currentLED--;
    if(currentLED ==0)
    {
      //currentLED = LEDStripLength -1;
      movingForward = true;
    }
  }

  delay(5);
  for(int LED_number = 0; LED_number < LEDStripLength; LED_number++)
  {
    Color c;
    if(LED_number == currentLED)
    {
      c.r = 255;
      c.g = 255;
    }
    else
    {
      c.r = 1;
      c.g = 1;
      c.b = 1;
    }


    delayMicroseconds(8);
    for(byte color_b = 7; color_b != 255; color_b--)//checks for overflow which is rather interesting to me
    {
      
      if(bitRead(c.g, color_b))
        writeOne();
      else
        writeZero();
    }
    for(byte color_b = 7; color_b != 255; color_b--)//checks for overflow which is rather interesting to me
    {
      
      if(bitRead(c.r, color_b))
        writeOne();
      else
        writeZero();
    }
    for(byte color_b = 7; color_b != 255; color_b--)//checks for overflow which is rather interesting to me
    {
      
      if(bitRead(c.b, color_b))
        writeOne();
      else
        writeZero();
    }
    delayMicroseconds(50);

  }

  digitalWrite(LEDPortNum, LOW);
  delayMicroseconds(100);
  /*
  asm volatile (
     " mainLoop: "                         // move DelayTime to registers
     "    mov r16, %D2  \n\t"              // LSB of DelayTime
     "    mov r17, %C2  \n\t"              // A2, B2, C2, D2 each is 8 bits
     "    mov r18, %B2  \n\t"
     "    mov r19, %A2  \n\t"              // MSB of DelayTime
     "    mov r20, %D2  \n\t"
     "    mov r21, %C2  \n\t"
     "    mov r22, %B2  \n\t"
     "    mov r23, %A2  \n\t"
     "    sbi %[port], %[ledbit] \n\t"     // set I/O bit (turn LED on)
     " onLoop: "
     "    subi r23, 1  \n\t"       // subtract constant from register
     "    sbci r22, 0  \n\t"       // subtract with carry constant from register
     "    sbci r21, 0  \n\t"
     "    sbci r20, 0  \n\t"
     "    brcc onLoop  \n\t"               // branch if carry cleared
     "    cbi  %[port], %[ledbit] \n\t"    // clear I/O bit (turn LED off)
     " offLoop:"
     "    subi r19, 1  \n\t"
     "    sbci r18, 0  \n\t"
     "    sbci r17, 0  \n\t"
     "    sbci r16, 0  \n\t"
     "    brcc offLoop \n\t"
     :                                     // no output variables
     : [port] "n" (_SFR_IO_ADDR(LEDPort)), // input variables
       [ledbit] "n" (LEDBit),              // n: integer with known value
       "d" (DelayTime)                     // d: greater than r15
     : "r16","r17","r18","r19","r20","r21","r22","r23"  // clobbers
     );
     */
}
