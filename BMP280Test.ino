//Iniciacion de librerias para componentes 
#include <Wire.h>  //Libreria para uso de protocolo I2C
#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp; //Crea el objeto BMP280 para el control de las funciones de la libreria. 

void setup() {
  Serial.begin(9600); //Inicio de comunicacion Serial 

  while ( !Serial ) delay(100); //Verificar conexion del puerto serial 
  Serial.println(F("BMP280 test")); // Imprimir mensaje de inicio "BMp280 test"


  unsigned status; //Variable de estado de sensor. 

  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76); //Iniciamos el sensor e ingresamos la direccion de I2C del dispositivo. 


//Si el estado del sensor no esta conectado devolver el mensaje de error que corresponda. 
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10); //La condicion se cierra hasta que el valor sea 1, osea no tenga errores de conexion el sensor.
  }


  /* Configuracion por defecto de la hoja de datos del fabricante */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de operacion "Normal" */
                  Adafruit_BMP280::SAMPLING_X2,     /* sobremuestreo de temperatura  */
                  Adafruit_BMP280::SAMPLING_X16,    /* sobremuestreo de presion */
                  Adafruit_BMP280::FILTER_X16,      /* Filtrado de señales  */
                  Adafruit_BMP280::STANDBY_MS_500); /* tiempo de espera */
}


void loop() {
    Serial.print(F("Temperature = "));     //Imprime el mensaje Temperatura
    Serial.print(bmp.readTemperature());   //Imprime el valor de la temperatura leida por el sensor BMP280
    Serial.println(" *C");                 //Imprime el dimensional de grados centigrados 

    Serial.print(F("Pressure = "));        //Imprime el mensaje de Presion  
    Serial.print(bmp.readPressure());      //Imprime el valor de la presion atmosferica leida por el sensor BMP280
    Serial.println(" Pa");                 //Imprime el valor de la dimensional de pascales.

    Serial.print(F("Approx altitude = ")); //Imprime el mensaje de altitud aproximadamente 
    Serial.print(bmp.readAltitude(1028));  //Imprime el valor de la altitud leida por el sensor BMP280 /* Adjusted to local forecast! */
    Serial.println(" m");                  //Imprime el valor de la dimensional de metros

    Serial.println();  //Imprime el valor 
    delay(2000);       //Espera 2 segundos entre cada medicion.
}