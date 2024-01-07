#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "buffer.h"
#include "pos_sockets/char_buffer.h"
#include "pos_sockets/active_socket.h"
#include "pos_sockets/passive_socket.h"

typedef struct vzor{
    char* vzor;
} VZOR;

_Bool vzor_try_deserialize(struct vzor* vzor, struct char_buffer* buf) {
    char *str = buf->data;
    if(str != NULL) {
        sscanf(buf->data, "%s",

               vzor->vzor);
        return true;
    }
    else {
        return false;
    }
}

GENERATE_BUFFER(struct vzor, vzor)
typedef struct thread_data {
    struct buffer_vzor buf;
    pthread_mutex_t mutex_write;
    pthread_cond_t is_writing;

    short port;
    ACTIVE_SOCKET* my_socket;
} THREAD_DATA;

void zapis(struct vzor *pVzor);

void thread_data_init(struct thread_data* data, long long replications_count, int buffer_capacity,
                      short port, ACTIVE_SOCKET* my_socket) {
    buffer_vzor_init(&data->buf, buffer_capacity);
    pthread_mutex_init(&data->mutex_write, NULL);
    pthread_cond_init(&data->is_writing, NULL);

    data->port = port;
    data->my_socket = my_socket;
}

void thread_data_destroy(struct thread_data* data) {
    buffer_vzor_destroy(&data->buf);
    pthread_mutex_destroy(&data->mutex_write);
    pthread_cond_destroy(&data->is_writing);

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
_Bool try_get_client_vzor(struct active_socket* my_sock, struct vzor* vzor) {
    _Bool result = false;
    CHAR_BUFFER r_buf;
    char_buffer_init(&r_buf);

    if(active_socket_try_get_read_data(my_sock, &r_buf)) {
        if(r_buf.size > 0) {
            if(active_socket_is_end_message(my_sock, &r_buf)) {
            } else if (vzor_try_deserialize(vzor, &r_buf)) {
                result = true;
            } else {
                printf("Klient poslal spravu v zlom formate\ndata: %s\n", r_buf.data);
            }
        }
    }
    char_buffer_destroy(&r_buf);
    return result;
}
int pocetRiadkovVSubore() {
    FILE * p_soubor = fopen("zoznam_vzorov.txt", "r");
    int pocet = 0;
    if (p_soubor != NULL)
    {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), p_soubor) != NULL)
        {
            pocet++;
        }
    }
    fclose("zoznam_vzorov.txt");
    return pocet;
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
                txt = buffer - '\n';
                CHAR_BUFFER charBuffer;
                char_buffer_init(&charBuffer);
                char_buffer_append(&charBuffer,txt, sizeof(txt));
                active_socket_write_data(data->my_socket,&charBuffer);
                break;
            }

        }
    }
    fclose("zoznam_vzorov.txt");
}
void* consume(void* thread_data) {
    struct thread_data *data = (struct thread_data *) thread_data;
    struct vzor vzor;
    if (data->my_socket != NULL) {
        if (try_get_client_vzor(data->my_socket, &vzor)) {
                if (strcmp(vzor.vzor, "daj") == 0) {
                    if (!pthread_cond_wait(&data->is_writing, &data->mutex_write)) {
                        int pocet = pocetRiadkovVSubore();
                        const char * txt = pocet+"";
                        CHAR_BUFFER charBuffer;
                        char_buffer_init(&charBuffer);
                        char_buffer_append(&charBuffer, txt, sizeof(txt));
                        active_socket_write_data(data->my_socket, &charBuffer);
                    }
                } else if (strcmp(vzor.vzor, "citaj") == 0) {
                    if (!pthread_cond_wait(&data->is_writing, &data->mutex_write)) {
                        citaj(data, (int)vzor.vzor[0]);
                    }
                } else {
                    pthread_mutex_lock(&data->mutex_write);
                    pthread_cond_signal(&data->is_writing);
                    zapis(&vzor);
                    pthread_mutex_unlock(&data->mutex_write);


                }
        }

    }
    return NULL;
}

void zapis(struct vzor *pVzor) {
    FILE * p_soubor = fopen("zoznam_vzorov.txt", "a");
    if (p_soubor != NULL)
    {
        const char* txt = pVzor->vzor + '\n';
        fprintf(p_soubor, txt );
    }
}

int main() {
    pthread_t th_receive;
    struct thread_data data;
    struct active_socket my_socket;
    active_socket_init(&my_socket);
    thread_data_init(&data, 100000, 10, 12289, &my_socket);
    pthread_create(&th_receive, NULL, process_client_data, &data);
    pthread_join(th_receive, NULL);

    thread_data_destroy(&data);
    active_socket_destroy(&my_socket);
    return 0;
}
