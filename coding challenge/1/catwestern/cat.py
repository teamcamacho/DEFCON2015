from parse import *
import socket   #for sockets
import sys  #for exit
import binascii 
try:
	#create an AF_INET, STREAM socket (TCP)
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error, msg:
	print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message : ' + msg[1]
	sys.exit();
 
print 'Socket Created'
 
host = 'catwestern_631d7907670909fc4df2defc13f2057c.quals.shallweplayaga.me'
port = 9999
 
try:
	remote_ip = socket.gethostbyname( host )
 
except socket.gaierror:
	#could not resolve
	print 'Hostname could not be resolved. Exiting'
	sys.exit()
	 
print 'Ip address of ' + host + ' is ' + remote_ip
 
#Connect to remote server
s.connect((remote_ip , port))
 
print 'Socket Connected to ' + host + ' on ip ' + remote_ip

#Now receive data
reply = s.recv(4096)
print reply
r = parse ("****Initial Register State****\nrax={}\nrbx={}\nrcx={}\nrdx={}\nrsi={}\nrdi={}\nr8={}\nr9={}\nr10={}\nr11={}\nr12={}\nr13={}\nr14={}\nr15={}",reply)
print ("[rax] : " + r[0])
print ("[rbx] : " + r[1])
print ("[rcx] : " + r[2])
print ("[rdx] : " + r[3])
print ("[rsi] : " + r[4])
print ("[rdi] : " + r[5])
print (" [r8] : " + r[6])
print (" [r9] : " + r[7])
print ("[r10] : " + r[8])
print ("[r11] : " + r[9])
print ("[r12] : " + r[10])
print ("[r13] : " + r[11])
print ("[r14] : " + r[12])
print ("[r15] : " + r[13])


reply = s.recv(4096)
print reply
reply2=binascii.hexlify(reply)
print "[REPLY2]"
print reply2
r = search ("****Send Solution In The Same Format****\nAbout to send {:d} bytes:{}",reply)
print("[SIZE] : %d" % r[0])
print("[HEX VALUE] : ")

#jack2hex = reply[67:].encode("hex")
jack2hex = " ".join("{:02x}".format(ord(c)) for c in reply[66:])
print jack2hex