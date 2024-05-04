# Sockets

El modelo de la clase sockets utilizado fue el provisto por la catedra: [Eldipa](https://github.com/eldipa/sockets-en-cpp)

Basandonos en el modelo de Sockert provisto por la catedra, lo que se hizo fue diseñar la implementacion de 2 clases denominadas "ProtocoloClient" y "ProtocoloServer", las cuales se encargaran de aplicar el respectivo protocolo que se enunció para este trabajo practico. Ambas clases son las que posibilitan la comunicacion entre el cliente y servidor y ambas almacenan un Socket creado por medio de la clase "Socket".
Por otro lado, se cuentan con clases para encapsular comportamiento como "Movimientos" que maneja la logica como se encuentran los combos, y "Mensajero" que se encarga de transformar lo que el cliente introduce a un formato controlable por el protocolo. Las clases "LibError", "Resolver" y "ResolverError" sirven para el manejo de errores y la encapsulacion del comportamiento de la clase "Socket".

![ImagenDelDiagramaDeClasesUML](/docs/ClassDiagramSocket.png)


Nuestro programa "client_main" unicamente recibe el la direccion de IP, el puerto o servicio y luego se encarga de enviar al mensajero lo que se encuentra en la entrada estandar linea por linea. El mensajero maneja este mensaje para convertirlo en algo controlable por el protocolo y luego el protocolo lo prepara para su envio.

Por otro lado, nuestro "server_main" unicamente recibe el puerto o servicio por el cual escuchar e indica al protocolo que debe ponerse en marcha para la escucha de los clientes que deseen comunicarse con él (en este caso adminitmos un unico cliente). Este aplica el protocolo correspondiente y reenvia la informacion pertinente al cliente.

#CORRECCIONES
1) En ProtocoloClient: "sendsome/recvsome no te garantizan q van a enviar/recibir la cantidad de bytes pedidas: necesitas un loop o sendall/recvall."
   Correccion: Se modificaron todos los sendsome/recvsome por su version sendall/recvall para garantizar en mayor medida el envio de toda la informacion.

3) En ProtocoloServer: "Mezclas logica con protocolo: el protocolo no debe saber sobre como se arman lo combos."
   Correccion: Se encapusló la logica de buscar combos y la cantidad de movimientos realizados dentro de la clase "Movimientos".

5) En client_main: "Encapsular en el correspondiente TDA."
   Correccion: Se encapsuló el manejo de la informacion recibida por entrada estandar por parte del usuario dentro de la clase "Mensajero".

7) En ProtocoloClient: "Esto no corresponde para este TP."
   Correccion: Se modificaron los nombres de las variables para que representen realmente su funcion.
