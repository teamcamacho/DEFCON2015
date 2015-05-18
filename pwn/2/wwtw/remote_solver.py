#!/usr/bin/env python

from subprocess import *
import fcntl, os, time, re
import socket

SERVER_IP = '52.4.234.13'
SERVER_PORT = 2606




def main():
    #b = "./wwtw_c3722e23150e1d5abbc1c248d99d718d"
    #p = Popen(b, stdin=PIPE, stdout=PIPE)
    #fcntl.fcntl(p.stdout.fileno(), fcntl.F_SETFL, os.O_NONBLOCK)

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((SERVER_IP, SERVER_PORT))

    solve_grid(s)

    s.close()


def solve_grid(s):

    data = s.recv(1024)
    print data

    grid = parse_data(data)

    while True:
        
        start = find_V(grid)
        end = find_dest(grid)

        if end == None:
            end = find_dest(grid,'T')

        cmds = find_path(start, end, grid)

        for c in cmds:
            #print ""
            #for line in grid:
            #    print line
            print c
            s.send("%s\n" % c)
            data = s.recv(1024)
            print data
            grid = parse_data(data) 

        if 'TARDIS KEY' in data: 
            print "UeSlhCAGEp"
            s.send("UeSlhCAGEp\n")
            data = s.recv(1024)
            print data

        if 'Selection' in data: 
            print "1"
            s.send("1\n")
            data = s.recv(1024)
            print data

        if 'Selection' in data: 
            print "3"
            s.send("3\n")
            data = s.recv(1024)
            print data

            break

# 51.492137
# -0.192878


def find_path(V, E, grid):
    #print V
    #print E

    oV = V
    cmds = []
    while V != E:

        if V[0] < E[0] and grid[V[1]][V[0]+1] != 'A':
            V = (V[0]+1,V[1])
            cmds.append('d')
        elif V[1] < E[1] and grid[V[1]+1][V[0]] != 'A':
            V = (V[0],V[1]+1)
            cmds.append('s')
        elif V[0] > E[0] and grid[V[1]][V[0]-1] != 'A':
            V = (V[0]-1,V[1])
            cmds.append('a')
        elif V[1] > E[1] and grid[V[1]-1][V[0]] != 'A':
            V = (V[0],V[1]-1)
            cmds.append('w')
        else:
            break

    return cmds


def find_dest(grid, dest='E'):
    for y in range(len(grid)):
        line = grid[y]
        for x in range(len(line)):
            if line[x] == dest:
                return (x,y)

def find_V(grid):
    for y in range(len(grid)):
        line = grid[y]
        for x in range(len(line)):
            if line[x] == '<' or line[x] == '>' or line[x] == 'V' or line[x] == '^':
                return (x,y)
        
def parse_data(data):
    lines = []

    for line in data.split("\n"):
        #print line
        m = re.search(r'^\d\d (.*)', line)
        if m != None:
            lines.append( [c for c in m.group(1)] )

    return lines

def read_input(p):
    while True:
        data = ''
        try:
            data += p.stdout.read()
            print data
        except IOError:
            pass
        if got_all_data(data):
            break

        time.sleep(.1)

    return data

def got_all_data(data):
    return 'Your move (w,a,s,d,q):' in data \
        or 'TARDIS KEY:' in data \
        or 'Selection' in data

main()
