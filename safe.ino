#include <Keypad.h>
#include <Servo.h>

Servo servo;

String codeSecured = "";
String codeEntered = "";

int pass = 0;
int go = 0;

byte rowPins[4] = {9,8,7,6};
byte colPins[4] = {5,4,3,2};

char keys[4][4] = {
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'},
 {'*', '0', '#', 'D'},
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);
 
void setup() {
  Serial.begin(9600);
  servo.attach(10);
  servo.write(180);
}

void loop(){ 
  char key = keypad.getKey();
  
  if(pass <= 5){  
    if(key){
      codeSecured += String(key);
      pass++;
    }
  } 

  if(pass == 6){
    go = 1;
  }
 
  while(go){
    char key = keypad.getKey();
    
    if(key)
    {
      codeEntered += String(key);
      Serial.print(codeEntered);
      if(codeEntered.length() >= 6)
      {
        if(codeSecured == codeEntered)
        {
          delay(500);
          servo.write(50);
        }
      }
       
      if(key == '*')
      {
        servo.write(180);
        codeEntered = "";
      }
      
      delay(100);
      
    }
  }
}
