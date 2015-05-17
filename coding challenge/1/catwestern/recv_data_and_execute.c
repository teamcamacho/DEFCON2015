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
void registers_to_str(char *);

uint64_t rax;
uint64_t rbx;
uint64_t rcx;
uint64_t rdx;
uint64_t rsi;
uint64_t rdi;
uint64_t r8;
uint64_t r9;
uint64_t r10;
uint64_t r11;
uint64_t r12;
uint64_t r13;
uint64_t r14;
uint64_t r15;
char crax[10];
char crbx[10];
char crcx[10];
char crdx[10];
char crsi[10];
char crdi[10];
char cr8[10];
char cr9[10];
char cr10[10];
char cr11[10];
char cr12[10];
char cr13[10];
char cr14[10];
char cr15[10];

int main(int argc, uint8_t *argv[])
{
    int len, sock;
    uint8_t buff[MAXRCVLEN + 1];
    uint8_t shellcode[1024];
    char * response[1024];

    /*
48 B8 11 11 11 11 11 11 11 11
48 BB 22 22 22 22 22 22 22 22
48 B9 33 33 33 33 33 33 33 33 
48 BA 11 11 11 11 11 11 11 11
48 BE 22 22 22 22 22 22 22 22
48 BF 33 33 33 33 33 33 33 33 
49 B8 11 11 11 11 11 11 11 11 
49 B9 22 22 22 22 22 22 22 22 
49 BA 33 33 33 33 33 33 33 33 
49 BB 11 11 11 11 11 11 11 11 
49 BC 22 22 22 22 22 22 22 22
49 BD 33 33 33 33 33 33 33 33 
49 BE 11 11 11 11 11 11 11 11 
49 BF 22 22 22 22 22 22 22 22
    */

    sock = _connect();

    len = read_data(sock, buff);
    printf("%s", buff, len);

    register *rax asm("rax");
    register *rbx asm("rbx");
    register *rcx asm("rcx");
    register *rdx asm("rdx");
    register *rsi asm("rsi");
    register *rdi asm("rdi");
    register *r8 asm("r8");
    register *r9 asm("r9");
    register *r10 asm("r10");
    register *r11 asm("r11");
    register *r12 asm("r12");
    register *r13 asm("r13");
    register *r14 asm("r14");
    register *r15 asm("r15");

    parse_regs(buff);
    registers_to_str(response);
    printf("\n=====\nregisters (load):\n%s\n=====\n", response);

    len = read_data(sock, buff);
    printf("%s", buff, len);

    parse_inst(buff, shellcode);

    uint8_t * addr = mmap(NULL, len+200, PROT_READ|PROT_EXEC |PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0); 
    if (addr == MAP_FAILED)
    {
        printf("mmap fuck up. \n");
    }
    memcpy(addr,shellcode,len);


    int (*func)();
    func = (int (*)()) addr;
    (int)(*func)();

    registers_to_str(response);
    printf("\n=====\nregisters (exec):\n%s\n=====\n", response);

    printf("Sending solution:\n%s\n", response);

    write(sock, response, strlen(response));

    len = read_data(sock, buff);
    printf("%s", buff, len);


    close(sock);

    return EXIT_SUCCESS;
}

void registers_to_str(char * output) {
    sprintf(output, 
        "rax=0x%llx\nrbx=0x%llx\nrcx=0x%llx\nrdx=0x%llx\nrsi=0x%llx\nrdi=0x%llx\nr8=0x%llx\nr9=0x%llx\nr10=0x%llx\nr11=0x%llx\nr12=0x%llx\nr13=0x%llx\nr14=0x%llx\nr15=0x%llx\n", 
        rax, rbx, rcx, rdx, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15);
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
        //printf("%02X ", x & 0xff);
        shellcode[i] = inst[i];
    }
    //printf("\n");
}

void parse_regs(uint8_t * buff) {
    uint8_t * reg;
    uint8_t * val;
    uint8_t * tofree;
    uint8_t * string;
    uint8_t * line;

    string = strdup(buff);

    if (string != NULL) {
        tofree = string;

        while ((line = strsep(&string, "\n")) != NULL) {
            if (strstr(line, "Initial Register State") != NULL) continue;

            reg = strsep(&line, "=");
            val = strsep(&line, "=");
            
            if (val == NULL) break;

            //printf("register: %s, value: %s\n", reg, val);
/*
48 B8 11 11 11 11 11 11 11 11
48 BB 22 22 22 22 22 22 22 22
48 B9 33 33 33 33 33 33 33 33 
48 BA 11 11 11 11 11 11 11 11
48 BE 22 22 22 22 22 22 22 22
48 BF 33 33 33 33 33 33 33 33 
49 B8 11 11 11 11 11 11 11 11 
49 B9 22 22 22 22 22 22 22 22 
49 BA 33 33 33 33 33 33 33 33 
49 BB 11 11 11 11 11 11 11 11 
49 BC 22 22 22 22 22 22 22 22
49 BD 33 33 33 33 33 33 33 33 
49 BE 11 11 11 11 11 11 11 11 
49 BF 22 22 22 22 22 22 22 22
    */
            uint64_t nval = strtoull(val, NULL, 16);

            if (strcmp(reg, "rax")==0) {
                rax = nval;
                sprintf(crax,"48b8%llx",nval);
            }
            if (strcmp(reg, "rbx")==0){
                rbx = nval;
                sprintf(crbx,"48bb%llx",nval);
            }
            if (strcmp(reg, "rcx")==0){
                rcx = nval;
                sprintf(crcx,"48b9%llx",nval);
            }
            if (strcmp(reg, "rdx")==0){
                rdx = nval;
                sprintf(crdx,"48ba%llx",nval);
            }
            if (strcmp(reg, "rsi")==0) {
                rsi = nval;
                sprintf(crsi,"48be%llx",nval);
            }
            if (strcmp(reg, "rdi")==0) {
                rdi = nval;
                sprintf(crdi,"48bf%llx",nval);
            }
            if (strcmp(reg, "r8")==0)  {
                r8 = nval;
                sprintf(cr8,"49b8%llx",nval);
            }
            if (strcmp(reg, "r9")==0)  {
                r9 = nval;
                sprintf(cr9,"49b9%llx",nval);
            }
            if (strcmp(reg, "r10")==0) {
                r10 = nval;
                sprintf(cr10,"49ba%llx",nval);
            }
            if (strcmp(reg, "r11")==0) {
                r11 = nval;
                sprintf(cr11,"49bb%llx",nval);
            }
            if (strcmp(reg, "r12")==0) {
                r12 = nval;
                sprintf(cr12,"49bc%llx",nval);
            }
            if (strcmp(reg, "r13")==0) {
                r13 = nval;
                sprintf(cr13,"49bd%llx",nval);
            }
            if (strcmp(reg, "r14")==0) {
                r14 = nval;
                sprintf(cr14,"49be%llx",nval);
            }
            if (strcmp(reg, "r15")==0) {
                r15 = nval;
                sprintf(cr15,"49bf%llx",nval);
            }

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

