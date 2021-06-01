# TP3: Ta-Te-Ti #  
**Autor: Daniel Alejandro Lovera López**  
**Número padrón: 103442**  
**[https://github.com/DanieLovera/tp3](https://github.com/DanieLovera/tp3)**  

---
### Introducción ###  
El presente trabajo consiste en la creación del clásico juego Ta-Te-Ti, de manera distribuida. Es decir, el programa final es del tipo cliente-servidor con un servidor atendiendo las solicitudes de múltiples clientes. Los clientes pueden crear, unirse, jugar y listar las partidas que ya fueron creadas. El servidor por su parte tiene la lógica del juego y le responde al cliente cada vez que sea su turno.  
  
Para lograr crear un servidor-multicliente, el programa servidor deberá tener:  
- **Un hilo aceptador**: Este hilo tiene por objetivo liberar al programa principal del bloqueo generado por un socket cuando esta esperando por la llegada de un nuevo cliente, por lo tanto el servidor puede seguir ejecutando otras instrucciones independientemente del hilo aceptador que estara bloqueado en *accept*. En este trabajo esto permite que el servidor reciba un caracter **'q'** por entrada estándar que le permita saber cuando debe cerrarse.
- **Un hilo cliente por cada cliente atendido**: Estos hilos son creados por el hilo aceptador cada vez que acepta un nuevo cliente, tiene por objetivo liberarlo para evitar que operaciones bloqueantes como *send/recv* tomen el control del hilo aceptador y eviten que pueda seguir escuchando conexiones entrantes.  

Con esta estructura es suficiente para cumplir con los requerimientos del trabajo pues los *send/recv* siguien siendo ejecutados de forma secuencial. Por su parte el programa cliente no necesita ningún tratamiento especial más que el necesario para permitirle al usuario ingresar comandos por entrada estandar y comunicarse con el servidor.  

---
### Desarrollo ###  

![Diagrama de clases](images/diagrama_clases.png) 

![Diagrama de flujo](images/diagrama_flujo.png) 



