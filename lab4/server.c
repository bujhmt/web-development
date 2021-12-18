#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fcgi_config.h"
#include "fcgi_stdio.h"

extern char **Environment;

void readFile(const char *path)
{
    FILE *file = fopen(path, "r");

    char *line = NULL;
    size_t linesize = 0;

    while (getline(&line, &linesize, file) != -1)
        printf("%s", line);

    free(line);
    fclose(file);
}

int main()
{
    char **env = Environment;

    while (FCGI_Accept() >= 0)
    {
        char *contentLength = getenv("CONTENT_LENGTH");
        char *documentURI = getenv("DOCUMENT_URI");

        if (contentLength != NULL)
        {
            printf("Content-type: text/html\r\n");
        }

        if (strcmp(documentURI, "/") == 0)
        {
            readFile("./pages/index.html");
        }
        else if (strcmp(documentURI, "/echo") == 0)
        {
            printf("<a href=\"/~kp9223/fcgi/\">Main page</a><br><br>");

            printf("<code>");

            for (; *env != NULL; env++)
            {
                printf("%s\n", *env);
            }

            printf("</code><br>\n");
        }
        else
        {
            readFile("./pages/404.html");
        }
    }

    return 0;
}