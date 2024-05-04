# Sockets

El modelo de la clase sockets utilizado fue el provisto por la catedra: [Eldipa](https://github.com/eldipa/sockets-en-cpp)

Basandonos en el modelo de Sockert provisto por la catedra, lo que se hizo fue diseñar la implementacion de 2 clases denominadas "ProtocoloClient" y "ProtocoloServer", las cuales se encargaran de aplicar el respectivo protocolo que se enunció para este trabajo practico. Ambas clases son las que posibilitan la comunicacion entre el cliente y servidor y ambas almacenan un Socket creado por medio de la clase "Socket".
Por otro lado, se cuentan con clases para encapsular comportamiento como "Movimientos" que maneja la logica como se encuentran los combos, y "Mensajero" que se encarga de transformar lo que el cliente introduce a un formato controlable por el protocolo. Las clases "LibError", "Resolver" y "ResolverError" sirven para el manejo de errores y la encapsulacion del comportamiento de la clase "Socket".

![ImagenDelDiagramaDeClasesUML](TP Sockets/docs/ClassDiagramSocket.png)


Nuestro programa "client_main" unicamente recibe el la direccion de IP, el puerto o servicio y luego se encarga de enviar al mensajero lo que se encuentra en la entrada estandar linea por linea. El mensajero maneja este mensaje para convertirlo en algo controlable por el protocolo y luego el protocolo lo prepara para su envio.

Por otro lado, nuestro "server_main" unicamente recibe el puerto o servicio por el cual escuchar e indica al protocolo que debe ponerse en marcha para la escucha de los clientes que deseen comunicarse con él (en este caso adminitmos un unico cliente). Este aplica el protocolo correspondiente y reenvia la informacion pertinente al cliente.
