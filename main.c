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


typedef struct thread_data {
    short port;
    pthread_mutex_t zapis_mutex;
    PASSIVE_SOCKET* passiveSocket;
    int pocetPripojenych;
} THREAD_DATA;
typedef struct thread_data2 {
    THREAD_DATA * threadData;
    ACTIVE_SOCKET activeSocket;
} TREAD_DATA2;
void zapis(char * string);

void thread_data_init(struct thread_data* data, int buffer_capacity,
                      short port,PASSIVE_SOCKET* passiveSocket) {
    data->port = port;
    data->passiveSocket = passiveSocket;
    pthread_mutex_init(&data->zapis_mutex,NULL);
    data->pocetPripojenych =0;
}

void thread_data_destroy(struct thread_data* data) {
    data->port = 0;
    data->passiveSocket = NULL;
    pthread_mutex_destroy(&data->zapis_mutex);
    data->pocetPripojenych =0;
}

void* consume(void* thread_data);
void* read_active_socket(void* thread_data) {
    TREAD_DATA2 *data = (TREAD_DATA2 *)thread_data;
    pthread_t spracuj;
    pthread_create(&spracuj,NULL, consume,data);
    active_socket_start_reading(&data->activeSocket);
    pthread_join(spracuj,NULL);
    active_socket_destroy(&data->activeSocket);
    free(data);
    return NULL;
}

void* process_client_data(void* thread_data) {
    THREAD_DATA *data = (THREAD_DATA *)thread_data;
    passive_socket_start_listening(data->passiveSocket, data->port);
    while(passive_socket_is_listening(data->passiveSocket)) {
        TREAD_DATA2* treadData2 = malloc(sizeof (struct thread_data2));
        treadData2->threadData = data;
        active_socket_init(&treadData2->activeSocket);
        passive_socket_wait_for_client(data->passiveSocket, &treadData2->activeSocket);
        data->pocetPripojenych++;
        pthread_t  client;
        pthread_create(&client, NULL,read_active_socket,treadData2);
        pthread_detach(client);
    }
    return NULL;
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

void citaj(struct thread_data2* data , int riadok){

    FILE * p_soubor = fopen("zoznam_vzorov.txt", "r");
    int pocet = 0;
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
                char_buffer_append(&charBuffer,buffer, strlen(buffer));
                active_socket_write_data(&data->activeSocket,&charBuffer);
                char_buffer_destroy(&charBuffer);
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
    struct thread_data2 *data = (struct thread_data2 *) thread_data;
    _Bool ukonceny = false;
    while (!ukonceny) {
        struct char_buffer vzor;
        char_buffer_init(&vzor);

        while (!active_socket_try_get_read_data(&data->activeSocket, &vzor)) {
            sleep(2);
        }
        char *string = vzor.data;
        if (strcmp(string, "download") == 0) {
            int pocet = pocetRiadkovVSubore();
            char txt[20] = {0};
            sprintf(txt, "%d", pocet);
            CHAR_BUFFER charBuffer;
            char_buffer_init(&charBuffer);
            char_buffer_append(&charBuffer, txt, strlen(txt));
            active_socket_write_data(&data->activeSocket, &charBuffer);
            char_buffer_destroy(&charBuffer);
        } else if (isNumeric(string)) {
            int cisloRiadku = atoi(string);
            citaj(data, cisloRiadku);
        } else if (strcmp(string, data->activeSocket.end_message) == 0) {
            active_socket_stop_reading(&data->activeSocket);
            ukonceny = true;
            data->threadData->pocetPripojenych--;
            if (data->threadData->pocetPripojenych == 0) {
                passive_socket_stop_listening(data->threadData->passiveSocket);
            }
        } else {
            pthread_mutex_lock(&data->threadData->zapis_mutex);
            zapis(string);
            pthread_mutex_unlock(&data->threadData->zapis_mutex);
        }

    char_buffer_destroy(&vzor);
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
    PASSIVE_SOCKET p_socket;
    passive_socket_init(&p_socket);
    thread_data_init(&data, 10, 12389,&p_socket);
    pthread_create(&th_receive, NULL, process_client_data, &data);
    pthread_join(th_receive, NULL);

    thread_data_destroy(&data);
    passive_socket_destroy(&p_socket);
    return 0;
}