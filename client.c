//******************************* CLIENTE **********************************
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>

int main(int argc, char *argv[]) {
  
   int clientSocket, remotePort, status = 0;
   struct sockaddr_in ServerName={0};//CONTIENE LA DIRECCION Y PUERTO DEL SERVIDOR   
   
   char dirserver[16]= "127.0.0.1";  //DIRECCION DEL SERVIDOR    
   remotePort= 5001;  //PUERTO PREESTABLECIDO PARA EL SERVIDOR
       
   
   char peticion[50], respuesta[50];   
     
    //la funcion socket crea un socket y retorna su descriptor el cual se almacena en la variable  clientSocket   
   clientSocket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

   if(clientSocket ==-1) {
      printf("No es posible crear el socket\n");
      exit(1);
   }

   ServerName.sin_family = AF_INET;//Espacio de direcciones que permite una conexiòn a una maquina conectada a internet
   ServerName.sin_port = htons(remotePort);//asignacion del puerto por el cual se conectara
   ServerName.sin_addr.s_addr = inet_addr(dirserver); //asignacion de la direccion del servidor;

   //la funcion connect intenta establecer una conexion con un socket servidor
   status = connect(clientSocket,(struct sockaddr *)& ServerName,sizeof(ServerName));
   if(status==-1) {
      printf("Error al realizarse la conexion\n");
      exit(-1);
   }
   
   
  //se capturan los parametros pasados al programa
   strcpy(peticion, argv[1]);  
   printf("El nombre del producto a buscar es: %s",peticion);

   //la funcion write escribe en el fichero asociado al descriptor almacenado en la variable clientSocket
   write(clientSocket,&peticion,sizeof(peticion));   
   //la funcion read lee del fichero asociado al descriptor almacenado en la variable clientSocket
   read(clientSocket,&respuesta,sizeof(respuesta));
   printf("\nRespuesta del servidor:  %s\n",respuesta);
   
   //la funcion close cierra el descriptor
   close(clientSocket);
}
