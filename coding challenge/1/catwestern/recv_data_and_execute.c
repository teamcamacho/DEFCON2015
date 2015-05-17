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

<<<<<<< HEAD
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
=======
int main(int argc, uint8_t *argv[])
{
    int inst_len, len, sock;
    uint8_t buff1[MAXRCVLEN + 1];
    uint8_t buff2[MAXRCVLEN + 1];
<<<<<<< HEAD
    uint8_t shellcode[256];
>>>>>>> 8d24da5c572eb4ef7c3e0dbd9d624ef3edc34785
    char * response[1024];
=======
    uint8_t shellcode[256] = {0};
    char response[1024] = {0};
>>>>>>> e86a49429ead531a0237020ea387c5bd9d3a4686

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

<<<<<<< HEAD
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
=======
    len = read_data(sock, buff1);
    printf("%s", buff1, len);

    len = read_data(sock, buff2);
    printf("%s", buff2, len);

    inst_len = parse_inst(buff2, shellcode);

    uint8_t * exec_buff = mmap(shellcode, inst_len, PROT_READ|PROT_EXEC |PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0); 
    if (exec_buff == MAP_FAILED)
>>>>>>> 8d24da5c572eb4ef7c3e0dbd9d624ef3edc34785
    {
        printf("mmap fuck up. \n");
    }
    memcpy(exec_buff,shellcode,len);

    /*
    int (*func)();
    func = (int (*)()) addr;
    (int)(*func)();
    */

    parse_regs(buff1, exec_buff, response);

    //printf("\n\nSending solution:\n%s\n", response);

    /*
    ****Initial Register State****
    rax=0x2404dbf25a0af700
    rbx=0x68c05efe54a3c445
    rcx=0x76de93faba2f8502
    rdx=0x9dfc9b4e8be86957
    rsi=0x99d1bf79721f1b5f
    rdi=0xd6eee8551b0bf0d2
    r8=0xe7cb59ab3e4bdd9c
    r9=0xd3441b0b62187ecb
    r10=0x8f5026659569b7c0
    r11=0x842348707b626fc
    r12=0x268871d483f109fc
    r13=0x375ae2f6b95c4969
    r14=0xbceb39501e6b9667
    r15=0x50d1360c44d70ecd
    ****Send Solution In The Same Format****
    */

    write(sock, response, strlen(response));

    len = read_data(sock, buff1);
    printf("%s", buff1, len);

    close(sock);

    return EXIT_SUCCESS;
}

/*
void registers_to_str(char * response) {
    sprintf(response, 
        "rax=%0x064llx\nrbx=%0x064llx\nrcx=%0x064llx\nrdx=%0x064llx\nrsi=%0x064llx\nrdi=%0x064llx\nr8=%0x064llx\nr9=%0x064llx\nr10=%0x064llx\nr11=%0x064llx\nr12=%0x064llx\nr13=%0x064llx\nr14=%0x064llx\nr15=%0x064llx\n", 
        rax, rbx, rcx, rdx, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15);
}
*/

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

    //printf("len: %d\n", len);
    //printf("inst: %s\n", inst);

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

<<<<<<< HEAD
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
=======
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
>>>>>>> 8d24da5c572eb4ef7c3e0dbd9d624ef3edc34785

        }

        /*
        sprintf(response, 
            "rax=0x%016llx\nrbx=0x%016llx\nrcx=0x%016llx\nrdx=0x%016llx\nrsi=0x%016llx\nrdi=0x%016llx\nr8=0x%016llx\nr9=0x%016llx\nr10=0x%016llx\nr11=0x%016llx\nr12=0x%016llx\nr13=0x%016llx\nr14=0x%016llx\nr15=0x%016llx\n", 
            rax, rbx, rcx, rdx, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15);
        printf("\n=====\nregisters (load):\n%s\n=====\n", response);
        */

        /*
        asm volatile (
            ""
            :   // Input
            :   // Output
            :   // Clobber
        );
        */
       
        int len_exec_buff = strlen(exec_buff);
        exec_buff[len_exec_buff] = "\xc3";
        
        asm volatile (
            "call _next      \n"
            "movq %0, %%rax  \n"
            "movq %1, %%rbx  \n"
            "movq %2, %%rcx  \n"
            "movq %3, %%rdx  \n"
            "movq %4, %%rsi  \n"
            "movq %5, %%rdi  \n"
            "movq %6, %%r8  \n"
            "movq %7, %%r9  \n"
            "movq %8, %%r10  \n"
            "movq %9, %%r11  \n"
            "movq %10, %%r12  \n"
            "movq %11, %%r13  \n"
            "movq %12, %%r14  \n"
            "movq %13, %%r15  \n"
            "jmp _end_buf     \n"
            "_next:           \n"
            "movq %%rax, %14  \n"
            "movq %%rbx, %15  \n"
            "movq %%rcx, %16  \n"
            "movq %%rdx, %17  \n"
            "movq %%rsi, %18  \n"
            "movq %%rdi, %19 \n"
            "movq %%r8, %20  \n"
            "movq %%r9, %21  \n"
            "movq %%r10, %22  \n"
            "movq %%r11, %23  \n"
            "movq %%r12, %24  \n"
            "movq %%r13, %25  \n"
            "movq %%r14, %26  \n"
            "movq %%r15, %27  \n"
            "jmp %28         \n" // exec code
            "_end_buf:       \n"
            : "=r" (rax), "=r" (rbx), "=r" (rcx), "=r" (rdx), "=r" (rsi), "=r" (rdi), "=r" (r8), "=r" (r9), "=r" (r10), "=r" (r11), "=r" (r12), "=r" (r13), "=r" (r14), "=r" (r15)
            : "r" (rax), "r" (rbx), "r" (rcx), "r" (rdx), "r" (rsi), "r" (rdi), "r" (r8), "r" (r9), "r" (r10), "r" (r11), "r" (r12), "r" (r13), "r" (r14), "r" (r15), "m" (exec_buff)
            //: "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" //clobber
        );

        sprintf(response, 
            "rax=0x%llx\nrbx=0x%llx\nrcx=0x%llx\nrdx=0x%llx\nrsi=0x%llx\nrdi=0x%llx\nr8=0x%llx\nr9=0x%llx\nr10=0x%llx\nr11=0x%llx\nr12=0x%llx\nr13=0x%llx\nr14=0x%llx\nr15=0x%llx\n",
            rax, rbx, rcx, rdx, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15);
        printf("\n=====\nregisters (exec):\n%s\n=====\n", response);

        /*
        sprintf(response, 
            "rax=0x%016llx\nrbx=0x%016llx\nrcx=0x%016llx\nrdx=0x%016llx\nrsi=0x%016llx\nrdi=0x%016llx\nr8=0x%016llx\nr9=0x%016llx\nr10=0x%016llx\nr11=0x%016llx\nr12=0x%016llx\nr13=0x%016llx\nr14=0x%016llx\nr15=0x%016llx\n",
            rax, rbx, rcx, rdx, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15);
        printf("\n=====\nregisters (exec):\n%s\n=====\n", response);
        */
        /* Invalid Format error if we add header and footer:
        sprintf(response, 
            "****Initial Register State****\n" \
            "rax=0x%016llx\nrbx=0x%016llx\nrcx=0x%016llx\nrdx=0x%016llx\nrsi=0x%016llx\nrdi=0x%016llx\nr8=0x%016llx\nr9=0x%016llx\nr10=0x%016llx\nr11=0x%016llx\nr12=0x%016llx\nr13=0x%016llx\nr14=0x%016llx\nr15=0x%016llx\n" \
            "****Send Solution In The Same Format****\n", 
            rax, rbx, rcx, rdx, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15);
        printf("\n=====\nregisters (exec):\n%s\n=====\n", response);
        */

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

