TaskHandle_t Task1;
TaskHandle_t Task2;

//Microphone Input Pins
const int volumeMic = 0;
const int lowFMic = 4;
#include "LedController.hpp"
#define CS_PIN 5

LedController<1,1> lc;

const int medFMic = 2;
const int highFMic = 34;
int L = 0, M = 0, H = 0;
int min_intensitate = 3, max_intensitate = 300;
byte coloana[9] = { B00000000, B00000001, B00000011, B00000111, B00001111, B00011111, B00111111, B01111111, B11111111 };

void setup() {
  lc = LedController<1,1>(CS_PIN);
  
  analogReadResolution(9); //9 biti 0 - 511
  Serial.begin(115200); 

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                   
  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
  delay(500); 
}

//Task1code: blinks an LED every 1000 ms
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  
  int intensitate = 0;
  
  while(1){
    intensitate = map(L, min_intensitate, max_intensitate, 1, 9);
    lc.setRow(0,7, coloana[intensitate]);
    lc.setRow(0,6, coloana[intensitate]);
    
    intensitate = map(M, min_intensitate, max_intensitate, 1, 9);
    lc.setRow(0,4, coloana[intensitate]);
    lc.setRow(0,3, coloana[intensitate]);
    
    intensitate = map(H, min_intensitate, max_intensitate, 1, 9);
    lc.setRow(0,1, coloana[intensitate]);
    lc.setRow(0,0, coloana[intensitate]);

    delay(20);
  }
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
   while(1){
      L = analogRead(lowFMic);
      if(L < 3)
        L = 0;
      M = analogRead(medFMic);
      if(M < 3)
        M = 0;
      H = analogRead(highFMic);
      if(H < 3)
        H = 0;
      
      /*
      Serial.print("Low Frequency Mic reading: ");
      Serial.println(L);
      Serial.print("Med Frequency Mic reading: ");
      Serial.println(M);
      Serial.print("High Frequency Mic reading: ");
      Serial.println(H);
      */
      
      delay(20);
  }
}

void loop() {
  
}
