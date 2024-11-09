#include <rhash.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#ifdef UNEEX_READLINE
#include <readline/readline.h>
#endif

int main(int argc, char* argv[]) {
    int hash_algo;
    unsigned char digest[64];
    char output[130];
    int res;
    char *cmd = NULL, *cmd_token = NULL;

    rhash_library_init();

    while (1) {
#ifdef UNEEX_READLINE
        if ((cmd = readline(">")) == NULL) {
            return 0;
        }
#else
        putc('>', stdout);

        size_t line_len = 0;
        if (getline(&cmd, &line_len, stdin) == -1) {
            free(cmd);
            return 0;
        }
#endif
        cmd_token = strtok(cmd, " ");
        if (!strcasecmp(cmd_token, "md5")) {
            hash_algo = RHASH_MD5;
        } else if (!strcasecmp(cmd_token, "sha1")) {
            hash_algo = RHASH_SHA1;
        } else if (!strcasecmp(cmd_token, "tth")) {
            hash_algo = RHASH_TTH;
        } else {
            fprintf(stderr, "Unsupported hash algo: %s\n", cmd_token);
            free(cmd);
            return 1;
        }

        cmd_token = strtok(NULL, " \n");
        if (cmd_token == NULL) {
            puts("Invalid command");
        } else {
            if (cmd_token[0] == '"') {
                char* s = cmd_token;
                res = rhash_msg(hash_algo, s, strlen(s), digest);
            } else {
                char* filepath = cmd_token;
                res = rhash_file(hash_algo, filepath, digest);
            }
            if (res < 0) {
                fprintf(stderr, "LibRHash error: %s: %s\n", cmd_token, strerror(errno));
                free(cmd);
                return 1;
            }

            rhash_print_bytes(output, digest, rhash_get_digest_size(hash_algo),
                (RHPR_HEX | RHPR_UPPERCASE));
            printf("hash: %s\n", output);
        }

        free(cmd);
    }

    return 0;
}
