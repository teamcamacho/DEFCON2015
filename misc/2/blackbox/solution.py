#!/usr/bin/env python
import socket
import string
import re

SERVER_IP = '52.7.160.61'
SERVER_PORT = 18324

valid_chars = """ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ """
rev_valid_chars = valid_chars[::-1]

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

        if "A little harder maybe?" in rdata:
            s.send("ABABABABABABABA\n")
            rdata = s.recv(1024)
            print rdata

            s.send("A\n")
            rdata = s.recv(1024)
            print rdata


            sdata = solve_stage_3(rdata)
            print "sending: ", sdata
            s.send(sdata + "\n")

            rdata = s.recv(1024)
            print rdata

            break
        
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

        decoded += valid_chars[loc % len(valid_chars)]

    return decoded

def solve_stage_3(rdata):
    (password, expected) = re.match(r'Password \[(.*)\]\s+Expected\s+\[(.*)\]', rdata).groups()
    offset = rev_valid_chars.index(password)

    key = generate_stage3_key(offset)

    rot = string.maketrans(
        key,
        valid_chars
    )

    print valid_chars
    print key

    return string.translate(expected, rot)


def generate_stage1_key(offset):
    result = [None]*len(valid_chars)
    for i in range(len(valid_chars)):
        result[i] = valid_chars[(i+offset) % len(valid_chars)]
    return "".join(result)
   
def generate_stage3_key(offset):
    result = [None]*len(rev_valid_chars)
    for i in range(len(rev_valid_chars)):
        result[i] = rev_valid_chars[(i+offset) % len(rev_valid_chars)]
    return "".join(result)


main()
