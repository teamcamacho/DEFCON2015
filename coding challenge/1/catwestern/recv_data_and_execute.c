#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
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
int read_data(int, uint8_t *);
void parse_regs(uint8_t *);
void parse_inst(uint8_t *, uint8_t *);

int main(int argc, uint8_t *argv[])
{
    int len, sock;
    uint8_t buff[MAXRCVLEN + 1];
    uint8_t shellcode[256];

    sock = _connect();

    len = read_data(sock, buff);
    printf("Received %s (%d bytes).\n", buff, len);

    parse_regs(buff);

    len = read_data(sock, buff);
    printf("Received %s (%d bytes).\n", buff, len);

    parse_inst(buff, shellcode);

    uint8_t * addr = mmap(NULL, len, PROT_READ|PROT_EXEC |PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0); 
    if (addr == MAP_FAILED)
    {
        printf("mmap fuck up. \n");
    }
    memcpy(addr,shellcode,len);
    int (*func)();

    func = (int (*)()) addr;

    (int)(*func)();


    close(sock);

    return EXIT_SUCCESS;
}

void parse_inst(uint8_t * buff, uint8_t * shellcode) {
    uint8_t * str;
    uint8_t * prep;
    uint8_t * inst;
    uint8_t slen[3];
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
    uint8_t x;
    for(i=0; i < len; i++) {
        x = inst[i];
        printf("%02X ", x & 0xff);
    }
    printf("\n");
}

void parse_regs(uint8_t * buff) {
    uint8_t * reg;
    uint8_t * val;
    uint8_t * tofree;
    uint8_t * string;
    uint8_t * line;

    register uint64_t rax asm("rax");
    register uint64_t rbx asm("rbx");
    register uint64_t rcx asm("rcx");
    register uint64_t rdx asm("rdx");
    register uint64_t rsi asm("rsi");
    register uint64_t rdi asm("rdi");
    register uint64_t r8 asm("r8");
    register uint64_t r9 asm("r9");
    register uint64_t r10 asm("r10");
    register uint64_t r11 asm("r11");
    register uint64_t r12 asm("r12");
    register uint64_t r13 asm("r13");
    register uint64_t r14 asm("r14");
    register uint64_t r15 asm("r15");

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


int read_data(int sock, uint8_t * buff) {
    int len;

    len = recv(sock, buff, MAXRCVLEN, 0);

    buff[len] = '\0';

    return len;
}

