#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

#define LUNGIME_TEREN 16
char teren_sus[LUNGIME_TEREN];
char teren_jos[LUNGIME_TEREN];

void grafica(){
  unsigned char desen[] = {
      { B11111,    //obstacol
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111},

      { B11000,    // jumate obstacol stanga
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000},

      { B00111,    // jumate obstacol dreapta
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111,
        B00111},

    
      { B01100,    //alearga omul
        B01100,
        B00000,
        B01110,
        B11100,
        B01100,
        B11010,
        B10011},

      { B01100,    //alearga omul alta pozitie
        B01100,
        B00000,
        B11100,
        B01110,
        B01100,
        B11010,
        B10011}, 
        
      { B01100,    //om nemiscat
        B01100,
        B00000,
        B11110,
        B01100,
        B01100,
        B01100,
        B01110},

      { B01100,    //sare omul
        B01100,
        B00000,
        B11110,
        B01101,
        B11111,
        B10000,
        B00000}

      
    
    };

    for(int i=0;i<7;i++){
      lcd.createChar(i, desen[i]);
    }

    
}

void setup() {
  // put your setup code here, to run once:
  
  initializeGraphics();
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:

}
