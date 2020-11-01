#!/usr/bin/env python3

# Python Dummy DNS query constructor
#
# Example usage:
#   ./dummy_query.py --type=A --name=www.pacific.edu --server=8.8.8.8
#   ./dummy_query.py --type=AAAA --name=www.google.com --server=8.8.8.8

# Should print the dummy raw_bytes to be sent to the server.
# NOTE: THIS IS NOT A SOLUTION FOR LAB 09


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


	# Generate DNS request message, raw_bytes and PRINT it
	# ---------
	# STUDENT TO-DO
	# ---------

	raw_bytes = bytearray()
	request = "dig " + qname + " " + qtype + " " + server_ip + " +noedns\r\n\r\n"
	raw_string = bytes(request, 'ascii') 
	raw_bytes = struct.pack("Q", len(request))
	print(raw_bytes)

if __name__ == "__main__":
    sys.exit(main())
