/*
 * Fundacion Kinal
 * Centro educativo tecnico laboral Kinal
 * Perito en electonica
 * Quinto perito
 * EB5AM
 * Taller de electronica digital y reparacion de computadoras
 * Nombre: Francisco Barillas
 * Carnet: 2019376
*/
//Incluyo las Librerias
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Directivas de preprocesador
#define Neopixel_pin 3   
#define Sensor_RCWL 4
#define RED   8
#define BLUE  9
#define GREEN 10
#define BUZZ  14
#define PUERTA 6
#define Servo_pin 15
#define Rele_1 11
#define Rele_2 12 
#define Foco_1 7 
#define Foco_2 5 
#define DIRECCION_LCD 0x27
#define FILAS 2
#define COLUMNAS 16
//Constructores
Servo SERVO_FRANCISCO;
Adafruit_NeoPixel Neopixel(7,Neopixel_pin, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C LCD_FRANCISCO_BARILLAS(DIRECCION_LCD, COLUMNAS, FILAS);
OneWire ourWire(2);
DallasTemperature sensors(&ourWire);
//Funciones
void puerta();
void movimiento();
void temperatura();
int temperaturac();
void rele1();
void rele2();
//variables
int Celsius;
int Puerta=0; 
int foco_1=0;
int foco_2=0;

byte hielo[] = {
  B00000,
  B00000,
  B01110,
  B01010,
  B01010,
  B01110,
  B00000,
  B00000
};
byte Copo_de_Nieve[] = {
  B00000,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00000,
  B00000
};
byte Fuego[] = {
   B00010,
  B00110,
  B01110,
  B10011,
  B10111,
  B11111,
  B01110,
  B00000
};
byte person[] = {
  B01110,
  B01110,
  B01110,
  B00100,
  B11111,
  B00100,
  B01010,
  B01010
};
byte f_oof[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B01110,
  B01110,
  B00100
};
byte f_on[] = {
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B01110,
  B01110,
  B00100
};

void setup() {
  pinMode(Neopixel_pin,OUTPUT);
  pinMode(Sensor_RCWL,INPUT);
  pinMode(PUERTA,INPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(RED,OUTPUT);
  pinMode(BUZZ,OUTPUT);
  pinMode(Rele_1,OUTPUT);
  pinMode(Rele_2,OUTPUT);
  pinMode(Foco_1,INPUT);
  pinMode(Foco_2,INPUT);
  digitalWrite(Rele_1, HIGH);
  digitalWrite(Rele_2, HIGH);
  //
  SERVO_FRANCISCO.attach(Servo_pin);
  sensors.begin();  
  LCD_FRANCISCO_BARILLAS.init(); //inicio la comunicacion serial con el modulo i2c
  LCD_FRANCISCO_BARILLAS.backlight(); 
  LCD_FRANCISCO_BARILLAS.createChar(0,hielo);
  LCD_FRANCISCO_BARILLAS.createChar(1,Copo_de_Nieve);
  LCD_FRANCISCO_BARILLAS.createChar(2,Fuego);
  LCD_FRANCISCO_BARILLAS.createChar(3,person);
  LCD_FRANCISCO_BARILLAS.createChar(4,f_oof);
  LCD_FRANCISCO_BARILLAS.createChar(5,f_on);
  LCD_FRANCISCO_BARILLAS.setCursor(0,1);
  LCD_FRANCISCO_BARILLAS.print("P:close");
  LCD_FRANCISCO_BARILLAS.setCursor(9,1);
  LCD_FRANCISCO_BARILLAS.print("F:");
  LCD_FRANCISCO_BARILLAS.write(4);
  LCD_FRANCISCO_BARILLAS.setCursor(13,1);
  LCD_FRANCISCO_BARILLAS.print("F:");
  LCD_FRANCISCO_BARILLAS.write(4);
}

void loop() {
  Celsius = temperaturac();
  puerta();
  rele1();
  rele2();
  puerta();
  temperatura();
  rele1();
  rele2();
  movimiento();
  rele1();
  rele2();
  puerta();
}

void temperatura(){
  if ( Celsius> 14 && Celsius<22){
      LCD_FRANCISCO_BARILLAS.setCursor(0,0);
      LCD_FRANCISCO_BARILLAS.print("Temp:");
      LCD_FRANCISCO_BARILLAS.write(0);
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, LOW);
      }  
  if ( Celsius>21 && Celsius<26){
      LCD_FRANCISCO_BARILLAS.setCursor(0,0);
      LCD_FRANCISCO_BARILLAS.print("Temp:");
      LCD_FRANCISCO_BARILLAS.write(1);
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, HIGH);
      } 
  if ( Celsius>25 && Celsius<46){
      LCD_FRANCISCO_BARILLAS.setCursor(0,0);
      LCD_FRANCISCO_BARILLAS.print("Temp:");
      LCD_FRANCISCO_BARILLAS.write(2);
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, LOW);
      }  
}

int temperaturac(){
  sensors.requestTemperatures();
  float temp= sensors.getTempCByIndex(0);
  return temp;
}

void movimiento(){
  bool accion = digitalRead(Sensor_RCWL);
  if(accion==1){
    LCD_FRANCISCO_BARILLAS.setCursor(9,0);
    LCD_FRANCISCO_BARILLAS.print("Radar:");
    LCD_FRANCISCO_BARILLAS.write(3);
    for(int i =0; i<8; i++){
      Neopixel.setPixelColor(i,Neopixel.Color(255,0,0));
      Neopixel.show(); 
    }
    digitalWrite(BUZZ, HIGH);
    delay(250);
    for(int i =0; i<8; i++){
      Neopixel.setPixelColor(i,Neopixel.Color(124,252,0));
      Neopixel.show(); 
    }
    LCD_FRANCISCO_BARILLAS.setCursor(9,0);
    LCD_FRANCISCO_BARILLAS.print("Radar: ");
    digitalWrite(BUZZ, LOW);
    delay(250);
   
  }
  if(accion==0){
    for(int i =0; i<8; i++){
      Neopixel.setPixelColor(i,Neopixel.Color(0,0,255));
      Neopixel.show(); 
      LCD_FRANCISCO_BARILLAS.setCursor(9,0);
      LCD_FRANCISCO_BARILLAS.print("Radar: ");
    }
  }
}
void puerta(){
  if(digitalRead(PUERTA) && Puerta==0){
    SERVO_FRANCISCO.write(0);
    LCD_FRANCISCO_BARILLAS.setCursor(0,1);
    LCD_FRANCISCO_BARILLAS.print("P:open ");
    delay(500);
    Puerta=1;
  }
  if(digitalRead(PUERTA) && Puerta==1){
    SERVO_FRANCISCO.write(90);
    LCD_FRANCISCO_BARILLAS.setCursor(0,1);
    LCD_FRANCISCO_BARILLAS.print("P:close ");
    delay(500);
    Puerta=0;
  }
}

void rele1(){
  if (digitalRead(Foco_1) && foco_1==0){
    digitalWrite(Rele_1, LOW);
    LCD_FRANCISCO_BARILLAS.setCursor(9,1);
    LCD_FRANCISCO_BARILLAS.print("F:");
    LCD_FRANCISCO_BARILLAS.write(5);
    delay(500);
    foco_1=1;
  }
if (digitalRead(Foco_1) && foco_1==1){
    digitalWrite(Rele_1, HIGH);
    LCD_FRANCISCO_BARILLAS.setCursor(9,1);
    LCD_FRANCISCO_BARILLAS.print("F:");
    LCD_FRANCISCO_BARILLAS.write(4);
    delay(500);
    foco_1=0;
  }
}
 
void rele2(){
  if (digitalRead(Foco_2) && foco_2==0){
    digitalWrite(Rele_2, LOW);
    LCD_FRANCISCO_BARILLAS.setCursor(13,1);
    LCD_FRANCISCO_BARILLAS.print("F:");
    LCD_FRANCISCO_BARILLAS.write(5);
    delay(500);
    foco_2=1;
  }
if (digitalRead(Foco_2) && foco_2==1){
    digitalWrite(Rele_2, HIGH);
    LCD_FRANCISCO_BARILLAS.setCursor(13,1);
    LCD_FRANCISCO_BARILLAS.print("F:");
    LCD_FRANCISCO_BARILLAS.write(4);
    delay(500);
    foco_2=0;
  }
}
