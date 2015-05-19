#!/usr/bin/env python
import socket
import string
import re

valid_chars = """ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ """

def solve_stage_2():

    print "------------"
    print "Encoder"
    
    test = "ABABABABABABABA"
    print "input: ", test

    encoded = ""
    count = 0
    for i in range(len(test)):
        loc = valid_chars.index(test[i])
        encoded += valid_chars[(loc + count) % len(valid_chars)]
        count += loc + count 

        print "loc: ", loc, " count: ", count

    print "encoded: ", encoded


    print "------------"
    print "Decoder"


    print "input: ", encoded
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

    print "decoded: ", decoded
    print "-------------"

solve_stage_2()
