#if !defined ClientConnection_H
#define ClientConnection_H

#include <pthread.h>

#include <cstdio>
#include <cstdint>

const int MAX_BUFF=1000;

class ClientConnection {
public:
    ClientConnection(int s);
    ~ClientConnection();
    
    void WaitForRequests();
    void stop();

    
private:  
   bool ok; // 	Esta variable es un flag que evita que el servidor
	    // escuche peticiones si ha habido errores en la inicialización.
    
    FILE *fd;	 // Descriptor de fichero en C. Se utiliza para que
		 // socket de la conexión de control tenga esté bufferado
		 // y se pueda manipular como un fichero a la C, con
		 // fprintf, fscanf, etc.
  
    char command[MAX_BUFF];  // Buffer para almacenar el comando.
    char arg[MAX_BUFF];      // Buffer para almacenar los argumentos. 
    
    int data_socket;         // Descriptor de socket para la conexion de datos;
    int control_socket;      // Descriptor de socket para al conexión de control;

    bool parar;
    bool pasivo;
    void user(void);
    void list(void);
    void pwd(void);
    void pass(void);
    void cwd(void);
    void stor(void);
    void type(void);
    void retr(void);
    void syst(void);
    void quit(void);
    void port(void);
    void pasv(void);

};

#endif