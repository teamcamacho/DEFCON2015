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

    print s.recv(1024)
    print s.recv(1024)

    s.send("A\n")

    rdata = s.recv(1024)
    print rdata

    (password, expected) = re.match(r'Password \[(.*)\]\s+Expected\s+\[(.*)\]', rdata).groups()
    offset = valid_chars.index(password)

    print "offset: ", offset

    rot_key = generate_rot(offset)

    rot = string.maketrans(
        rot_key,
        valid_chars
    )

    print valid_chars
    print rot_key


    sdata = string.translate(expected, rot)

    print "sending: " + sdata

    s.send(sdata + "\n")

    print s.recv(1024)

    s.close()

def generate_rot(offset):
    result = [None]*len(valid_chars)
    for i in range(len(valid_chars)):
        result[i] = valid_chars[(i+offset) % len(valid_chars)]
    return "".join(result)
    


main()
