'''
blackbox_ced7f267475a0299446fa86c26d77161.quals.shallweplayaga.me 18324
'''
import socket

'''
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ "
'''

def query():
	ip = socket.gethostbyname('blackbox_ced7f267475a0299446fa86c26d77161.quals.shallweplayaga.me')
	sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
	sock.connect( (ip, 18324) )
	print sock.recv(1024)
	print sock.recv(1024)
	print 'sending 1234'
	sock.send('1234\n')
	#split the string into the shifted alphabet and what was submitted
	strPass = sock.recv(1024)
	strSplitSpace = strPass.split(' ')
	submitted = ''
	received = ''
	
	sock.send('()_+\n')
	print sock.recv(1024)
	sock.send('abcd\n')
	print sock.recv(1024)
	'''
ABCDEFGHI  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  0  1  2  3  4  5  6  7  8  9  !  "  #  $  %  &  '  (  )  *  +  ,  -  .  /  :  ;  <  =  >  ?  @  [  \  ]  ^  _  `  {  |  }  ~    
123456789  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95

ABDH P  f  "  g  $      ,
1248 16 32 64 33 66 ... 74

ABDHPf"g$k,0KVr^=%m:8a1MZzIRj*wCFLXvABDHPf"g$k,v
ABDHPf"g$k,0KVr^=%m:8a1MZzIRj*wCFLXvABDHPf"g$k,0KVr^=%m:8a1MZz!e9c5Up@+yGNb3Qh&o>'q\/6Wt|_?)u~}
ABDHPf"g$k,0KVr^=%m:8a1MZzIRj*wCFLXvABDHPf"g$k,0KVr^=%m:8a1MZzIRj*wCFLXvABDHPf"g$k,0KVr^=%m:8a1
	'''
def calcPass():
	arrChars = [' ','A','B','C','D','E','F','G','H','I','J','K','L','M',
	'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c',
	'd','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
	't','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8',
	'9','!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/',
	':',';','<','=','>','?','@','[','\\',']','^','_','`','{','|','}',
	'~']
	encChars = []
	pos = 0
	for i in range(0,len(arrChars)):
		pos = ((pos*2)) % len(arrChars)
		if i==0:
			pos = 1
		encChars.append(arrChars[pos])
		print "pos = " + str(pos)
		

	print "encChars are: "+ ''.join(encChars)
if __name__ == '__main__':
	calcPass()