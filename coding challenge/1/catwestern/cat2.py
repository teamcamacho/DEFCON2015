import os, re
import socket
import sys
import socket

def def_catwestern(ip, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((ip, int(port)))
    recv1 = s.recv(1024*5)
    print recv1
    p = re.compile("0x\S.*", re.MULTILINE)
    rax = (p.findall(recv1))[0]
    rbx = (p.findall(recv1))[1]
    rcx = (p.findall(recv1))[2]
    rdx = (p.findall(recv1))[3]
    rsi = (p.findall(recv1))[4]
    rdi = (p.findall(recv1))[5]
    r8 = (p.findall(recv1))[6]
    r9 = (p.findall(recv1))[7]
    r10 = (p.findall(recv1))[8]
    r11 = (p.findall(recv1))[9]
    r12 = (p.findall(recv1))[10]
    r13 = (p.findall(recv1))[11]
    r14 = (p.findall(recv1))[12]
    r15 = (p.findall(recv1))[13]
    recv2 = s.recv(1024*5)
    problem = recv2[recv2.index(":")+1:]
    print problem.encode('hex')
    
    s.close()