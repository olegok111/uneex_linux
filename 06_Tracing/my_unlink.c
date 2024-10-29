#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

typedef int (*unlink_type)(const char*);

int unlink(const char* pathname) {
    int status = 0;

    if (strstr(pathname, "PROTECT") == NULL) {
        unlink_type real_unlink = (unlink_type) dlsym(RTLD_NEXT, "unlink");
        status = real_unlink(pathname);
    }

    return status;
}
