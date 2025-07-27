#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    openlog(NULL, 0, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments: expected 2, got %d", argc - 1);
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    const char *str = argv[2];

    FILE *fp = fopen(filepath, "w");
    if (!fp) {
        syslog(LOG_ERR, "Failed to open file: %s", filepath);
        return 1;
    }

    fprintf(fp, "%s", str);
    fclose(fp);

    syslog(LOG_DEBUG, "Writing %s to %s", str, filepath);
    closelog();

    return 0;
}