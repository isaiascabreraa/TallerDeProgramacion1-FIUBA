# Threads

El modelo de la clase Threads y Queue utilizado fue el provisto por la catedra: [Eldipa](https://github.com/eldipa/hands-on-threads.git)

En el diagramas de clases a continuacion se muestran las principales clases implementadas del lado del servidor. Desde nuestro main creamos la instancia de Juego (Thread main) en donde a continuacion se crea la instancia de Aceptador (Thread 1). Juego continuará ejecutandose en un loop hasta que el servidor presione la letra 'q'. Aceptador se encargará de la aceptacion de jugadores y en ciertos momento corroborará si hay jugadores que ya esten desconectados para poder eliminarlos de su lista, ademas instanciará la clase Partida (Thread 4) que se ejectuará en un loop para simular el mundo del juego. Partida interactúa con un protocolo para poder generar los mensajes para cada uno de los jugadores, y la forma en la que les envia estos mensajes en forma de broadcast es por medio de la clase ControladorPartida. Esta clase maneja las referencias a las Queues de todos los jugadores asi como a la Queue partida. ControladorPartida es la que actua como nuestro monitor de la lista de referencias de las Queues de todos los jugadores para así evitar las race condition entre los diferentes threads. Por otro lado, la clase Jugador que se implementa cuando Aceptador acepta a nuevos jugadores y esta misma clase lanza dos nuevos threads, el Receiver (Thread 2) y el Sender (Thread 3). Cada uno de ellos cumple la funcion de recibir y enviar datos entre el cliente y servidor. Finalmente, aunque no se muestra en este diagrama, la clase Aceptador acepta jugadores nuevos por medio de la clase Socket, a la cual le delega completamente esta tarea.

![ImagenDelDiagramaDeClasesSERVER_UML](/docs/ThreadClasesPrincipales0.png)

Como se mencionó anteriormente, a continuacion se ilustra el manejo de hilos a lo largo del programa. La forma de visualizacion es de izquierda a derecha y de arriba hacia abajo. Cada una de las clases que se ejecuta en thread especifico (con expcepcion del jugador), lo hacen por medio de heredar de una clase padre llamada Thread que se encuentra con el nombre de "common_thread.h". Esta clase thread tiene un metodo run() que permite sobreescribirse y en él es donde se coloca la funcionalidad que esperamos que tenga nuestro thread. Las clases que corren en diferentes thread son: Aceptador, Partida, Sender y Aceptador.

![ImagenDeHilosDelPrograma](/docs/HilosDelPrograma.png)

Por el lado del cliente, el diagrama de clase representado a continuacion ilustra como partiendo desde un main se solicita recibir informacion por la entrada estandar. Esta informacion es enviada a una clase mensajera que se encarga de adaptar el mensaje a un formato que el ProtocolClient pueda manejar. El protocolo cliente se encarga de realizar las operaciones necesarias con el mensaje para luego enviarlo por medio de la clase Socket.
Cuando el cliente solicita leer los mensajes que ha recibido hasta ahora, la clase ProtocolClient empaqueta los datos recibidos para poder devolverlos a la clase Mensajero. Mensajero es quien comunicará los resultados obtenidos al cliente (ProtocolClient solo convierte la informacion recibida del servidor en algo comprensible para el cliente).

![ImagenDelDiagramaDeClasesCLIENTE_UML](/docs/ThreadClasesPrincipales1.png)

Para este trabajo se emplearon 2 tipos de Queues. Cada cliente tiene asociada una Queue bloqueante ya que me interesa siempre estar esperando a que el juego me envie su estado para poder comunicarselo al cliente. Por otro lado, la Queue de partida (la que opera dentro del Gameloop) es no bloqueante ya que no me interesa tener siempre informacion lista para manejar. Lo que es prioridad en el gameloop es continuar realizando iteraciones para que el mundo de juego continue y se sigan incrementando los turnos. Si esta Queue fuera bloqueante entonces, a menos que el jugador enviara algun comando, nunca se pasaria al siguiente turno y en este caso en particular, los enemigos nunca revivirian.
Para poder manejar estos dos tipos de Queues se emplearon dos hilos diferentes por lo que gameloop no se ve afectada por el caso en que se tenga que esperar para enviar la informacion del estado del juego al cliente.

#CORRECIONES:
1) Se modificó la forma en la que se cerraba el socket aceptador. Ahora se hace shutdown() para la finalizacion del mismo.
2) Se agregaron las restricciones de copia y movimiento para las clases que lo requerian como Jugador o Partida.
3) Se agregó un metodo que limpia los jugadores que vayan saliendo de la partida. Si bien antes ya se eliminaban de la lista de Queues, ahora tambien se eliminan de la lista de jugadores.
4) Se modificó el nombre de GameLogic por Aceptador para que represente mejor su proposito.
5) Iniciar partida ahora inicia en el momento que el servidor inicia, no espera a que se conecte algún jugador.
6) El Sender tiene su propia referencia a la Queue del cliente sobre la cual va a tomar elementos y luego enviarselos por el socket.
7) Se modificaron los nombres de los archivos para que correspondan con quien los usa (Si el server, el cliente o common en caso de usarlos ambos).