#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    const char* haystack = "GET /cat.jpg HTTP/1.1\r\n";
    char* needle = strstr(haystack, "\r\n");
    
    const char *cursor = needle;
    const char *space1 = strchr(haystack, ' ');
    if (space1 == NULL)
    {
        return 0;
    }
    const char *space2 = strrchr(haystack, ' ');
    if (space2 == NULL || space2 == space1)
    {
        return 0;
    }


    char method[space1 - haystack + 1];
    strncpy(method, haystack, space1 - haystack);
    method[space1 - haystack] = '\0';

    char request_target[space2 - space1];
    strncpy(request_target, space1 + 1, space2 - space1 - 1);
    request_target[space2 - space1 - 1] = '\0';

    const char *queryStart = strchr(request_target, '?');
    const char *targetStart = request_target;
    const char *targetEnd = &request_target[space2 - space1 - 1];
    char query[space2 - space1];
    char absolute_path[space2 - space1];
    
    if (queryStart == NULL)
    {
        strncpy(absolute_path, targetStart, targetEnd - targetStart + 1);
        absolute_path[space2 - space1 - 1] = '\0';
        query[0] = '\0';
    }
    else
    {
        strncpy(absolute_path, space1 + 1, queryStart - space1 - 1);
        absolute_path[queryStart - space1 - 1] = '\0';
        
        strncpy(query, queryStart, space2 - queryStart);
        query[space2 - queryStart] = '\0';
    }

    char http_version[cursor - space2];
    strncpy(http_version, space2 + 1, cursor - space2 - 1);
    http_version[cursor - space2 - 1] = '\0';
    
    char path[4096] = {};
    strcat(path, "/home/jharvard/Dropbox/pset6/public");
    strcat(path, absolute_path);
    
    char *extensionStart = strchr(haystack, '.');
    char extension[space2 - space1];
    if (queryStart == NULL)
    {
        strncpy(extension, extensionStart, space2 - extensionStart);
        extension[space2 - extensionStart] = '\0';
    }
    else
    {
        strncpy(extension, extensionStart, queryStart - extensionStart);
        extension[queryStart - extensionStart] = '\0';
    }
    
    
    printf("%d\n", access(path, F_OK));
    printf("%d\n", access(path, R_OK));

    return 0;
}

