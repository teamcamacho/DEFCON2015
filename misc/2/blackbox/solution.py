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
            s.send("ABABABABABABABA\n")
            rdata = s.recv(1024)
            print rdata

            sdata = solve_stage_2(rdata)
            print "sending: ", sdata
            s.send(sdata + "\n")

        if "A little harder maybe?" in rdata:
            s.send("ABABABABABABABA\n")
            rdata = s.recv(1024)
            print rdata

            s.send("ABABABABABABABA\n")
            rdata = s.recv(1024)
            print rdata
            
        
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
    (password, encoded) = re.match(r'Password \[(.*)\]\s+Expected\s+\[(.*)\]', rdata).groups()

    decoded = ""
    count = 0 
    loc = valid_chars.index(encoded[0])

    for i in range(len(encoded)):
        loc = 0 
        ctry = valid_chars[(loc + count) % len(valid_chars)]

        while ctry != encoded[i]:
            loc += 1 % len(valid_chars)
            ctry = valid_chars[(loc + count) % len(valid_chars)]

        count += loc + count 

        print "loc: ", loc, " count: ", count
    
        decoded += valid_chars[loc % len(valid_chars)]

    return decoded

def generate_stage1_key(offset):
    result = [None]*len(valid_chars)
    for i in range(len(valid_chars)):
        result[i] = valid_chars[(i+offset) % len(valid_chars)]
    return "".join(result)
   
def generate_stage2_key():
    result = [None]*len(valid_chars)

    return "".join(result)

    """
    #ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ 
    #ACEGIKMOQSUWYacegikmoqsuwy02468!#%')+-/;=?[]_{} BDFHJLNPRTVXZbdfhjlnprtvxz13579"$&(*,.:<>@\^`|~
    """



main()
