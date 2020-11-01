#!/usr/bin/env python3

# Python DNS query client
#
# Example usage:
#   ./dns.py --type=A --name=www.pacific.edu --server=8.8.8.8
#   ./dns.py --type=AAAA --name=www.google.com --server=8.8.8.8

# Should provide equivalent results to:
#   dig www.pacific.edu A @8.8.8.8 +noedns
#   dig www.google.com AAAA @8.8.8.8 +noedns
#   (note that the +noedns option is used to disable the pseduo-OPT
#    header that dig adds. Our Python DNS client does not need
#    to produce that optional, more modern header)


from dns_tools import dns  # Custom module for boilerplate code

import argparse
import ctypes
import random
import socket
import struct
import sys

def main():

	# Setup configuration
	parser = argparse.ArgumentParser(description='DNS client for ECPE 170')
	parser.add_argument('--type', action='store', dest='qtype',
		                required=True, help='Query Type (A or AAAA)')
	parser.add_argument('--name', action='store', dest='qname',
		                required=True, help='Query Name')
	parser.add_argument('--server', action='store', dest='server_ip',
		                required=True, help='DNS Server IP')

	args = parser.parse_args()
	qtype = args.qtype
	qname = args.qname
	server_ip = args.server_ip
	port = 53
	server_address = (server_ip, port)

	if qtype not in ("A", "AAAA"):
		print("Error: Query Type must be 'A' (IPv4) or 'AAAA' (IPv6)")
		sys.exit()

    # Create UDP socket
    # ---------
    # STUDENT TO-DO
    # ---------

	try: 
		s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	except socket.error as msg:
		print("Error: could not create socket")
		print("Description: " + str(msg))
		sys.exit()	
	
	print("Socket created")	

    # Generate DNS request message
    # ---------
    # STUDENT TO-DO
    # ---------

	#print("Sending request for for " + qname + ", " + qtype + " to server " + server_ip + ", " + port 
	#creating a query package 
	bytearray()	
	raw_bytes = bytearray()
	#transaction id
	raw_bytes.append(0xab)
	raw_bytes.append(0xcd)
	#flags
	raw_bytes.append(0x01)
	raw_bytes.append(0x20)
	#questions
	raw_bytes.append(0x00)
	raw_bytes.append(0x01)
	#answer
	raw_bytes.append(0x00)
	raw_bytes.append(0x00)
	#authority RRs
	raw_bytes.append(0x00)
	raw_bytes.append(0x00)
	#add RRs
	raw_bytes.append(0x00)
	raw_bytes.append(0x00)
	#query; add the binary version of the website name
	query = qname.split('.')
	for items in query:
		raw_bytes.append(len(items))
		j=bytes(items,'ascii')
		raw_bytes = raw_bytes + j
	raw_bytes.append(0x00)
	#type
	raw_bytes.append(0x00)
	if(qtype == "A"): 
		raw_bytes.append(0x01)
	else: 
		raw_bytes.append(0x1c)
	#class
	raw_bytes.append(0x00)
	raw_bytes.append(0x01)

    # Send request message to server
    # (Tip: Use sendto() function for UDP)
    # ---------
    # STUDENT TO-DO
    # ---------

	#raw_bytes = bytearray()
	#raw_bytes = request
	print(raw_bytes)
	
	#for string in request
	#	string_bytes = bytes(string, 'ascii')
	#	raw_bytes += string_bytes 
	
	#raw_bytes = bytes(request, 'ascii')

	try:
		bytes_sent = s.sendto(raw_bytes, server_address) 
	except socket.error as msg:
		print("Error: sendto() failed")
		print("Description: " + str(msg))
		sys.exit()

	print("Sent " + str(bytes_sent) + " bytes to server")	

    # Receive message from server
    # (Tip: use recvfrom() function for UDP)
    # ---------
    # STUDENT TO-DO
    # ---------
	
	max_bytes = 4064

	try:
		data = s.recvfrom(max_bytes)
	except socket.error as msg:
		print("Error: unable to recvfrom()")
		print("Description: " + str(msg))
		sys.exit()

	print("Server response: " + str(data))

    # Close socket
    # ---------
    # STUDENT TO-DO
    # ---------

	try:
		s.close()
	except socket.error as msg:
		print("Error: unable to close() socket")
		print("Description: " + str(msg))
		sys.exit()

	print("Socket closed, now exiting")

    # Decode DNS message and display to screen
	dns.decode_dns(raw_bytes)
	print(raw_bytes)


if __name__ == "__main__":
    sys.exit(main())
