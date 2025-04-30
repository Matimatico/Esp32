Semaforos:
Para estos trabajos, tuvimos como objetivos tanto setear un semaforo con sus cambios de luz, como su sincronizacion.
Utilizamos un esp32, 6 leds (2 rojos, 2 amarillos y 2 verdes) con sus respetivas resistencias.
El trabajo, se hizo utilizando 2 cores para correr ambos semaforos, y para evitar solapamientos entre ambos cores, ya que estos corren a la par, se utilizo 
concurrencia que permite indicar cuando uno deja de correr para dejr que segundo arranque, cuando este segundo termina, vuelve al primero.
![se3maforo](https://github.com/user-attachments/assets/494cebf5-c5ed-4d0c-b81b-69bf1bfc49bd)
