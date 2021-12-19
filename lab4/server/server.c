#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include "fcgi_config.h"
#include "fcgi_stdio.h"

#define WRITE_FILE_CREATE_RULES 0644
#define LOG_FILE_NAME "logs.txt"

extern char **environ;

void sendHtml(char *path)
{
    printf("Content-type: text/html\r\n\r\n");
    int charIndex;
    FILE *file;
    file = fopen(path, "r");

    if (file)
    {
        while ((charIndex = getc(file)) != EOF)
            putchar(charIndex);
        fclose(file);
    }
}

void sendPiped(char *util)
{
    printf("Content-type: text/plain\r\n\r\n");
    FILE *fp;
    char buffer[128];
    fp = popen(util, "r");
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        printf("%s", buffer);
    }
    pclose(fp);
}

void throwError(char *message)
{
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(1);
}

char *getCurrentTime()
{
    time_t rawtime;
    time(&rawtime);
    struct tm currentTime = (*localtime(&rawtime));
    char *str = asctime(&currentTime);

    str[strlen(str) - 1] = '\0';

    return str;
}

int main()
{
    int logFileDescr = open(LOG_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, WRITE_FILE_CREATE_RULES);

    if (logFileDescr == -1)
    {
        throwError("Error while opening logs file");
    }

    char temp[100];
    sprintf(temp, "Server Started. PID: %d\n\n", getpid());
    write(logFileDescr, temp, strlen(temp));

    while (FCGI_Accept() >= 0)
    {
        char *contentLength = getenv("CONTENT_LENGTH");
        char *documentURI = getenv("DOCUMENT_URI");

        char logBuffer[200];
        sprintf(logBuffer, "[%s]\nNew request: '%s'. Content lenght: %s\n", getCurrentTime(), documentURI, contentLength);
        write(logFileDescr, logBuffer, strlen(logBuffer));

        if (strcmp(documentURI, "/") == 0)
        {
            sendHtml("./pages/index.html");
        }
        else if (strcmp(documentURI, "/echo") == 0)
        {
            char **env = environ;
            printf("Content-type: text/html\r\n\r\n");
            printf("<h1>ECHO</h1><br><a href=\"/~kp9223/fcgi/\">Main page</a><br><br>");

            printf("<pre>");

            for (; *env != NULL; env++)
            {
                printf("%s\n", *env);
            }

            printf("</pre><br>\n");
        }
        // lab 4.2
        else if (strcmp(documentURI, "/mpstat") == 0) {
            sendPiped("mpstat");
        }
        else if (strcmp(documentURI, "/iostat") == 0) {
            sendPiped("iostat");
        }
        else if (strcmp(documentURI, "/free") == 0) {
            sendPiped("free");
        }
        else
        {
            sendHtml("./pages/404.html");
        }
    }

    close(logFileDescr);
    return 0;
}
