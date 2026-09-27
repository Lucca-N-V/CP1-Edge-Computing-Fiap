/* Associação de equipamentos as entradas no arduino */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int verde = 12;
int amarelo = 11;
int vermelho = 10;
int buzzer = 7;
int ldr = A0;
int luz = 0;
int porcentagem = 0;
int menor = 0;
int maior = 0;
/* Medir o tempo para o buzzer */
unsigned long tempo = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Informação para o logo
byte sol_TL_Aberto[8] = {
  B00000, 
  B10001, 
  B01001, 
  B00111, 
  B01010, 
  B11000, 
  B01010, 
  B01001  
};

byte sol_TR_Aberto[8] = {
  B00000, 
  B10001, 
  B10010, 
  B11100, 
  B01010, 
  B00011, 
  B01010, 
  B10010  
};

byte sol_BL[8] = {
  B01000, 
  B00111, 
  B01001, 
  B10001, 
  B00000, 
  B00000, 
  B00000, 
  B00000  
};

byte sol_BR[8] = {
  B00010, 
  B11100, 
  B10010, 
  B10001, 
  B00000, 
  B00000, 
  B00000, 
  B00000  
};

byte sol_TL_Pisca[8] = {
  B00000, 
  B10001, 
  B01001, 
  B00111, 
  B01100,  
  B11010,  
  B01010,  
  B01001  
};


void desenharSol(int col, int lin) {
  lcd.setCursor(col, lin);
  lcd.write(byte(0));
  lcd.setCursor(col + 1, lin);
  lcd.write(byte(1));

  lcd.setCursor(col, lin + 1);
  lcd.write(byte(2));
  lcd.setCursor(col + 1, lin + 1);
  lcd.write(byte(3));
}

void setup(){
  lcd.init();
  lcd.backlight();
  pinMode(vermelho,OUTPUT);
  pinMode(verde,OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Logo da empresa
  
  // Pega da memória
  lcd.createChar(0, sol_TL_Aberto);
  lcd.createChar(1, sol_TR_Aberto);
  lcd.createChar(2, sol_BL);
  lcd.createChar(3, sol_BR);

  // 1. O Sol Nasce e "HELIOS" aparece junto
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("HELIOS");
  desenharSol(10, 1);
  delay(800);

  // Sobe para o centro
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("HELIOS");
  desenharSol(10, 0);
  delay(1200); 

  // 2. Dá uma piscada com 1 olho
  lcd.createChar(0, sol_TL_Pisca);
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("HELIOS");
  desenharSol(10, 0);
  delay(300); 

  // Abre o olho novamente
  lcd.createChar(0, sol_TL_Aberto);
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("HELIOS");
  desenharSol(10, 0);
  delay(1200); 

  // 3. O Sol se Põe
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("HELIOS");
  desenharSol(10, 1); 
  delay(800);
  
  // Limpa a tela de vez para iniciar o projeto principal
  lcd.clear();
  // --------------------------------------------------------
}

void loop(){
  //mostra que o texto vai ser escrito na coluna 0 e linha 0
  lcd.setCursor(0,0);
  //anota o valor luminoso para uma variavel
  unsigned int luz = analogRead(ldr);
  porcentagem = map(luz, 1023, 0, 0, 100 );
  // imprime o valor junto com texto
  lcd.print("Luz: ");
  lcd.print(porcentagem);
  /* adicionar vários espaços para não existir problemas
    com 0% ocupar 2 casas e 100% ocupar 4*/
  lcd.print("%     ");
  // proxima escrita será na coluna 0 e linha 1
  lcd.setCursor(0,1);
  /* se a porcentagem luminosa está entre 40 e 49% acende o LED amarelo e
    manda um alerta que os niveis estão chegando perto exceder os parametros*/
  if (porcentagem >= 40 && porcentagem <= 49){
    digitalWrite(amarelo,HIGH);
    digitalWrite(vermelho,LOW);
    digitalWrite(verde,LOW);
    lcd.print("CUIDADO        ");
    tone(buzzer,1000);
    tempo = millis();
    /* Se o tempo desde o inicio do buzzer tocar for igual ou maior a 
    3 segundos ele para e depois continua. Mas se o nivel de luminosidade
      mudar o buzzer para automaticamente devido aos noTone(buzzer) nos outros "if". 
      Feito para registrar mudança na luminosidade sem esperar o buzzer parar*/
    if (millis() - tempo >= 3000) {
      noTone(buzzer);
    }
  }
  /* se a porcentagem luminosa está acima de 50% acende o LED vermelho
    e manda um alerta que os niveis excedendo os parametros*/
  else if(porcentagem >=50){
    noTone(buzzer);
    digitalWrite(vermelho,HIGH);
    digitalWrite(amarelo,LOW);
    digitalWrite(verde,LOW);
    lcd.print("PERIGO         ");
  }
  /*se a porcentgem está menor que 40% acende o LED verde 
  e manda um alerta avisando que os niveis estão adequados*/
  else{
    noTone(buzzer);
    digitalWrite(verde,HIGH);
    digitalWrite(amarelo,LOW);
    digitalWrite(vermelho,LOW);
    lcd.print("Niveis normais");
  }
  // não sobrecarregar
  delay(500);
}