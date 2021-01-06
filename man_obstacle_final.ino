#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int buton = 8;
//#define LUNGIME_TEREN 16  //avem 16 coloane posibile pe lcd

int scor = 0;
int poz_obstacol;

int apasa = 0;
int joc=0;

int buton_apasat = LOW;
long debounce = 0;
long delay_debounce = 50;

  byte desen1[8] =
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

void loop() {
  // put your main code here, to run repeatedly:
  start();
  while(joc == 1){
    actiune();
  }
  end_game();
}

void start(){
  scor = 0;
  lcd.clear();
  lcd.print("Hello,come play!");
  lcd.setCursor(0,1);
  lcd.print("Avoid Runner!");
  delay(2000);
  lcd.clear();
  while(apasa_buton()!=1){
    lcd.setCursor(0,0);
    lcd.print("Press Button!");
    delay(100);
  }

  if(apasa_buton()==1){
    joc = 1;
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
  }else if(scor<6){
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
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.write(byte(0));
  }else{
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.write(1);
  }
}

int apasa_buton(){
  int apasare = digitalRead(buton);
  if(apasare!=buton_apasat){
    debounce = millis();
  }

  int dif = millis() - debounce;
  if( dif > delay_debounce){
    apasa = apasare;
    if(apasa == HIGH){
      buton_apasat = apasare;
      return 1;
    }
  }
  buton_apasat = apasare;
}

void actiune(){
  int poz_obstacol = 15;
  int delay_obstacol = 200;
  while(joc==1){ //cat timp jucam
    alergator(); //il afisam pe alergator fugind/miscandu-se
    if(apasa_buton()==1){  //daca apasam butonul pentru a sari
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write(2);   //il afiseaza pe alergator sarind
      obstacol(poz_obstacol);    //il afiseaza pe aparator
      delay(400);     //se asteapta un moment
      lcd.clear();    
      lcd.setCursor(0,1);
      lcd.write(1);   //afisam iarasi alergatorul, dar in pozitia de alergare, nu sarire
      obstacol(poz_obstacol);    //la fel si pe aparator
    }else{
      if(poz_obstacol!=0){       //daca pozitia nu a ajuns la zero(adica pozitia cea mai din stanga)
        alergator();  //afisam alergatorul alergand
        obstacol(poz_obstacol);  //la fel si aparatorul este afisat
      }else if(poz_obstacol==0){
        joc = 0;      //altfel jocul se termina, deoarece aparatorul a ajuns la poz zero
        break;
      }
    }
    poz_obstacol = poz_obstacol-1;  //se tot decrementeaza pozitia, adica aparatorul se apropie de alergator
    if(poz_obstacol<0){  //daca alergatorul il evita pe aparator, se revine la forma initiala
      delay_obstacol = delay_obstacol - 20;  //crestem viteza
      poz_obstacol = 15;   //aparatorul revine la pozitia initiala
      scor++;
    }
    if(delay_obstacol == 0){ 
      joc = 0; 
    }

    delay(delay_obstacol);
  }
}
