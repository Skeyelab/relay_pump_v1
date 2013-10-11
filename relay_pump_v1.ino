#include <matrix_lcd_commands.h>
#include <LiquidCrystal.h>
#include <TKLCD.h>
#include <Streaming.h>
#include <SoftwareSerial.h>
#include <serLCD.h>

#define relay 5
#define led 3 //TK O5
#define buttonPin 1 //TK I1

#define moisturePin 2
long previousMillis = 0; 

//serLCD lcd(2);
TKLCD_Local lcd = TKLCD_Local();
// the setup routine runs once when you press reset:
void setup() {    

 
  // initialize the digital pin as an output.
  pinMode(relay, OUTPUT);    
  pinMode(led, OUTPUT);
  //pinMode(buttonPin, INPUT);
  Serial.begin(9600); 
  pinMode(7, OUTPUT);

//  lcd.clear();
  checkPlants();
}

// the loop routine runs over and over again forever:
void loop() {
  unsigned long currentMillis = millis();


  if(currentMillis - previousMillis > 10000) {
    previousMillis = currentMillis; 
    checkPlants();
  }
  checkButton();
   
}

void waterPlants(int howLong){
  //lcd.clear();
  //lcd.home();
//  lcd.selectLine(2);
lcd.setCursor(1, 2);
lcd.print("Watering");
  //lcd.blink();
  Serial.println("Relay on");
  digitalWrite(led, HIGH);

  digitalWrite(relay, HIGH);
  delay(howLong*1000);
  Serial.println("Relay off");
  lcd.clearLine(2);
  
  digitalWrite(led, LOW);
  digitalWrite(relay, LOW); 
}

void checkPlants(){
  digitalWrite(7, HIGH);
  int TimerA= millis();
  while (millis() - TimerA < 1000){
    checkButton();
  }
  int val = analogRead(moisturePin);
  digitalWrite(7, LOW);

  Serial.println(val);
  lcd.clear();
  lcd << "Reading: "<< map(val,0, 1023, 0, 100);
  if (val <= 600){
    waterPlants(10);  
  }
}

void checkButton(){
  if (analogRead(buttonPin) >= 700){
    waterPlants(1); 
  }
}







