#include "network.h"

SSIDS* get_ssids(void)
{

        size_t count = 0;
        SSIDS* ssids_t = malloc(1 * sizeof(SSIDS));

        char** ssids = malloc(MAX_NETWORKS * sizeof(char*));
        char* command = "nmcli -f ssid device wifi list | tail -n +2 | tail -n 49";
        FILE* proc = popen(command, "r");
                #ifdef DEBUG
                        printf("running command: %s\n", command);
                #endif
        if (proc == NULL)
        {
                printf("Error running command\n");
                return ssids_t;
        }

        char buff[80];
        // TODO:
        //      SSIDS may repeat due to different channel OR signal
        //      Include channel if mult show up
        while (fgets(buff, sizeof buff, proc) != NULL)
        {
                if (strstr(buff, "--") != NULL) continue; // Null entry
                size_t l = strlen(buff);
                buff[l - 1] = '\0';
                // if (!s_find(ssids, count, buff))
                // {
                        ssids[count] = malloc(l * sizeof(char));
                        strcpy(ssids[count], buff);
                        count++;
                        // printf("ADDED SSID: %s\n", buff);
                // }
                if (count >= MAX_NETWORKS) break;

                #ifdef DEBUG
                        printf("Network: %s\n", buff);
                #endif

                // TODO: next page or scrollable solution ???
        }
        printf("Network size: %ld\n", count);
        ssids_t->count = count;
        ssids_t->ssid_list = ssids;
        ssids_t->page = 0;

        // free(proc); free(command);

        return ssids_t;
}

// Network get_network_info(char* ssid)
// {
//         Network net;
//         char* command = "nmcli -f ssid device wifi list | tail -n +2 | tail -n 49";
//
//         return net;
// }

void refresh_ssids(SSIDS* s, size_t count)
{
        SSIDS* new_ssids = get_ssids();
        if (new_ssids == NULL) return;

        count = (count > s->count) ? s->count : count;

        for (size_t i = 0; i < count; ++i)
        {
                s->ssid_list[i] = new_ssids->ssid_list[i];
        }

}

int s_find(char** set, size_t set_l,  char* f)
{
        // printf("size: %ld\n", set_l);
        int found = 0;
        if (set_l == 0) return found;

        for (size_t i = 0; i < set_l; ++i)
        {
                // printf("i: %ld Set[i]: %s\n", i, (char*)set[i]);
                if (strcmp(set[i], f) != 0)
                {
                        found = 1;
                        break;
                }
        }
        return found;
}

char* get_connected_ssid()
{
        return "Something";
}
