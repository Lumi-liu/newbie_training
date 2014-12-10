
#include <IRremote.h>
int RECV_PIN = 12;
int redpin = 11;
int greenpin = 10;
int ar = 13;

int uu = 0;
int yy = 0;
int pp;
int i;
boolean redState = HIGH;
boolean greenState = LOW;

int ButtonState1 = LOW;
int ButtonState2 = LOW;
long lastDebounceTime1 = 0;
long lastDebounceTime2 = 0;
unsigned long lastrecv;

IRrecv irrecv(RECV_PIN);
decode_results results;
int currentNumber = 0;

long codes[13]=
{
   0xFD30CF,0xFD08F7,//0,1
   0xFD8877,0xFD48B7,//2,3
   0xFD28D7,0xFDA857,//4,5
   0xFD6897,0xFD18E7,//6,7
   0xFD9867,0xFD58A7,//8,9
   0xFD20DF,0xFD609F,//< >
   0xFD00FF,         // OPEN/CLOSE
};

int number[12][8] =  
{
  {0,0,0,1,0,0,0,1},//0
  {0,1,1,1,1,1,0,1},//1
  {0,0,1,0,0,0,1,1},//2
  {0,0,1,0,1,0,0,1},//3
  {0,1,0,0,1,1,0,1},//4
  {1,0,0,0,1,0,0,1},//5
  {1,0,0,0,0,0,0,1},//6
  {0,0,1,1,1,1,0,1},//7
  {0,0,0,0,0,0,0,1},//8
  {0,0,0,0,1,0,0,1},//9
  {1,1,1,1,1,1,1,1},//close
  {0,0,0,0,0,0,0,0}//init
};


void numberShow(int i) {
  for(int pin = 2; pin <= 9 ; pin++){
     digitalWrite(pin, number[i][pin-2]);
  }
}

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(redpin, OUTPUT);
  pinMode(ar,OUTPUT);
  pinMode(greenpin, OUTPUT);
  for(int pin = 2 ; pin <= 9 ; pin++){
      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH);
  }
}

void loop() {
    
    digitalWrite(ar,LOW);  
   ButtonState1 = analogRead(0);
   ButtonState2 = analogRead(1);
  
   if (irrecv.decode(&results)/* && (millis() - lastrecv > 1000)/*|| ButtonState1/* || ButtonState2*/) {
//     lastrecv = millis();
    
//     uu++;
     digitalWrite(ar,HIGH);
     delay(50);
     digitalWrite(ar,LOW);
     if(results.value == codes[12]){
       redState = !redState;
       greenState = !greenState;
       digitalWrite(redpin,redState);
       digitalWrite(greenpin,greenState);
   //    if(greenState)
       uu++;
       if(uu == 1)
       {
         numberShow(11);
         currentNumber = 11;
       }
       else if(!(uu%2))
         numberShow(10);
       else if(uu%2)
          numberShow(currentNumber);

     }
      

      if(greenState) {
        
        for( i = 0; i <= 11; i++){
        
         if(results.value == codes[i])
             uu++;
        }
     
      for( i = 0; i <= 12; i++){
        
        if(results.value == codes[i]&& i <= 9){
               numberShow(i);
               currentNumber = i;
               pp = currentNumber;
               Serial.println(i);
               break;        
         } 
         
      
    else if(results.value == codes[10]/* || ((millis() - lastDebounceTime1) > 500)/*&& currentNumber != 0*/){
 //     lastDebounceTime1 = millis();
         currentNumber--;
         if (currentNumber < 0)
         {
           currentNumber = 9;
         }
         numberShow(currentNumber);
         pp = currentNumber;
         Serial.println(currentNumber); 
         break;        
         }
         
         
     else if(results.value == codes[11]/* || ((millis() - lastDebounceTime2) > 500)/*&& currentNumber != 9*/){
//       lastDebounceTime2 = millis();
         currentNumber++;
         if(currentNumber > 9)
         {
            currentNumber = 0;
         }
          numberShow(currentNumber);
          pp = currentNumber;
          Serial.println(currentNumber);
          break;            
         }
      }
      
      }
    
   Serial.println(results.value, HEX);
  
  
   Serial.println(uu);
   irrecv.resume();
  }
  /*
  
  
  
  
     if ((millis() - lastDebounceTime1) > 500) {
  
    lastDebounceTime1 = millis();
    currentNumber--;
    if (currentNumber < 0)
     {
        currentNumber = 9;
     }
     numberShow(currentNumber);
     pp = currentNumber;
     Serial.println(currentNumber); 
          
     }
   if ((millis() - lastDebounceTime2) > 500) {
  
   lastDebounceTime2 = millis();
   currentNumber++;
   if(currentNumber > 9)
   {
      currentNumber = 0;
   }
   numberShow(currentNumber);
   pp = currentNumber;
   Serial.println(currentNumber);
              
   }
  
     irrecv.resume();
*/
}

