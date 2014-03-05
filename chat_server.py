import socket, select, string, sys
from time import ctime

#storing the clients in the connection_list
CONNECTION_LIST= []
#for receieing buffer
bufsize=1024
host = '0.0.0.0'
port = 5000
password = 'hi'
message1= 'your password is incorrect'
message2 = 'you can communicate with me now'
begin =True
#create the socket
sever = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
#bind the sever to an address and initialize the listern number
sever.bind((host,port))
sever.listen(2)

#add the sever into the readable connection
CONNECTION_LIST.append(sever)

print 'chat sever start at port: ' + str(port)

while True:
	print 'waiting for the client to connect'
	# need to accept the client's connection
	clientsock,addr = sever.accept()
	print 'received from: ', addr
	begin =True
        data = clientsock.recv(bufsize)
	if data == password:
		clientsock.send(message2)
	else:
		begin=False
		clientsock.send(message1)
			
	while begin:
		data =clientsock.recv(bufsize)
		print '%s\n%s' % (ctime(),data)
		data = raw_input(">")
		clientsock.send(data)
	clientsock.close()


sever.close()




