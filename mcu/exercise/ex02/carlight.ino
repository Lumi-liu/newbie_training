int carred = 12;
int caryellow = 11;
int cargreen = 10;
int button = 9;
int pedred = 8;
int pedgreen = 7;
int cross = 5000;
unsigned long changetime;

void setup()
{
  pinMode(carred,OUTPUT);
  pinMode(caryellow,OUTPUT);
  pinMode(cargreen,OUTPUT);
  pinMode(pedred,OUTPUT);
  pinMode(pedgreen,OUTPUT);
  pinMode(button,INPUT);
  digitalWrite(cargreen,HIGH);
  digitalWrite(pedred,LOW);
}

void loop() {
  int state = digitalRead(button);
  if (state == HIGH && (millis() - changetime)> 5000)
  {
    changeLights();
  }
}

void changeLights()
{
  digitalWrite(cargreen, LOW); 
  digitalWrite(caryellow, HIGH); 
  delay(2000); 
  digitalWrite(caryellow, LOW); 
  digitalWrite(carred, HIGH); 
  delay(1000); 
  digitalWrite(pedred, LOW); 
  digitalWrite(pedgreen, HIGH);
  delay(cross); 

  for (int x=0; x<10; x++) 
  {
  digitalWrite(pedgreen, HIGH);
  delay(250);
  digitalWrite(pedgreen, LOW);
  delay(250);
  }
  digitalWrite(pedred, HIGH);
  delay(500);
  digitalWrite(carred, LOW);
  digitalWrite(caryellow, HIGH);
  delay(1000);
  digitalWrite(caryellow, LOW);
  digitalWrite(cargreen, HIGH);
  changetime = millis();
}
