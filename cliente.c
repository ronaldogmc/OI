//=============================================================================
// CLIENTE.C 
// Exemplo de uso do mecanismo de comunicação por Socket - UDP
// Programa que envia e recebe uma mensagem para outro processo via socket
// Ramon Gottardo
// Ronaldo Guimaraes
//=============================================================================

#include "./local.h"
main(int argc, char *argv[])
{
  int socket_servidor,bytes_enviados, bytes_recebidos;
  struct sockaddr_in servidor;
  int tamanho_servidor = sizeof(servidor);
  char buffer[MAX_SIZE_BUFFER]="qualquer coisa ...";
  char novo_buffer[MAX_SIZE_BUFFER]="qualquer coisa ...";

  system("clear");

  while ( strcmp(buffer,"shutdown") != 0 ) {

  socket_servidor = socket(AF_INET, SOCK_DGRAM, 0);

  bzero(&servidor, sizeof(servidor));
  servidor.sin_family        = AF_INET;
  servidor.sin_port          = htons(atoi(argv[2]));
  servidor.sin_addr.s_addr = inet_addr(argv[1]);

      printf("> ");
      gets(buffer);
      
      if ( strcmp(buffer,"exit") == 0 ) 
	{ 
         system("clear");
	 exit (0);
	}
	
      if ( strcmp(buffer,"help") == 0 ) 
	{ 
        printf("\n--------------------------------------\n");
	printf("date:     (remoto) retornar a data.\n");
	printf("time:     (remoto) retornar a hora.\n");
	printf("nodename: (remoto) retornar o nome do no.\n");
	printf("sysname:  (remoto) retornar o nome do sistema.\n");
	printf("release:  (remoto) retornar a liberação do sistema.\n");
	printf("version:  (remoto) retornar a versão do sistema.\n");
	printf("machine:  (remoto) retornar o nome da maquina.\n");
	printf("shutdown: (remoto) encerrar a execução da aplicação SERVIDOR.\n");
	printf("credits:  (remoto) exibir o nome completo da equipe.\n");
	printf("exit:     (local)  encerrar a execução da aplicação CLIENTE.\n");
	printf("help:     (local)  exibir um auxilio sobre os comandos existentes.\n");
	printf("--------------------------------------\n");
	}
	
      bytes_enviados=sendto(socket_servidor, buffer, MAX_SIZE_BUFFER, 0, (struct sockaddr *)&servidor, sizeof(servidor));

      bytes_recebidos = recvfrom(socket_servidor, novo_buffer,MAX_SIZE_BUFFER, 0, (struct sockaddr *)&servidor, &tamanho_servidor);

      printf("Resposta Recebida: %s.\n", novo_buffer);

      close(socket_servidor);

  }
  system("clear");

  return 0;
}