//Código desarrollado por LEANTEC ROBOTICS&ELECTRONICS
//Esta permitido el uso de este código por cualquier usuario que lo necesite.
//Esta prohibido el usode este código con ánimo de lucro
// Incluimos la librería de los motores
#include <LEANTEC_ControlMotor.h>
// Configuramos los pines que vamos a usar
ControlMotor control(2,3,7,4,5,6); // MotorDer1,MotorDer2,MotorIzq1,MotorIzq2,PWM_Derecho,PWM_Izquierdo

#define PIN_LDR1 2    // Define el pint de LDR 1
#define PIN_LDR2 3    // Define el pint de LDR 2
#define PIN_FL1  0    // Define el pint de IR  1 (Este sensor no se usa en este programa)
#define PIN_FL2  1    // Define el pint de IR  2 (Este sensor no se usa en este programa)


#define GANANCIA   6    // Valor de ganancia para que le robot reaccione antes frente a los cambios de luz
#define P_MUERTO   10    // Valor que tendrá que superar el cambio de luz para que gire el robot +/- P_MUERTO
#define VELOCIDAD  255  // Velocidad a la que se desplazará el robot
#define GIRO_MAX   60   // Máximo giró que realizará el sensor (entre 0 y 100), 100 sería parado girando sobre su eje

int OFFSET_LDR1 = 0; // Ajusto el punto central del sensor para que los dos estén iguales
int OFFSET_LDR2 = 0; // Ajusto el punto central del sensor para que los dos estén iguales
int OFFSET_FL1  = 0; // (Este sensor no se usa en este programa)
int OFFSET_FL2  = 0; // (Este sensor no se usa en este programa)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Estos valores de abajo no es necesario cambiarlos
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sensores[4];  // Array donde se guardarán los valores   

#define LDR1 0    // Define la posición en el ARRAY donde se guardará el valor de la LDR 1
#define LDR2 1    // Define la posición en el ARRAY donde se guardará el valor de la LDR 2
#define FL1  2    // Define la posición en el ARRAY donde se guardará el valor de la IR  1 (Este sensor no se usa en este programa)
#define FL2  3    // Define la posición en el ARRAY donde se guardará el valor de la IR  2 (Este sensor no se usa en este programa)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void leer_sensores();
int calcula_diferencia();
void mostrar_valores();

//----------------------------- Configuramos Ardunio ---------------------------------------
//------------------------------------------------------------------------------------------
void setup(void){
  // Iniciamos el puerto de comunicación
  Serial.begin(9600);           
  
  //********************************* Calibramos los sensores ****************************************************//
  leer_sensores();     // Leemos sensores con los OFFSET a 0
  if(sensores[LDR1] > sensores[LDR2]){  // Comprobamos si LDR1 es mayor que LDR2
    OFFSET_LDR1 = 0;                    // Como LDR1 es mayor, sumamos a LDR2
    OFFSET_LDR2 = sensores[LDR1]-sensores[LDR2];  // Sumamos a LDR2 la diferencia para que esten igualadas las dos
   }
  else{              // Si hemos llegado aquí, es porque LDR2 o igual que LDR1
    OFFSET_LDR2 = 0;   // Como LDR2 es mayor, sumamos a LDR1
    OFFSET_LDR1 = sensores[LDR2]-sensores[LDR1];  // Sumamos a LDR1 la diferencia para que esten igualadas las dos
   }
  //**************************************************************************************************************//
}
//--------------------------- Arrancamos el programa ---------------------------------------
//------------------------------------------------------------------------------------------
void loop(void)
{
  leer_sensores();        // Leemos los sensores con los OFFSET ya calculados
  mostrar_valores();  // Mostramos los valores por si tenemos que comprobar algún dato
  control.Motor(VELOCIDAD,calcula_diferencia());   // Movemos el robot a la velocidad seleccionada y el giro calculado
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Mostramos los valores por el monitor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrar_valores(){
  Serial.print(" OFF_1 = " );  // Imprimimos el OFFSET del LDR1
  Serial.print(OFFSET_LDR1);
  Serial.print(" OFF_2 = " );  // Imprimimos el OFFSET del LDR2   
  Serial.print(OFFSET_LDR2);
  Serial.print(" LDR_1 = " );  // Imprimimos el valor del LDR1
  Serial.print(sensores[LDR1]);
  Serial.print(" LDR_2 = " );  // Imprimimos el valor del LDR2
  Serial.print(sensores[LDR2]);
  Serial.print(" DIF = " );    // Imprimimos la diferencia entre el sensor 1 y el sensor 2
  Serial.println(calcula_diferencia()); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Leemos los sensores y ajustamos los OFFSET
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void leer_sensores(){
  sensores[LDR1]=analogRead(PIN_LDR1)+OFFSET_LDR1;         // Leemos y guardamos el valor del sensor con el OFFSET incluido
  if(sensores[LDR1]<0){sensores[LDR1] = 0;}                // Comprobamos que con el OFFSET no sea menor de 0
  else if(sensores[LDR1] > 1023){sensores[LDR1] = 1023;}   // Comprobamos que con el OFFSET no sea mayor de 0
  
  sensores[LDR2]=analogRead(PIN_LDR2)+OFFSET_LDR2;         // Leemos y guardamos el valor del sensor con el OFFSET incluido 
  if(sensores[LDR2]<0){sensores[LDR2] = 0;}                // Comprobamos que con el OFFSET no sea menor de 0
  else if(sensores[LDR2] > 1023){sensores[LDR2] = 1023;}   // Comprobamos que con el OFFSET no sea mayor de 0
  
  sensores[FL1]=analogRead(PIN_FL1)+OFFSET_FL1;           // Leemos y guardamos el valor del sensor con el OFFSET incluido 
  if(sensores[FL1]<0){sensores[FL1] = 0;}                  // Comprobamos que con el OFFSET no sea menor de 0
  else if(sensores[FL1] > 1023){sensores[FL1] = 1023;}     // Comprobamos que con el OFFSET no sea mayor de 0
  
  sensores[FL2]=analogRead(PIN_FL2)+OFFSET_FL2;           // Leemos y guardamos el valor del sensor con el OFFSET incluido  
  if(sensores[FL2]<0){sensores[FL2] = 0;}                  // Comprobamos que con el OFFSET no sea menor de 0
  else if(sensores[FL2] > 1023){sensores[FL2] = 1023;}     // Comprobamos que con el OFFSET no sea mayor de 0 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Calculamos la diferencia que hay de un sensor a otro
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int calcula_diferencia(){ 
  int valor;  // En esta variable almacenamos el valor positivo o negativo del resultado de la función
    
  valor = sensores[LDR1]-sensores[LDR2];  // Restamos el valor de la LDR 1 al valor de la LDR 2, la dirección se calcula viendo si el valor es positivo o negativo.
  
  if((valor > P_MUERTO) || (valor < -P_MUERTO)){// Si el valor cambia por encima de P_MUERTO el robot cambiará de posición según la diferencia de un sensor a otros      
    valor *= GANANCIA;                    // Multiplicamos por el factor de ganancia para que el sensor gire mas rápido antes un cambio de luz.
    
    if (valor > GIRO_MAX) {valor= GIRO_MAX;}  // Comprobamos que el giro a la izquierda no pase del maximo permitido
    if(valor < -GIRO_MAX){valor = -GIRO_MAX;} // Comprobamos que el giro a la derecha no pase del maximo permitido
  }
  else {        // Si el cambio es menor al punto muerto, el robot no gira
    valor = 0;  // Dejamos que el robot sigua recto                        
  }
   return valor;  // Devolvemos el valor
} 
