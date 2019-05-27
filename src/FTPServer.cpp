//****************************************************************************
//                         REDES Y SISTEMAS DISTRIBUIDOS
//                      
//                     2ª de grado de Ingeniería Informática
//                       
//  Clase principal para la implementación de un servidor FTP sencillo
// 
//****************************************************************************

#include <cerrno>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

 #include <unistd.h>


#include <pthread.h>

#include <list>

#include "common.h"
#include "FTPServer.h"
#include "ClientConnection.h"


int define_socket_TCP(int port) {
   struct sockaddr_in sin;
   int s;
   s= socket(AF_INET,SOCK_STREAM,0);
   if(s<0){
     errexit("Fallo creacion de socket:%s\n", strerror(errno));
     return -1;
   }


   memset(&sin, 0, sizeof(sin));
   sin.sin_family=AF_INET;
   sin.sin_addr.s_addr=INADDR_ANY;
   sin.sin_port=htons(port);

   if(bind(s,(struct sockaddr *)&sin, sizeof(sin))<0){
     errexit("Fallo bind: %s\n",strerror(errno));
     return -1;
   }

   if(listen(s,5)<0){
     errexit("Fallo listen :%s\n",strerror(errno));
     return -1;
   }

   return s;
}

// Esta es la función que se ejecuta al
// crear el hilo.
void* run_client_connection(void *c) {
    ClientConnection *connection = (ClientConnection *)c;
    connection->WaitForRequests();
  
    return NULL;
}



FTPServer::FTPServer(int port) {
    this->port = port;
  
}


// Parada del servidor.
void FTPServer::stop() {
    close(msock);
    shutdown(msock, SHUT_RDWR);

}


// Arranque del servidor
void FTPServer::run() {

    struct sockaddr_in fsin;
    int ssock;
    socklen_t alen;
    msock = define_socket_TCP(port);
    while (1) {
	pthread_t thread;
        ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
        if(ssock < 0)
            errexit("Fallo en el accept: %s\n", strerror(errno));
	
	ClientConnection *connection = new ClientConnection(ssock);
	
	// Aquí se crea un hilo para que se puedan ejecutar varias
	// peticiones simultáneamente.
	pthread_create(&thread, NULL, run_client_connection, (void*)connection);
       std::cout<<"Peticion entrante: "<<inet_ntoa(fsin.sin_addr)<<":"<<fsin.sin_port<<"\n";
    }

}