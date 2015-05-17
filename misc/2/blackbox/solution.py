#!/usr/bin/env python
import socket
import string
import re

SERVER_IP = '52.7.160.61'
SERVER_PORT = 18324

valid_chars = """ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ """

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((SERVER_IP, SERVER_PORT))

    while True:
        rdata = s.recv(1024)
        print rdata

        if "Let's try some easy boxes" in rdata:
            s.send("A\n")
            rdata = s.recv(1024)
            print rdata
            
            sdata = solve_stage_1(rdata)
            print "sending: ", sdata
            s.send(sdata + "\n")
        if "Another easy box:" in rdata:
            s.send("A\n")
            rdata = s.recv(1024)
            print rdata

            sdata = solve_stage_2(rdata)
            print "sending: ", sdata
            s.send(sdata + "\n")


    s.close()

def solve_stage_1(rdata):
    (password, expected) = re.match(r'Password \[(.*)\]\s+Expected\s+\[(.*)\]', rdata).groups()
    offset = valid_chars.index(password)

    key = generate_stage1_key(offset)

    rot = string.maketrans(
        key,
        valid_chars
    )

    return string.translate(expected, rot)

def solve_stage_2(rdata):
    (password, expected) = re.match(r'Password \[(.*)\]\s+Expected\s+\[(.*)\]', rdata).groups()
    offset = valid_chars.index(password)

    key = generate_stage2_key()

    print valid_chars
    print key
        

    rot = string.maketrans(
        key,
        valid_chars
    )

    return string.translate(expected, rot)

def generate_stage1_key(offset):
    result = [None]*len(valid_chars)
    for i in range(len(valid_chars)):
        result[i] = valid_chars[(i+offset) % len(valid_chars)]
    return "".join(result)
   
def generate_stage2_key():
    result = [None]*len(valid_chars)


    for i in range(len(valid_chars)):
        result[i] = valid_chars[(i*2) % len(valid_chars)]

    return "".join(result)

    """
    #ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ 
    #ACEGIKMOQSUWYacegikmoqsuwy02468!#%')+-/;=?[]_{} BDFHJLNPRTVXZbdfhjlnprtvxz13579"$&(*,.:<>@\^`|~
    """

main()