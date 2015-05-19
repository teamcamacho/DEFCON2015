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
            (expected, key) = get_key(s)
            print "key:", key
            sdata = solve_stage_1(expected, key)

            print "sending: ", sdata
            s.send(sdata + "\n")

        if "Another easy box:" in rdata:
            (expected, key) = get_key(s)
            print "key:", key
            sdata = solve_stage_1(expected, key)

            print "sending: ", sdata
            s.send(sdata + "\n")


    s.close()

def solve_stage_1(expected, key):
    rot = string.maketrans(
        key,
        valid_chars
    )

    return string.translate(expected, rot)

def solve_stage_2(expected, key):
    stage2_rot = string.maketrans(
        key,
        valid_chars
    )

    return string.translate(expected, stage2_rot)

def get_key(s):
    print "get key"
    s.send("%s\n" % valid_chars[:len(valid_chars)/2])
    rdata = s.recv(1024)
    print rdata
    (key_lh, expected) = re.match(r'Password \[(.*)\]\s+Expected\s+\[(.*)\]', rdata).groups()

    s.send("%s\n" % valid_chars[len(valid_chars)/2:])
    rdata = s.recv(1024)
    print rdata
    (key_uh, expected) = re.match(r'Password \[(.*)\]\s+Expected\s+\[(.*)\]', rdata).groups()

    return (expected, "%s%s" % (key_lh, key_uh))

main()
