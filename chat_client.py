import socket,select,string
from time import ctime
import  sys

bufsize =1024
message = 'you can communicate with me now'
host = sys.argv[1]
port = int(sys.argv[2])
addr = (host,port)
start = True

while True:
	if start:
		 client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		 client.connect(addr)
		 print 'Enter you password'
		 
	data = raw_input(">")
	if not data:
		break
	else:
		client.send(data)
		data= client.recv(bufsize)
		if data == message:
			start = False
		print '%s\n%s' %(ctime(),data)		
client.close()
