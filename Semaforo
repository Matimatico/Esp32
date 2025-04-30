SemaphoreHandle_t mySemaphore;  // Declaramos el semáforo (mutex)
int rojo0 = 32, amarillo0 = 13, verde0 = 12;

void setup() {
  Serial.begin(115200);
  
  pinMode(rojo0,OUTPUT);
  pinMode(amarillo0,OUTPUT);
  pinMode(verde0,OUTPUT);

  mySemaphore = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(
    taskSemaphore,  // Función que vamos a ejecutar
    "Task_Core1",   // Nombre para la función (solo para debugging)
    4096,           // Tamaño del stack
    NULL,           // Parámetros
    1,              // Prioridad de la tarea
    NULL,           // No es importante
    1               // Asignamos el núcleo 1
  );

  xTaskCreatePinnedToCore(
    taskSemaphore,
    "Task_Core0",
    4096,
    NULL,
    1,
    NULL,
    0
  );
}

void taskSemaphore(void *parameter) {
  while (1) {
    int coreID = xPortGetCoreID();  // Detecta en qué core estamos

    // Intentamos tomar el semáforo
    if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE) {
      Serial.print("Core ");
      Serial.print(coreID);
      Serial.println(" tiene el semáforo");

    // Simulación de un semáforo
      if (coreID == 0) {
        digitalWrite(rojo0,LOW);
        digitalWrite(verde0, HIGH);
        vTaskDelay(pdMS_TO_TICKS(2000));
        digitalWrite(verde0,LOW);
        digitalWrite(amarillo0, HIGH);
        vTaskDelay(pdMS_TO_TICKS(500));
        digitalWrite(amarillo0,LOW);
        digitalWrite(rojo0, HIGH);
      }
      else if (coreID == 1) {
        Serial.println("Esperando...");
	vTaskDelay(pdMS_TO_TICKS(1500));
      }
      xSemaphoreGive(mySemaphore);

      Serial.print("Core ");
      Serial.print(coreID);
      Serial.println(" liberó el semáforo");
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
}

void loop() {

}


--------------------------------------------------------------------------Sincronizacion de Semaforos--------------------------------------------------------------------------
SemaphoreHandle_t mySemaphore;  // Declaramos el semáforo (mutex)
int rojo0 = 32, amarillo0 = 13, verde0 = 12;
int rojo1 = 14, amarillo1 = 27, verde1 = 25;

void setup() {
  Serial.begin(115200);
  
  pinMode(rojo0,OUTPUT);
  pinMode(amarillo0,OUTPUT);
  pinMode(verde0,OUTPUT);
  pinMode(rojo1,OUTPUT);
  pinMode(amarillo1,OUTPUT);
  pinMode(verde1,OUTPUT);

  mySemaphore = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(
    taskSemaphore,  // Función que vamos a ejecutar
    "Task_Core1",   // Nombre para la función (solo para debugging)
    4096,           // Tamaño del stack
    NULL,           // Parámetros
    1,              // Prioridad de la tarea
    NULL,           // No es importante
    1               // Asignamos el núcleo 1
  );

  xTaskCreatePinnedToCore(
    taskSemaphore,
    "Task_Core0",
    4096,
    NULL,
    1,
    NULL,
    0
  );
}

void taskSemaphore(void *parameter) {
  while (1) {
    int coreID = xPortGetCoreID();  // Detecta en qué core estamos

    // Intentamos tomar el semáforo
    if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE) {
      Serial.print("Core ");
      Serial.print(coreID);
      Serial.println(" tiene el semáforo");

    // Simulación de un semáforo para ambos cores
      if (coreID == 0) {
        digitalWrite(rojo0,LOW);
        digitalWrite(verde0, HIGH);
        vTaskDelay(pdMS_TO_TICKS(2000));
        digitalWrite(verde0,LOW);
        digitalWrite(amarillo0, HIGH);
        vTaskDelay(pdMS_TO_TICKS(500));
        digitalWrite(amarillo0,LOW);
        digitalWrite(rojo0, HIGH);
      }
      else if (coreID == 1) {
        digitalWrite(rojo1,LOW);
        digitalWrite(verde1, HIGH);
        vTaskDelay(pdMS_TO_TICKS(2000));
        digitalWrite(verde1,LOW);
        digitalWrite(amarillo1, HIGH);
        vTaskDelay(pdMS_TO_TICKS(500));
        digitalWrite(amarillo1,LOW);
        digitalWrite(rojo1, HIGH);
      }
      xSemaphoreGive(mySemaphore);

      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
}

void loop() {

}
