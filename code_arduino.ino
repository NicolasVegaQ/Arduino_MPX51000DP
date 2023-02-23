 #include <LiquidCrystal.h>  
 LiquidCrystal lcd(10, 9, 8, 5, 4, 3, 2); //(RS, RW, E, D4,D5, D6, D7)


//-------------------Declaracion de variables globales------------------
float P;
const float Voffset = 0.2/0.0451; //0.2 -> es el voltaje tipico minimo con que trabaja el sensor
const float Sensitivity = 1/0.0451; //Resolucion del sensor 45 mV/Kpa
const float Vs = 5.0;
int const n = 4;
int Pin = A0;

//-------------------------------Presión--------------------------------------
float getPressure(){
  //ADC 0->1023 Resolución 4.888 mV/bit  siendo 5v -> 1024bit
    int bitADC = analogRead(Pin);
    return bitADC*(Vs/1023.0)*Sensitivity-Voffset;    
  };

//-----------------------------Average------------------------------------------
float average(){
  float accu = 0;  
  for(int i=1;i<=n;i++){
    P = getPressure();
    accu+=P;
  }
  return accu/n;
}

//---------------------------------Presion en psi-----------------------------------
float getpPressurePsi(float P_kpa){
  //1.0kPa (kiloPascal) equals 0.145 psi
  return 0.145038*P_kpa;
}
//--------------------------------Main--------------------------------------------
void setup() {
  //Velocidad con la que trasmite los datos por comunicacion serial la placa
  Serial.begin(9600);
  //(columnas,filas)
  lcd.begin(16,2);
  lcd.setCursor(4, 0);
  lcd.print("SENSOR");
  lcd.setCursor(3, 1);
  lcd.print("MPX5100DP");
  delay(500);
}

void loop() {

  float Pa = average();
  //float Pa = getPressure();
  Serial.print("Presion Pascales: ");
  Serial.print(Pa,3);
  Serial.println(" Pa");
  float Ppsi = getpPressurePsi(Pa);
  Serial.print("Presion Psi: ");
  Serial.print(Ppsi,3);
  Serial.println(" Psi");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("P(Kpas): ");
  lcd.print(Pa);
  lcd.setCursor(0,1);
  lcd.print("P(Psi): ");
  lcd.print(Ppsi);
  delay(500);
  
}
