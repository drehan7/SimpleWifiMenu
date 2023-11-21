#ifndef NETWORK_H
#define NETWORK_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_NETWORKS 50
// #define DEBUG 0

typedef char* SSID;

typedef struct {
        SSID* ssids;
        size_t count;
        size_t page;
} SSIDS;

typedef struct {
        char* bssid;
        SSID ssid;
        unsigned int channel;
        unsigned int rate;
        unsigned int signal;
        char* security;
} Network;


SSIDS* get_ssids(void);

char* get_connected_ssid(void);

#endif //NETWORK_H
