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
void parse_inst(uint8_t *, uint8_t *);
void registers_to_str(char *);

int main(int argc, uint8_t *argv[])
{
    int len, sock;
    uint8_t buff1[MAXRCVLEN + 1];
    uint8_t buff2[MAXRCVLEN + 1];
    uint8_t shellcode[256];
    char * response[1024];

    sock = _connect();

    len = read_data(sock, buff1);
    printf("%s", buff1, len);

    len = read_data(sock, buff2);
    printf("%s", buff2, len);

    parse_inst(buff2, shellcode);

    uint8_t * exec_buff = mmap(shellcode, len, PROT_READ|PROT_EXEC |PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0); 
    if (exec_buff == MAP_FAILED)
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

    printf("\n\nSending solution:\n%s\n", response);

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
        shellcode[i] = inst[i];
    }
    printf("\n");
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
            "jmp _end_buf     \n"
            "_next:           \n"
            "movq %%rax, %13  \n"
            "movq %%rbx, %14  \n"
            "movq %%rcx, %15  \n"
            "movq %%rdx, %16  \n"
            "movq %%rsi, %17  \n"
            "movq %%rdi, %18  \n"
            "movq %%r8, %19  \n"
            "movq %%r9, %20  \n"
            "movq %%r10, %21  \n"
            "movq %%r11, %22  \n"
            "movq %%r12, %23  \n"
            "movq %%r13, %24  \n"
            "movq %%r14, %25  \n"
            "jmp %26         \n" // exec code
            "_end_buf:       \n"
            : "=r" (rax), "=r" (rbx), "=r" (rcx), "=r" (rdx), "=r" (rsi), "=r" (rdi), "=r" (r8), "=r" (r9), "=r" (r10), "=r" (r11), "=r" (r12), "=r" (r13), "=r" (r14)
            : "r" (rax), "r" (rbx), "r" (rcx), "r" (rdx), "r" (rsi), "r" (rdi), "r" (r8), "r" (r9), "r" (r10), "r" (r11), "r" (r12), "r" (r13), "r" (r14), "r" (exec_buff)
            //: "%rax"
        );

        sprintf(response, 
            "rax=0x%016llx\nrbx=0x%016llx\nrcx=0x%016llx\nrdx=0x%016llx\nrsi=0x%016llx\nrdi=0x%016llx\nr8=0x%016llx\nr9=0x%016llx\nr10=0x%016llx\nr11=0x%016llx\nr12=0x%016llx\nr13=0x%016llx\nr14=0x%016llx\nr15=0x%016llx\n", 
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

