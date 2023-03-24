#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <pthread.h>
#include<stdbool.h>
#include "funciones.h"
#define BACK_LOG 5 
#define MAXIMA_LONGITUD_CADENA 50


int serverSocket = 0;
int status = 0, clientSocket = 0;   
struct sockaddr_in serverName, clientName;   

typedef void * (*thread_start_func)(void * arg);

typedef struct {
    pthread_t id;
    pthread_attr_t attr;
    thread_start_func start_func;
    void * arg;
}Thread;

//Funcion que permite crear un nuevo hilo de ejecucion
Thread * start_thread(thread_start_func func, void * arg) {
  Thread* t;
  t=(Thread*)malloc(sizeof(Thread));
  t->start_func=func;
  t->arg = arg;
  pthread_attr_init(&(t->attr));
  pthread_create(&(t->id), &(t->attr), (void*)t->start_func, t->arg);  
  
  return t;
}

void * funcion(void *param) { // funcion que obtiene los datos de la peticion del cliente y escribe la respuesta 
    int * id;              //en el identificador del cliente obtenido mediante el accept
  	id = (int*)param;
	char peticion[50], respuesta[50]; 
    char vectorProductos [] [MAXIMA_LONGITUD_CADENA] =
    {"Primer computador MAC", "Codigo fuente de la WWWW", 
    "Cuadro Guernica de Pablo Picasso", "Escultura de Botero"};
    bool bandera=false;
	read((int)*id, &peticion, sizeof(peticion));

    bandera = existeProductoASubastar (peticion, vectorProductos);
	
    if (bandera)
    {
        strcpy(respuesta,"El producto fue encontrado");
    }
    else{
        strcpy(respuesta,"El producto NO fue encontrado");
    }
	printf("\nPeticion del Cliente: %s",peticion);
	fflush(stdout);
    write((int)*id,&respuesta,sizeof(respuesta));
}
void connectSC(){
  
   int portNum=5001;   
   //la funcion socket crea un socket y retorna su descriptor el cual se almacena en la variable  serverSocket  
   serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
   if(serverSocket == -1) {
      printf("Error al crear el socket");
      exit(1);
   }
   serverName.sin_family = AF_INET;//Espacio de direcciones que permite una conexiòn a una maquina conectada a internet
   serverName.sin_port = htons(portNum); /*asigna el puerto por el cual se escucharan las peticiones*/
   serverName.sin_addr.s_addr = htonl(INADDR_ANY); /*se establece la direccion de la maquina del socket, INADDR_ANY indica que la direccion corresponde
						    a la maquina donde se ejecuta el programa servidor*/
						    
   status = bind(serverSocket,(struct sockaddr*) &serverName, sizeof(serverName)); /*Asocia el descriptor de socket almacenado en la variable serverSocket con la direccion
										  almacenada en la variable serverName*/

   if(status==-1) {
      printf("Error en bind()\n");
      exit(1);
   }
   int x = 5;/*numero de conexiones entrantes que pueden quedarse en la cola para su aceptaciòn*/
   
   while(1) {
   	status = listen(serverSocket,x); /*Hace que el socket pasado como parametro escuche los intentos de conexiòn entrantes*/   	
   
   	if (status==-1) {
      		printf("Error en funcion Accept()\n");
      		exit(1);
   	}

      //acepta una conexion, crea un socket y devuleve el descritor del nuevo socket el cual es conectado con el socket del cliente
      clientSocket = accept(serverSocket,(struct sockaddr*) 0, (int*)NULL);  
      printf("\n\nNuevo cliente conectado ");
      //se limpia el descriptor de salida estandar  
      fflush(stdout);
      int id[1];
      id[0]=clientSocket;  
      
      //crea un nuevo hilo de ejecucion y lo lanza invocando a la funcion 'funcion' pasandole como parametro el descriptor asociado al cliente
    Thread * hilo; 	
    hilo=start_thread(funcion, (void*)&id[0]);
	
   }

}



int main(){
    printf("Iniciando servidor...\n\n");   
    connectSC();   
    printf("Termino el servidor...\n");
    return 0;
}