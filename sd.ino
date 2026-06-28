#include <SPI.h>
#include <SD.h>

File dataFile;

const int chipSelect = 10; // El pin CS de la tarjeta SD

void setup() {
  Serial.begin(9600);

  // Inicializar la comunicación con la tarjeta SD
    if (!SD.begin(10)) {
    Serial.println("Error al inicializar la tarjeta SD.");
    return;
  }

  // Abrir el archivo en modo de escritura
  dataFile = SD.open("example.csv", FILE_WRITE);

  // Verificar si se pudo abrir el archivo
  if (dataFile) {
    // Escribir "hello" seguido de una coma y luego "world"
    dataFile.println("hello;world");

    // Cerrar el archivo
    dataFile.close();

    Serial.println("Se ha creado el archivo example.csv en la tarjeta SD y se ha escrito 'hello,world' en él.");
  } else {
    // Si no se pudo abrir el archivo, imprimir un mensaje de error
    Serial.println("Error al abrir el archivo.");
  }
}

void loop() {
  // Nada más se hace en el loop, solo queremos que se ejecute una vez en la inicialización.
}
