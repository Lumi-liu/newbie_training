float sinVal;
int toneVal;
int redPin = 6;
int greenPin = 7;
int bluePin = 8;
unsigned long tepTimer ;
int red = 4;
int green = 12;
int yellow = 13;


void setup(){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(2, OUTPUT); 
  Serial.begin(9600); 
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow,OUTPUT);
}

void loop(){
  int val; 
  double data; 
  val=analogRead(3);
  /*
  int x=0;
  int y=0;
  int z=0;
  
  for(x=0;x<=255;x++)
  {
    analogWrite(redPin,constrain(x,0,255));
    for(y=0;y<=255;y++)
    {
      analogWrite(greenPin,constrain(y,0,255));
      for(z=0;z<=255;z++)
      analogWrite(bluePin,constrain(z,0,255));
    }

  }
   */ 
  digitalWrite(green,HIGH);
  digitalWrite(red,LOW);
  digitalWrite(yellow,LOW);
  data = (double) val * (5/10.24);
  
  if(data>27){
    digitalWrite(yellow,HIGH);
    digitalWrite(green,LOW); 
  }
  if(data>30){
    for(int x=0; x<180; x++){
      sinVal = (sin(x*(3.1412/180)));
      toneVal = 2000+(int(sinVal*1000));
      tone(2, toneVal);
      digitalWrite(green,LOW);
      digitalWrite(red,HIGH);
      digitalWrite(yellow,LOW);
   //   delay(500);
       }
   } 
  else {
    noTone(2);
  }
  //if(millis() - tepTimer > 1000){
  //tepTimer = millis();
  Serial.print("temperature:  ");
  Serial.print(data);
  Serial.println(" C");
//  delay(500);
//  }
colorRGB();
  
}


void color(){
//  analogWrite(redPin,constrain(0,0,255));
//  analogWrite(greenPin,constrain(0,0,255));
//  analogWrite(bluePin,constrain(0,0,255));
//  delay(500);
  
  analogWrite(bluePin,constrain(255,0,255));
  delay(random(500,1500));
  
  analogWrite(bluePin,constrain(0,0,255));
  analogWrite(greenPin,constrain(255,0,255));
  delay(random(500,1500));
  
  analogWrite(bluePin,constrain(255,0,255));
  delay(random(500,1500));
  
  analogWrite(bluePin,constrain(0,0,255));
  analogWrite(greenPin,constrain(0,0,255));
  analogWrite(redPin,constrain(255,0,255));
  delay(random(500,1500));
  
  analogWrite(bluePin,constrain(255,0,255));
  delay(random(500,1500));
  
  analogWrite(bluePin,constrain(0,0,255));
  analogWrite(greenPin,constrain(255,0,255));
  delay(random(500,1500)); 
  
  analogWrite(bluePin,constrain(255,0,255));
 // delay(500);
}


void colorRGB(){
  analogWrite(redPin,constrain(0,0,255));
  analogWrite(greenPin,constrain(0,0,255));
  analogWrite(bluePin,constrain(0,0,255));
  delay(100);
  
  analogWrite(bluePin,constrain(255,0,255));
  delay(100);
  
  analogWrite(redPin,constrain(0,0,255));
  analogWrite(greenPin,constrain(0,0,255));
  analogWrite(bluePin,constrain(0,0,255));
  delay(100);
  
  analogWrite(greenPin,constrain(255,0,255));
  delay(100);
  
  analogWrite(redPin,constrain(0,0,255));
  analogWrite(greenPin,constrain(0,0,255));
  analogWrite(bluePin,constrain(0,0,255));
  delay(100);
  
  analogWrite(bluePin,constrain(255,0,255));
  analogWrite(greenPin,constrain(255,0,255));
  delay(100);
  
  analogWrite(redPin,constrain(0,0,255));
  analogWrite(greenPin,constrain(0,0,255));
  analogWrite(bluePin,constrain(0,0,255));
  delay(100);
 
  analogWrite(redPin,constrain(255,0,255));
  delay(100);
  
  analogWrite(redPin,constrain(0,0,255));
  analogWrite(greenPin,constrain(0,0,255));
  analogWrite(bluePin,constrain(0,0,255));
  delay(100);
  
  analogWrite(redPin,constrain(255,0,255));
  analogWrite(bluePin,constrain(255,0,255));
  delay(100);
  
  analogWrite(redPin,constrain(0,0,255));
  analogWrite(greenPin,constrain(0,0,255));
  analogWrite(bluePin,constrain(0,0,255));
  delay(100);
  
  analogWrite(redPin,constrain(255,0,255));
  analogWrite(greenPin,constrain(255,0,255));
  delay(100); 
  
  analogWrite(redPin,constrain(0,0,255));
  analogWrite(greenPin,constrain(0,0,255));
  analogWrite(bluePin,constrain(0,0,255));
  delay(100);
  
  analogWrite(redPin,constrain(255,0,255));
  analogWrite(greenPin,constrain(255,0,255));
  analogWrite(bluePin,constrain(255,0,255));
  delay(100);
}
