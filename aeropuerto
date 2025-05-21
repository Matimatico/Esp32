#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

// Configuración del sistema
#define NUM_AVIONES 5
#define NUM_PISTAS 3
#define MAX_ESPERA 10

// Estructura para comunicación avión-torre
struct MensajeAterrizaje {
  int avionId;
  TickType_t tiempoSolicitud;
};

// Colas y mutex
QueueHandle_t colaSolicitudes;
QueueHandle_t colaAutorizaciones[NUM_AVIONES];
SemaphoreHandle_t mutexPistas[NUM_PISTAS];

// Tarea Torre de Control (Core 1)
void torreControl(void *pvParameters) {
  Serial.println("Torre de control iniciada");
  
  while(1) {
    MensajeAterrizaje solicitud;
    
    // Esperar solicitud de aterrizaje
    if(xQueueReceive(colaSolicitudes, &solicitud, portMAX_DELAY)) {
      Serial.printf("Torre: Recibida solicitud de aterrizaje del Avion %d\n", solicitud.avionId);
      
      // Buscar pista disponible
      int pistaLibre = -1;
      for(int i = 0; i < NUM_PISTAS; i++) {
        if(xSemaphoreTake(mutexPistas[i], 0) == pdTRUE) {
          pistaLibre = i;
          break;
        }
      }
      
      if(pistaLibre != -1) {
        // Autorizar aterrizaje en pista específica
        Serial.printf("Torre: Autorizado Avion %d para aterrizar en Pista %d\n", solicitud.avionId, pistaLibre);
        xQueueSend(colaAutorizaciones[solicitud.avionId], &pistaLibre, portMAX_DELAY);
      } else {
        // Todas las pistas ocupadas, reintentar más tarde
        Serial.printf("Torre: No hay pistas disponibles para Avion %d. Esperando...\n", solicitud.avionId);
        vTaskDelay(pdMS_TO_TICKS(1000));
        xQueueSend(colaSolicitudes, &solicitud, portMAX_DELAY);
      }
    }
  }
}

// Tarea Avión (Core 0)
void avion(void *pvParameters) {
  int avionId = (int)pvParameters;
  Serial.printf("Avion %d iniciado\n", avionId);
  
  while(1) {
    // Tiempo de aproximación aleatorio (1-5 segundos)
    int tiempoAproximacion = random(1000, 5000);
    vTaskDelay(pdMS_TO_TICKS(tiempoAproximacion));
    
    // Solicitar permiso para aterrizar
    MensajeAterrizaje solicitud;
    solicitud.avionId = avionId;
    solicitud.tiempoSolicitud = xTaskGetTickCount();
    
    Serial.printf("Avion %d solicita permiso para aterrizar\n", avionId);
    xQueueSend(colaSolicitudes, &solicitud, portMAX_DELAY);
    
    // Esperar autorización
    int pistaAsignada;
    if(xQueueReceive(colaAutorizaciones[avionId], &pistaAsignada, pdMS_TO_TICKS(MAX_ESPERA * 1000)) == pdTRUE) {
      Serial.printf("Avion %d comienza aterrizaje en Pista %d\n", avionId, pistaAsignada);
      
      // Tiempo de aterrizaje aleatorio (2-6 segundos)
      int tiempoAterrizaje = random(2000, 6000);
      vTaskDelay(pdMS_TO_TICKS(tiempoAterrizaje));
      
      // Liberar pista
      xSemaphoreGive(mutexPistas[pistaAsignada]);
      Serial.printf("Avion %d ha liberado Pista %d\n", avionId, pistaAsignada);
    } else {
      Serial.printf("Avion %d: Tiempo de espera agotado. Reintentando...\n", avionId);
    }
  }
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
  
  // Inicializar colas y semáforos
  colaSolicitudes = xQueueCreate(NUM_AVIONES, sizeof(MensajeAterrizaje));
  
  for(int i = 0; i < NUM_AVIONES; i++) {
    colaAutorizaciones[i] = xQueueCreate(1, sizeof(int));
  }
  
  for(int i = 0; i < NUM_PISTAS; i++) {
    mutexPistas[i] = xSemaphoreCreateMutex();
    xSemaphoreGive(mutexPistas[i]); // Inicialmente libres
  }
  
  // Crear tareas
  for(int i = 0; i < NUM_AVIONES; i++) {
    xTaskCreatePinnedToCore(
      avion,           // Función de la tarea
      "Avion",         // Nombre
      4096,            // Tamaño de pila
      (void*)i,        // Parámetro
      2,               // Prioridad
      NULL,            // Handle
      0                // Core 0
    );
  }
  
  xTaskCreatePinnedToCore(
    torreControl,      // Función de la tarea
    "TorreControl",    // Nombre
    4096,              // Tamaño de pila
    NULL,              // Parámetro
    3,                 // Prioridad (mayor que aviones)
    NULL,              // Handle
    1                  // Core 1
  );
}

void loop() {
}
