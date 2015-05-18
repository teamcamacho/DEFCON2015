#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
 
#define MAXRCVLEN 1024

int _connect(void);
int read_data(int, char *);
void parse_regs(char *);
void parse_inst(char *, char *);

int main(int argc, char *argv[])
{
    int len, sock;
    char buff[MAXRCVLEN + 1];
    char shellcode[256];

    sock = _connect();

    len = read_data(sock, buff);
    printf("Received %s (%d bytes).\n", buff, len);

    parse_regs(buff);

    len = read_data(sock, buff);
    printf("Received %s (%d bytes).\n", buff, len);

    parse_inst(buff, shellcode);

    int (*func)();

    func = (int (*)()) shellcode;

    (int)(*func)();


    close(sock);

    return EXIT_SUCCESS;
}

void parse_inst(char * buff, char * shellcode) {
    char * str;
    char * prep;
    char * inst;
    char slen[3];
    int len;

    str = strstr(buff, "About to send");

    prep = strsep(&str, "\n");
    inst = strsep(&str, "\n");

    slen[0] = prep[14];
    slen[1] = prep[15];
    slen[2] = '\0';

    len = atoi(slen);

    //printf("len: %d\n", len);
    //printf("inst: %s\n", inst);

    int i;
    char x;
    for(i=0; i < len; i++) {
        x = inst[i];
        printf("%02X ", x & 0xff);
    }
    printf("\n");
}

void parse_regs(char * buff) {
    char * reg;
    char * val;
    char * tofree;
    char * string;
    char * line;

    register int rax asm("rax");
    register int rbx asm("rbx");
    register int rcx asm("rcx");
    register int rdx asm("rdx");
    register int rsi asm("rsi");
    register int rdi asm("rdi");
    register int r8 asm("r8");
    register int r9 asm("r9");
    register int r10 asm("r10");
    register int r11 asm("r11");
    register int r12 asm("r12");
    register int r13 asm("r13");
    register int r14 asm("r14");
    register int r15 asm("r15");

    string = strdup(buff);

    if (string != NULL) {
        tofree = string;

        while ((line = strsep(&string, "\n")) != NULL) {
            if (strstr(line, "Initial Register State") != NULL) continue;

            reg = strsep(&line, "=");
            val = strsep(&line, "=");
            
            if (val == NULL) break;

            printf("register: %s, value: %s\n", reg, val);

            if (strcmp(reg, "rax")==0) rax = *val;
            if (strcmp(reg, "rbx")==0) rbx = *val;
            if (strcmp(reg, "rcx")==0) rcx = *val;
            if (strcmp(reg, "rdx")==0) rdx = *val;
            if (strcmp(reg, "rsi")==0) rsi = *val;
            if (strcmp(reg, "rdi")==0) rdi = *val;
            if (strcmp(reg, "r8")==0)  r8 = *val;
            if (strcmp(reg, "r9")==0)  r9 = *val;
            if (strcmp(reg, "r10")==0) r10 = *val;
            if (strcmp(reg, "r11")==0) r11 = *val;
            if (strcmp(reg, "r12")==0) r12 = *val;
            if (strcmp(reg, "r13")==0) r13 = *val;
            if (strcmp(reg, "r14")==0) r14 = *val;
            if (strcmp(reg, "r15")==0) r15 = *val;

        }

        free(tofree);
    }
}

int _connect(void) {
    int sock;
    struct sockaddr_in dest;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr("52.4.66.84");
    dest.sin_port = htons(9999);
    connect(sock, (struct sockaddr *)&dest, sizeof(struct sockaddr));

    return sock;
}


int read_data(int sock, char * buff) {
    int len;

    len = recv(sock, buff, MAXRCVLEN, 0);

    buff[len] = '\0';

    return len;
}

