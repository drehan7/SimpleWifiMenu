#include <stdlib.h>

int main() {
    // char* command = "nmcli device wifi list";
    // system(command);

    FILE* fp;
    int status = 0;
    char path[256];

    fp = popen("nmcli device wifi list", "r");

    while (fgets(path, 256, fp) != NULL)
    {
        printf("%s", path);
    }

    status = pclose(fp);
    printf("\nStatus: %d\n", status);

}

