#ifndef NETWORK_H
#define NETWORK_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_NETWORKS 50

typedef struct {
        char** ssid_list;
        size_t count;
        size_t page;
} SSIDS;

typedef struct {
        char* bssid;
        char* ssid;
        unsigned int channel;
        unsigned int rate;
        unsigned int signal;
        char* security;
} Network;


SSIDS* get_ssids(void);

// Network get_network_info(char* ssid);

void refresh_ssids(SSIDS* state, size_t count);
char* get_connected_ssid(void); // UNIMPL

int s_find(char** set, size_t set_l, char* f);

#endif //NETWORK_H
