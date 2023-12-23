#include "system.h"

char** sys_get_ssids()
{
        char** ssids = malloc(MAX_NETWORKS * sizeof(char*));

        char buff[256];

        FILE* proc = popen("nmcli -f ssid device wifi list | tail -n +2", "r");
        if (proc == NULL)
        {
                printf("Error running command\n");
                return ssids;
        }

        while (fgets(buff, sizeof buff, proc) != NULL)
        {
                printf("WUD test: %s\n", buff);
        }

        free(proc);

        return ssids;
}

