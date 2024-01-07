#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "buffer.h"
#include "pos_sockets/char_buffer.h"
#include "pos_sockets/active_socket.h"
#include "pos_sockets/passive_socket.h"

typedef struct vzor{
    char* vzor;
};


GENERATE_BUFFER(struct vzor, vzor)
typedef struct thread_data {
    struct buffer_vzor buf;
    short port;
    ACTIVE_SOCKET* my_socket;
} THREAD_DATA;

void zapis(char * string);

void thread_data_init(struct thread_data* data, int buffer_capacity,
                      short port, ACTIVE_SOCKET* my_socket) {
    buffer_vzor_init(&data->buf, buffer_capacity);
    data->port = port;
    data->my_socket = my_socket;
}

void thread_data_destroy(struct thread_data* data) {
    buffer_vzor_destroy(&data->buf);
    data->port = 0;
    data->my_socket = NULL;
}

void* consume(void* thread_data);
void* read_active_socket(void* thread_data) {
    THREAD_DATA *data = (THREAD_DATA *)thread_data;
    active_socket_start_reading(data->my_socket);
    consume(data);
    return NULL;
}

void* process_client_data(void* thread_data) {
    THREAD_DATA *data = (THREAD_DATA *)thread_data;
    PASSIVE_SOCKET p_socket;
    passive_socket_init(&p_socket);
    passive_socket_start_listening(&p_socket, data->port);
    while(passive_socket_is_listening(&p_socket)) {
        passive_socket_wait_for_client(&p_socket, data->my_socket);
        pthread_t  client;
        pthread_create(&client, NULL,read_active_socket,data);
        pthread_join(client, NULL);
    }
    passive_socket_stop_listening(&p_socket);
    passive_socket_destroy(&p_socket);
    return NULL;
}

void try_get_client_vzor(struct active_socket* my_sock, struct vzor* vzor) {
    CHAR_BUFFER r_buf;
    char_buffer_init(&r_buf);

    if(active_socket_try_get_read_data(my_sock, &r_buf)) {
        if(r_buf.size > 0) {
            if(active_socket_is_end_message(my_sock, &r_buf)) {
            } else {
                vzor->vzor  = r_buf.data;
            }
        }
    }
    char_buffer_destroy(&r_buf);
}

int pocetRiadkovVSubore() {
    FILE * p_soubor = fopen("cmake-build-debug-frios2/zoznam_vzorov.txt", "r");
    int pocet = 0;
    if (p_soubor != NULL)
    {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), p_soubor) != NULL)
        {
            pocet++;
        }
        fclose(p_soubor);
    }

    return pocet;
}

void removeNewLine(char * string) {
    size_t length = 0;

    while (string[length] != '\0') {
        if (string[length] == '\n') {
            string[length] = '\0';
            break;
        }
        ++length;
    }

}

void citaj(struct thread_data* data , int riadok){

    FILE * p_soubor = fopen("zoznam_vzorov.txt", "r");
    int pocet = 0;
    char* txt;
    if (p_soubor != NULL)
    {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), p_soubor) != NULL)
        {
            pocet++;
            if(pocet == riadok){
                removeNewLine(buffer);
                CHAR_BUFFER charBuffer;
                char_buffer_init(&charBuffer);
                char_buffer_append(&charBuffer,txt, sizeof(txt));
                active_socket_write_data(data->my_socket,&charBuffer);
                break;
            }

        }
        fclose(p_soubor);
    }
}

size_t custom_strlen(const char * str) {
    size_t length = 0;

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

bool isNumeric(const char* string) {
    size_t length = 0;

    while (string[length] != '\0') {
        if (!isdigit(string[length])) {
            return false;
        }
        ++length;
    }

    return true;
}

void* consume(void* thread_data) {
    struct thread_data *data = (struct thread_data *) thread_data;

    char * string = data->my_socket->received_data.first->data.data;

    if (data->my_socket != NULL) {
            if (strcmp(string, "download") == 0) {
                    int pocet = pocetRiadkovVSubore();
                    const char *txt = "" + pocet;
                    CHAR_BUFFER charBuffer;
                    char_buffer_init(&charBuffer);
                    char_buffer_append(&charBuffer, txt, custom_strlen(txt));
                    active_socket_write_data(data->my_socket, &charBuffer);
            }
            else if (isNumeric(string)) {
                int cisloRiadku = atoi(string);
                citaj(data, cisloRiadku);
            } else {
                zapis(string);
            }

    }

    return NULL;
}

void zapis(char * string) {
    FILE * p_soubor = fopen("zoznam_vzorov.txt", "a");

    if (p_soubor != NULL)
    {
        fprintf(p_soubor, "%s", string);
        fprintf(p_soubor, "\n");
        if(fclose(p_soubor) == EOF) printf("Subor sa nepodarilo uzavrieť");
    }
}

int main() {
    pthread_t th_receive;
    struct thread_data data;
    struct active_socket my_socket;
    active_socket_init(&my_socket);
    thread_data_init(&data, 10, 12389, &my_socket);
    pthread_create(&th_receive, NULL, process_client_data, &data);
    pthread_join(th_receive, NULL);

    thread_data_destroy(&data);
    active_socket_destroy(&my_socket);
    return 0;
}