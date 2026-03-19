// ESP32 TEST TOUCH SENSORS WITH WATER / FRUITS / ALUMINUM FOIL
// Piano TEST
#include <MedianFilter.h>
#include <pitches.h>

MedianFilter test0(10, 40);
MedianFilter test1(10, 40);
MedianFilter test2(10, 40);
MedianFilter test3(10, 40);
MedianFilter test4(10, 40);
MedianFilter test5(10, 40);
MedianFilter test6(10, 40);
MedianFilter test7(10, 40);

#define touch_pin1 T0  // GPIO4
#define touch_pin2 T3  // GPIO15
#define touch_pin3 T4  // GPIO13
#define touch_pin4 T5  // GPIO12
#define touch_pin5 T6  // GPIO14
#define touch_pin6 T7  // GPIO27
#define touch_pin7 T8  // GPIO33
#define touch_pin8 T9  // GPIO32
#define buzzer_pin 2

// Threshold may need to be adjusted 
const int threshold = 20;

int touchState[8] = {100, 100, 100, 100, 100, 100, 100, 100};
int touchLastState[8] = {100, 100, 100, 100, 100, 100, 100, 100};

// These will likely need to be adjusted
int touchHigh = 40;
int touchLow = 30;

int freq = 2000;
int channel = 0;
int resolution = 8;

void setup() {
  Serial.begin(115200);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(buzzer_pin, channel);
}

void loop() {
  // I have 8 touch pins here but I use 7 for the piano 
  // DO - RE - MI - FA - SOL - LA - TI

  // Filtering values from touch pins
  touchState[0] = touchRead(touch_pin1);
  test0.in(touchState[0]);
  touchState[0] = test0.out();

  touchState[1] = touchRead(touch_pin2);
  test1.in(touchState[1]);
  touchState[1] = test1.out();

  touchState[2] = touchRead(touch_pin3);
  test2.in(touchState[2]);
  touchState[2] = test2.out();

  touchState[3] = touchRead(touch_pin4);
  test3.in(touchState[3]);
  touchState[3] = test3.out();

  touchState[4] = touchRead(touch_pin5);
  test4.in(touchState[4]);
  touchState[4] = test4.out();

  touchState[5] = touchRead(touch_pin6);
  test5.in(touchState[5]);
  touchState[5] = test5.out();

  touchState[6] = touchRead(touch_pin7);
  test6.in(touchState[6]);
  touchState[6] = test6.out();

  touchState[7] = touchRead(touch_pin8);
  test7.in(touchState[7]);
  touchState[7] = test7.out();
  
Serial.println(touchState[7]);
  for (int i = 0; i < 8; i++) {
    if ((touchState[i] < touchLow) && (touchLastState[i] > touchHigh)) {
      Serial.println(i);
      switch (i){
        case 0: ledcWriteTone(channel, NOTE_C5); delay(50); ledcWriteTone(channel, 0); delay(50); break;
        case 1: ledcWriteTone(channel, NOTE_D5); delay(50); ledcWriteTone(channel, 0); delay(50); break;
        case 2: ledcWriteTone(channel, NOTE_E5); delay(50); ledcWriteTone(channel, 0); delay(50); break;
        case 3: ledcWriteTone(channel, NOTE_F5); delay(50); ledcWriteTone(channel, 0); delay(50); break;
        case 4: ledcWriteTone(channel, NOTE_G5); delay(50); ledcWriteTone(channel, 0); delay(50); break;
        case 5: ledcWriteTone(channel, NOTE_A5); delay(50); ledcWriteTone(channel, 0); delay(50); break;
        case 6: ledcWriteTone(channel, NOTE_B5); delay(50); ledcWriteTone(channel, 0); delay(50); break;
        }
    }
    if ((touchState[i] < touchLow) || (touchState[i] > touchHigh))
      touchLastState[i] = touchState[i];
  }
}
