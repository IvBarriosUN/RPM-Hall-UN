#include <TM1637Display.h>
//#include "SevSeg.h"
//SevSeg sevseg;

#define CLK 12                          // El pin de reloj del display
#define DIO 2                           // El pin de datos del display
#define Pin_Hall 36                     // El pin del sensor de efecto hall
#define Pin_Unidad 7                     // El pin que define la unidad desplegada 1 = Km/h; 0 = RPM

unsigned long TiempoInicial = millis(); // Inicialización de la variable de conteo de tiempo
const long Muestreo = 1000;             // Tiempo de muestreo (en milisegundos)
float Conteo = 0.0;                     // Contador de activaciones del sensor
bool Encendido = false;                 // Variable para revisión del estado el sensor
int Imanes = 2;                         // Número de imanes en el eje
float Radio = 0.0;                      // Radio del eje
float RPM = 0.0;                        // Velocidad angular (RPM)
float Vel = 0.0;                        // Velocidad lineal (Km/h)


TM1637Display display = TM1637Display(CLK, DIO); // Crea el objeto de display

void setup() {
  /*
  Esta subrutina de setup puede ser usada en caso de necesistar usar un display de 4 dígitos sin controlador,
  configura los pines y usa "sevseg.refreshDisplay();" repetidamente o con un delay bajo para desplegar.
  Código tomado de los ejemplos de la librería.
  */

  // byte numDigits = 4;  
  //   byte digitPins[] = {2, 3, 4, 5};
  //   byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  //   bool resistorsOnSegments = 0; 
  //   // variable above indicates that 4 resistors were placed on the digit pins.
  //   // set variable to 1 if you want to use 8 resistors on the segment pins.
  //   sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments, false, false, false);
  //   sevseg.setBrightness(80);

    display.setBrightness(6); // Brillo del display (Max 7)
    display.clear();
    pinMode(Pin_Hall, INPUT); // 
    pinMode(Pin_Unidad, INPUT); // 
}


void loop() {
  
  // Detecta cambios en estados lógicos del sensor para determinar el número de disparos en el tiempo dado

  if (digitalRead(Pin_Hall)==0){
      if (Encendido==false){
        Encendido = true;
        Conteo++;
      }
    } else{
      Encendido = false;
    }

  unsigned long TiempoActual = millis();       // Revisa el tiempo transcurrido
  if (TiempoActual-TiempoInicial>= Muestreo){  // En el intervalo de muestra, calcula la velocidad
    RPM = Conteo/Muestreo*60000/Imanes;        // Velocidad angular
    Vel = RPM*2*PI*Radio/60*3.6;               // Velocidad lineal
    Conteo = 0.0;                              // Reinicio del conteo del sensor
    TiempoInicial = TiempoActual;              // Reinicio del conteo de tiempo
      }

  // Despliega velocidad lineal o angular dependiendo del estado del pin de unidad
  if (digitalRead(Pin_Unidad) == 0){
    display.showNumberDecEx(round(RPM*10.0), 0b00100000, false);
  } else{
    display.showNumberDecEx(round(Vel*100.0), 0b01000000, false);
  }

}
