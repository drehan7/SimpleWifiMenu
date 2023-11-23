#include "network.h"

SSIDS* get_ssids(void)
{

        size_t count = 0;
        SSIDS* ssids_t = malloc(1 * sizeof(SSIDS));

        char** ssids = malloc(MAX_NETWORKS * sizeof(char*));
        char* command = "nmcli -f ssid device wifi list | tail -n +2";
        FILE* proc = popen(command, "r");
                #ifdef DEBUG
                        printf("running command: %s\n", command);
                #endif
        if (proc == NULL)
        {
                printf("Error running command\n");
                return ssids_t;
        }

        char* buff[80];
        while (fgets(buff, sizeof buff, proc) != NULL)
        {
                if (strstr(buff, "--") != NULL) continue;
                size_t l = strlen(buff);
                buff[l - 1] = '\0';
                ssids[count] = malloc(l * sizeof(char));
                strcpy(ssids[count], buff);
                count++;
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

        return ssids_t;
}

void refresh_ssids(SSIDS* s, size_t count)
{
        SSIDS* new_ssids = get_ssids();
        if (new_ssids == NULL) return;

        count = (count > s->count) ? s->count : count;

        for (size_t i = 0; i < count; ++i)
        {
                s->ssid_list[i] = new_ssids->ssid_list[i];
        }

        free(new_ssids);
}

char* get_connected_ssid()
{
        return "Something";
}
