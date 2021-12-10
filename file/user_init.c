#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int main()
{

    char *buf = malloc(100);
    FILE *fd = fopen("user.bin", "wb");
    sprintf(buf,"username:admin\npassword:123456\n");
    int size = fwrite(buf, strlen(buf), 1, fd);
    free(buf);
    fclose(fd);
    return 0;
}
