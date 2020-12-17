#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define LUNGIME_TEREN 16  //avem 16 coloane posibile pe lcd
int scor = 0;
int poz_obstacol;
int buton = 8;
int apasa;
int joc=0;
  byte desen1[8] = {
      { B01100,    //fuge1
        B01100,
        B00000,
        B11100,
        B01110,
        B01100,
        B11110,
        B00011};

  byte desen2[8] =
      { B00110,    //fuge2
        B00110,
        B00000,
        B00111,
        B01110,
        B00110,
        B01110,
        B00101};

   byte desen3[8] =
      { B00100,    // sare
        B01100,
        B11100,
        B01110,
        B01100,
        B11111,
        B00000,
        B00001};

    
   byte desen4[8] =
      { B00100,    //def1
        B00110,
        B00111,
        B01110,
        B00110,
        B01111,
        B01000,
        B00000};

   byte desen5[8] =
      { B00100,    //def2
        B00110,
        B00111,
        B01110,
        B00110,
        B00110,
        B00110,
        B00010}; 
        
   byte desen6[8] =
      { B00000,    //slide
        B00000,
        B00011,
        B00011,
        B00000,
        B01111,
        B01111,
        B00000};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buton,INPUT);
  lcd.begin(16,2);
  lcd.createChar(0,desen1);
  lcd.createChar(1,desen2);
  lcd.createChar(2,desen3);
  lcd.createChar(3,desen4);
  lcd.createChar(4,desen5);
  lcd.createChar(5,desen6);
  apasa = digitalRead(buton);
}

void start(){
  lcd.clear();
  lcd.print("Hello,come play!");
  lcd.setCursor(1,1);
  lcd.print("Press Button!");
  delay(2000);
  lcd.clear();
  if(buton==1){
    lcd.clear();
    lcd.write(1);
  }
  
}

void end_game(){
  if(scor==10){
    lcd.clear();
    lcd.print("Nice!Score:");
    lcd.setCursor(0,1);
    lcd.print(scor);
    delay(2000);
  }else if(scor<3){
    lcd.clear();
    lcd.print("Not bad!Score:");
    lcd.setCursor(0,1);
    lcd.print(scor);
    delay(2000);
  }else if(score<6){
    lcd.clear();
    lcd.print("Good!Score:");
    lcd.setCursor(0,1);
    lcd.print(scor);
    delay(2000);
  }else{
    lcd.clear();
    lcd.print("Keep it up!Score:");
    lcd.setCursor(0,1);
    lcd.print(scor);
    delay(2000);
  }
}

void obstacol(int i){
  if(poz_obstacol%2==0 && poz_obstacol>2){ //daca se afla pe o pozitie para si distanta e mai mai mare de 2, atunci ia o forma
    lcd.setCursor(i,1);
    lcd.write(3);
  }else if(poz_obstacol%2!=0 && poz_obstacol>2){ //daca se afla pe o pozitie impara si distanta e mai mai mare de 2, atunci ia alta forma
    lcd.setCursor(i,1);
    lcd.write(4);
  }else{
    lcd.setCursor(i,1); //daca distanta e mai mica ca si 2, atunci se fereste, luand o alta forma fata de celelalte.
    lcd.write(5);
  }
}

void alergator(){
  if(poz_obstacol%2==0){ //alergatorul ia diferite forme, in functie de pozitia para/impara in care se afla, capatand anumite forme
    lcd.setCursor(0,1);
    lcd.write(byte(0));
  }else{
    lcd.setCursor(0,1);
    lcd.write(1);
  }
}

int apasa_buton(){
  
}

void actiune(){
  while(joc==1){
    alergator();
    if(apasa_buton()==1){
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.write(2);
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  start();
}
