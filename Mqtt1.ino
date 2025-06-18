#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

// Conectarse a una red por nombre + contraseña
void conectarWiFi() {
  WiFi.begin("washington", "washington");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(". . . ");
    delay(1000); // aún no está conectado
  }
  Serial.println("Conectado");
}

// Callback que responde ante un nuevo mensaje recibido
void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA); // Fuerza al ESP32 a arrancar como estación
  conectarWiFi();

  // Realizamos la conexión con el servidor MQTT
  client.setServer("broker.hivemq.com", 1883);

  // Configuramos el cliente con el callback correcto
  client.setCallback(callback);

  // Esperamos hasta que se conecte
  while (!client.connect("washington")) { // ID que nos identifica
    Serial.println("esperando...");
    delay(3000);
  }

  // Me suscribo al tópico del otro ESP32
  client.subscribe("huergo/sistemas-embebidos/serafini");
}

void loop() {
  // Mantiene la conexión y recibe mensajes
  client.loop();

  // Leer mensaje desde el monitor serial
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    // Enviar mensaje al topic propio
    String mensaje = "washington: " + msg;
    client.publish("huergo/sistemas-embebidos/washington", mensaje.c_str());
  }
}
