
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  


int blue = 9; // Definim pinii digitali pentru fiecare culoare
int green = 10;
int red = 11;

int redPot = A0;
int greenPot = A1; //Definim pinii analogici pentru fiecare potentiometru
int bluePot = A2;


int greenVal = 0; //Cream cate o variabila pentru a stoca starea fiecarui potentiometru
int blueVal = 0;
int redVal = 0;

const int BUTTON = 7; //Definim pinul butonului
int state = 0;    //Cream o variabila pentru starea butonului (on/off)
int val = 0;      //Cream o variabila pentru starea actuala a butonului
int old_val = 0;  //cream o variabila pentru starea veche

void setup() {
  

  lcd.init();
  
  lcd.clear();
  
  lcd.backlight();
 
  lcd.begin(16, 2);



  pinMode(green, OUTPUT);  //Aici setam ledurile ca si output, iar butonul ca input
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(BUTTON, INPUT);
  
  Serial.begin(9600);
}

void loop() {
 

  
  lcd.clear();
  
  Serial.begin(9600);                  

  val = digitalRead(BUTTON);                 // Verifica starea butonului

  if ((val == HIGH) && (old_val == LOW)) {  //Verifica daca starea butonului a fost modificata
    state = 1 - state;                       //Seteaza butonul ca pornit sau dezactivat 
    delay(10);                      
  }

  old_val = val;                            // Salveaza valoarea veche pentru a compara starea la urmatorul loop

  greenVal = analogRead(greenPot);           //Citim pozitia potentiometrului
  blueVal = analogRead(bluePot);
  redVal = analogRead(redPot);

  
  if (state == 1) {                         
                                             // Daca butonul este pornit se sincronizeaza ledul cu pozitia potentiometrului
    analogWrite(green, greenVal/4);         // Analog input are un range de la 0-1023, iar digital pwm de la 0-255, astfel impartim la 4
    analogWrite(blue, blueVal/4);           // pentru a functiona corect 
    analogWrite(red, redVal/4);              


  int  x = map(redVal, 0, 1023, 100, -1);   // Cu ajutorul acestui "map()" translatez valoarea de la analog input 0-1023
                                            // pentru a putea afisa rezultatul in procente de la 0 la 100
   lcd.setCursor(0,0);
    lcd.print("R:");
     lcd.print(x);
      lcd.print("%");
    
  int y = map(greenVal, 0, 1023, 100, -1);
  
  lcd.setCursor(8,0);
  lcd.print("G:");
  lcd.print(y);
  lcd.print("%");

  int z = map(blueVal, 0, 1023, 100, -1);
  
  lcd.setCursor(0,1);
  
  lcd.print("B:");
  lcd.print(z);
  lcd.print("%");
    
   
    delay(50);
    
  } else {                                   // Daca butonul este oprit nu vom avea permisiunea de a modifica culorile
    analogWrite(green, 0);
    analogWrite(blue, 0);
    analogWrite(red, 0);

    lcd.setCursor(0,0);
    lcd.print("Press the button");
    lcd.setCursor(0,1);
     lcd.print("to mix colours!");
    delay(50);
  }

  

  
   
}
