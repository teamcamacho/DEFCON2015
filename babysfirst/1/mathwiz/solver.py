'''
blackbox_ced7f267475a0299446fa86c26d77161.quals.shallweplayaga.me 18324
'''
import socket

'''
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ "
'''

def query():
	ip = socket.gethostbyname('mathwhiz_c951d46fed68687ad93a84e702800b7a.quals.shallweplayaga.me')
	sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
	sock.connect( (ip, 21249) )
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
	
def calcPass(submitted,received):
	arrChars = ['A','B','C','D','E','F','G','H','I','J','K','L','M',
	'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c',
	'd','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
	't','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8',
	'9','!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/',
	':',';','<','=','>','?','@','[','\\',']','^','_','`','{','|','}',
	'~',' ']
	#put submitted and received in hashmap

	pass

if __name__ == '__main__':
	query()