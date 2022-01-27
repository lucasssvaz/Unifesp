//
//	Lucas Saavedra Vaz - 120503
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_REQUEST_LEN 1000
#define METHOD_GET "GET"
#define METHOD_CREATE "CREATE"
#define METHOD_REMOVE "REMOVE"
#define METHOD_APPEND "APPEND"

#define RESP_SUCCESS_OK "\n200 OK\n"
#define RESP_SUCCESS_CREATED "\n201 Created\n"
#define RESP_ERROR_NOTIMP "\n501 Not Implemented\n"
#define RESP_ERROR_BADREQ "\n400 Bad Request\n"
#define RESP_ERROR_INTERR "\n500 Internal Server Error\n"

#define BLOCK_SIZE 4096

int sock;
struct sockaddr_in sock_addr;
socklen_t addr_size;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int *th_run;

void proc_req(int sock, char *req)
{
	char req_method[64] = "", req_file[256] = "", req_content[BLOCK_SIZE] = "";
	char *current_str;
	int file_fd, read_bytes;
	unsigned char file_buf[BLOCK_SIZE];

	bzero(file_buf,BLOCK_SIZE);

	printf("Getting method...\n");
	current_str = strtok(req, " \n\r\t");

	if (current_str == NULL)
	{
		printf("Bad request recieved.\n");
		send(sock, RESP_ERROR_BADREQ, strlen(RESP_ERROR_BADREQ), 0);
		return;
	}

	strncpy(req_method, current_str, 64);

	if (strcmp(req_method, METHOD_APPEND) == 0)
	{
		printf("Getting content...\n");
		current_str = strtok(NULL, "\"");

		if (current_str == NULL)
		{
			printf("Bad request recieved.\n");
			send(sock, RESP_ERROR_BADREQ, strlen(RESP_ERROR_BADREQ), 0);
			return;
		}

		strncpy(req_content, current_str, BLOCK_SIZE);
	}

	printf("Getting filename...\n");
	current_str = strtok(NULL, " \n\t\r");
	
	if (current_str == NULL)
	{
		printf("Bad request recieved.\n");
		send(sock, RESP_ERROR_BADREQ, strlen(RESP_ERROR_BADREQ), 0);
		return;
	}
	
	strncpy(req_file, current_str, 256);

	printf("Request recieved:\nMethod: %s\nContent: %s\nFilename: %s\n", req_method, req_content, req_file);

	if (strcmp(req_method, METHOD_GET) == 0)
	{
		if ((file_fd = open(req_file, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
			perror("Open (Get)");
			printf("File could not be opened\n");
			send(sock, RESP_ERROR_INTERR, strlen(RESP_ERROR_INTERR), 0);
			return;
		}

		do
		{
			read_bytes = read(file_fd, file_buf, BLOCK_SIZE);
			send(sock, file_buf, read_bytes, 0);
		} while (read_bytes > 0);

		close(file_fd);

		send(sock, RESP_SUCCESS_OK, strlen(RESP_SUCCESS_OK), 0);
	}
	else if (strcmp(req_method, METHOD_CREATE) == 0)
	{

		if ((file_fd = open(req_file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
			perror("Open (Create)");
			printf("File could not be created\n");
			send(sock, RESP_ERROR_INTERR, strlen(RESP_ERROR_INTERR), 0);
			return;
		}

		close(file_fd);

		send(sock, RESP_SUCCESS_CREATED, strlen(RESP_SUCCESS_CREATED), 0);
	}
	else if (strcmp(req_method, METHOD_REMOVE) == 0)
	{

		if (remove(req_file) == -1)
		{
			perror("Remove");
			printf("File could not be removed\n");
			send(sock, RESP_ERROR_INTERR, strlen(RESP_ERROR_INTERR), 0);
			return;
		}

		send(sock, RESP_SUCCESS_OK, strlen(RESP_SUCCESS_OK), 0);
	}
	else if (strcmp(req_method, METHOD_APPEND) == 0)
	{

		if ((file_fd = open(req_file, O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
			perror("Open (Append)");
			printf("File could not be opened\n");
			send(sock, RESP_ERROR_INTERR, strlen(RESP_ERROR_INTERR), 0);
			return;
		}

		write(file_fd, req_content, BLOCK_SIZE);

		close(file_fd);

		send(sock, RESP_SUCCESS_OK, strlen(RESP_SUCCESS_OK), 0);
	}
	else
	{
		send(sock, RESP_ERROR_NOTIMP, strlen(RESP_ERROR_NOTIMP), 0);
	}
}

void* thread_server(void *arg)
{
	int id = *((int *) arg);
	th_run[id] = 1;

	int th_socket;
	struct sockaddr_in client_addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);
	char sock_buf[MAX_REQUEST_LEN];

	pthread_mutex_lock(&lock);

	if ((th_socket = accept(sock, (struct sockaddr *) &client_addr, &addr_size)) == -1)
	{
		perror("Accept");
		pthread_exit(NULL);
	}

	pthread_mutex_unlock(&lock);

	printf("Connected to client on %s:%d.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

	bzero(sock_buf, MAX_REQUEST_LEN);

	if (recv(th_socket, sock_buf, MAX_REQUEST_LEN, 0) > 0)
		proc_req(th_socket, sock_buf);

	close(th_socket);

	th_run[id] = 0;
	pthread_exit(NULL);
}

int main (int argc, char** argv)
{

	if (argc != 4)
	{
		printf("Usage: %s <port> <num_threads> <max_conn>\n", argv[0]);
		return 0;
	}

	int sv_port = atoi(argv[1]);
	int num_threads = atoi(argv[2]);
	int max_conn = atoi(argv[3]);

	pthread_t threads[num_threads];
	th_run = (int *) calloc(num_threads, sizeof(int));

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		perror("Socket");
		return 0;
	}

	sock_addr.sin_port = htons(sv_port);
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr *) &sock_addr, sizeof(struct sockaddr_in)) == -1)
	{
		perror("Bind");
		return 0;
	}

	if (listen(sock, max_conn) == -1)
	{
		perror("Listen");
		return 0;
	}

	while(1)
	{
		int i;
		for (i = 0; i < num_threads; i++)
			if (th_run[i] == 0)
				if (pthread_create(&threads[i], NULL, thread_server, (void *) &i) != 0)
					perror("Thread create");
	}

	close(sock);
	pthread_exit(NULL);

	return 0;
}