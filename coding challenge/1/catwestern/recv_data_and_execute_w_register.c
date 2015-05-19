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
void parse_regs(uint8_t *, uint8_t *, char *);
int parse_inst(uint8_t *, uint8_t *);
void registers_to_str(char *);

int main(int argc, uint8_t *argv[])
{
    int inst_len, len, sock;
    uint8_t buff1[MAXRCVLEN + 1];
    uint8_t buff2[MAXRCVLEN + 1];
    uint8_t shellcode[256] = {0};
    char response[1024] = {0};

    sock = _connect();

    len = read_data(sock, buff1);
    printf("%s", buff1, len);

    len = read_data(sock, buff2);
    printf("%s", buff2, len);

    inst_len = parse_inst(buff2, shellcode);

    uint8_t * exec_buff = mmap(shellcode, inst_len, PROT_READ|PROT_EXEC |PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0); 
    if (exec_buff == MAP_FAILED)
    {
        printf("mmap fuck up. \n");
    }
    memcpy(exec_buff,shellcode,len);

    parse_regs(buff1, exec_buff, response);

    write(sock, response, strlen(response));

    len = read_data(sock, buff1);
    printf("%s", buff1, len);

    close(sock);

    return EXIT_SUCCESS;
}

int parse_inst(uint8_t * buff, uint8_t * shellcode) {
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

    char * rev_shellcode[256];

    int i;
    uint8_t x;
    for(i=0; i < len; i++) {
        x = inst[i];
        printf("%02X ", x & 0xff);
        shellcode[i] = inst[i];
        rev_shellcode[i] = inst[len-(1+i)];
    }
    printf("\n");
    
    FILE * fd = fopen("out.dat", "w");
    for(i=0;i < len; i++) {
        fprintf(fd, "%c", shellcode[i]);
    }
    close(fd);

    fd = fopen("out_rev.dat", "w");
    for(i=0;i < len; i++) {
        fprintf(fd, "%c", rev_shellcode[i]);
    }
    close(fd);


    return len;
}

void parse_regs(uint8_t * buff, uint8_t * exec_buff, char * response) {
    uint8_t * reg;
    uint8_t * val;
    uint8_t * tofree;
    uint8_t * string;
    uint8_t * line;

    register uint64_t rax __asm__("rax");
    register uint64_t rbx __asm__("rbx");
    register uint64_t rcx __asm__("rcx");
    register uint64_t rdx __asm__("rdx");
    register uint64_t rsi __asm__("rsi");
    register uint64_t rdi __asm__("rdi");
    register uint64_t r8 __asm__("r8");
    register uint64_t r9 __asm__("r9");
    register uint64_t r10 __asm__("r10");
    register uint64_t r11 __asm__("r11");
    register uint64_t r12 __asm__("r12");
    register uint64_t r13 __asm__("r13");
    register uint64_t r14 __asm__("r14");
    register uint64_t r15 __asm__("r15");

    string = strdup(buff);

    if (string != NULL) {
        tofree = string;

        while ((line = strsep(&string, "\n")) != NULL) {
            if (strstr(line, "Initial Register State") != NULL) continue;

            reg = strsep(&line, "=");
            val = strsep(&line, "=");
            
            if (val == NULL) break;

            uint64_t nval = strtoull(val, NULL, 16);

            if (strcmp(reg, "rax")==0) rax = nval;
            if (strcmp(reg, "rbx")==0) rbx = nval;
            if (strcmp(reg, "rcx")==0) rcx = nval;
            if (strcmp(reg, "rdx")==0) rdx = nval;
            if (strcmp(reg, "rsi")==0) rsi = nval;
            if (strcmp(reg, "rdi")==0) rdi = nval;
            if (strcmp(reg, "r8")==0)  r8 = nval;
            if (strcmp(reg, "r9")==0)  r9 = nval;
            if (strcmp(reg, "r10")==0) r10 = nval;
            if (strcmp(reg, "r11")==0) r11 = nval;
            if (strcmp(reg, "r12")==0) r12 = nval;
            if (strcmp(reg, "r13")==0) r13 = nval;
            if (strcmp(reg, "r14")==0) r14 = nval;
            if (strcmp(reg, "r15")==0) r15 = nval;

        }

        int len_exec_buff = strlen(exec_buff);
        exec_buff[len_exec_buff] = "\xc3";
        
        asm volatile (
            "call %0         \n" // exec code
            : //output
            : "m" (exec_buff) //input
            : //clobber
        );

        sprintf(response, 
            "rax=0x%llx\nrbx=0x%llx\nrcx=0x%llx\nrdx=0x%llx\nrsi=0x%llx\nrdi=0x%llx\nr8=0x%llx\nr9=0x%llx\nr10=0x%llx\nr11=0x%llx\nr12=0x%llx\nr13=0x%llx\nr14=0x%llx\nr15=0x%llx\n",
            rax, rbx, rcx, rdx, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15);
        printf("\n=====\nregisters (exec):\n%s\n=====\n", response);

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

