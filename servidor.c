//=============================================================================
// SERVIDOR.C 
// Exemplo de uso do mecanismo de comunicação por Socket - UDP
// Programa que recebe e envia uma mensagem para outro processo via socket
// Ramon Gottardo
// Ronaldo Guimaraes
//=============================================================================

#include "./local.h"
main(int argc, char * argv[])
{
  int socket_servidor, socket_cliente, bytes_recebidos, bytes_enviados;
  struct sockaddr_in servidor, cliente;
  int tamanho_cliente = sizeof(cliente);
  int tamanho_servidor = sizeof(servidor);
  int dia=0;
  int mes=0;
  int ano=0;
  int hora=0;
  int min=0;
  int sec=0;
  int n;
  int flag;
  char data[50];
  char tempo[50];
  char buffer[MAX_SIZE_BUFFER]="qualquer coisa";
  char novo_buffer[MAX_SIZE_BUFFER]="qualquer coisa";

  system("clear");
  
  socket_servidor = socket(AF_INET, SOCK_DGRAM, 0);
  
  bzero(&servidor, sizeof(servidor));
  servidor.sin_family      = AF_INET;
  servidor.sin_port        = htons(atoi(argv[1]));
  servidor.sin_addr.s_addr = htonl(INADDR_ANY);
  
  bind(socket_servidor,(struct sockaddr *)&servidor, tamanho_servidor); 
  
  printf("Servidor aguardando comandos na porta %d\n",atoi(argv[1]));
  printf("--------------------------------------------\n");

  while (strcmp(buffer,"shutdown") != 0 ) {

      bytes_recebidos = recvfrom(socket_servidor, buffer, MAX_SIZE_BUFFER, 0,(struct sockaddr *)&cliente,&tamanho_cliente);

      printf("Comando Recebido: %s.\n", buffer);

	flag=0;

	//***PEGANDO A DATA ATUAL***	
	struct tm *local;
	time_t t;
	t= time(NULL);
	local=localtime(&t);

	dia=local->tm_mday;
	mes=local->tm_mon+1;
	ano=local->tm_year+1900;
	//***********************//

	//**PEGANDO A HORA ATUAL***//
	hora=local->tm_hour;
	min=local->tm_min;
	sec=local->tm_sec;
	//**************************//
	
        if(strcmp(buffer,"credits") == 0 ) 
	{
	flag=1;
	strcpy(novo_buffer,"\n\n****************************\n*     DESENVOLVIDO POR:    *\n*   > Ramon Gottardo       *\n*   > Ronaldo Guimarães    *\n*     ADS - 4 Semestre     *\n****************************");
       }

 	if(strcmp(buffer,"date") == 0 ) { 
	flag=1;
	n=sprintf (data, "%d/%d/%d", dia, mes, ano);
	strcpy(novo_buffer,data);

	}

	if(strcmp(buffer,"time") == 0 ) { 
	flag=1;
	n=sprintf (tempo, "%d:%d:%d", hora,min,sec);
	strcpy(novo_buffer,tempo);
	}

	if(strcmp(buffer,"nodename") == 0 ) { 
	flag=1;
	struct utsname uts;
        uname(&uts);
	strcpy(novo_buffer,uts.nodename);
	}	
	
	if(strcmp(buffer,"sysname") == 0 ) { 
	flag=1;
	struct utsname uts;
        uname(&uts);	
	strcpy(novo_buffer,uts.sysname);
	}

	if(strcmp(buffer,"release") == 0 ) { 
	flag=1;
	struct utsname uts;
        uname(&uts);	
	strcpy(novo_buffer,uts.release);
	}

	if(strcmp(buffer,"version") == 0 ) { 
	flag=1;
	struct utsname uts;
        uname(&uts);	
	strcpy(novo_buffer,uts.version);
	}
	
	if(strcmp(buffer,"machine") == 0 ) { 
	flag=1;
	struct utsname uts;
        uname(&uts);	
	strcpy(novo_buffer,uts.machine);
	}
	
	if(strcmp(buffer,"help") == 0 ) { 
	flag=1;
	strcpy(novo_buffer,"ACK");
	}
	
	//**LOG**
	FILE * pFile;
  	pFile = fopen ("log.txt","a+");
  	if (pFile!=NULL)
 	 {
  	  fprintf (pFile,"%d/%d/%d",dia,mes,ano);
	  fprintf (pFile," | %d:%d:%d",hora,min,sec);
	  fprintf (pFile," | %s\n",buffer); 
	  fclose (pFile);
	}

	if(flag==0)
	{
	strcpy(novo_buffer,"Comando nao existente");
	}
  
      bytes_enviados = sendto(socket_servidor, novo_buffer,MAX_SIZE_BUFFER, 0, (struct sockaddr *)&cliente, tamanho_cliente);	
	
  }

  close(socket_servidor);  

  system("clear");

  return 0;
} 
