import numpy
import os.path
import string


def open_sesame():
	while True:
		filename = input("Enter the name of the file you would like to open: ")
		if os.path.isfile(filename):
			break
		print("error opening file or file nonexistent\n")
	file = open(filename, "r")
	contents = file.read().split()
	file.close()
	return contents


def printeroni(num_proc, num_rec, avail, alloc, req): 
	row = 0
	print("Number of processes: ", num_proc)
	print("Number of resources: ", num_rec)
	print("Available instances of each resource: \n", end='')
	for x in avail:
		print(x, end='')
	print("\nAllocation matrix: ")
	for x in alloc:
		row+=1
		print(x, end='')
		if row == num_rec:
			row = 0
			print()
	row = 0
	print("Request matrix: ")
	for x in req:
		row+=1
		print(x, end='')
		if row == num_rec:
			row = 0
			print()


def assign(contents):
	num_proc = 0
	num_rec = 0
	avail = []
	alloc = []
	req = []
	counter = 0
	for x in contents:
		if counter == 0:
			num_proc = int(x)
			counter+=1
		elif counter == 1:
			num_rec = int(x)
			counter+=1 
		elif counter == 2:
			avail.append(int(x)) 
			if len(avail) == num_rec:
				counter+=1
		elif counter == 3:
			alloc.append(int(x))
			if len(alloc) == num_rec * num_proc:
				counter+=1
		elif counter == 4:
			req.append(int(x))
			if len(req) == num_rec * num_proc:
				break
	return num_proc, num_rec, avail, alloc, req


def diddlydo(num_proc, num_rec, avail, alloc, req):
	total_available = avail - numpy.sum(alloc, axis=0)

	running = numpy.ones(num_proc)

	while numpy.count_nonzero(running) > 0:
		isalloc = False
		for p in range(num_proc):
		    if running[p]:
		        if all(i >= 0 for i in total_available - (req[p] - alloc[p])):
		            isalloc = True
		            print(str(p) + " is running")
		            running[p] = 0
		            total_available += alloc[p]
		if not isalloc:
			#printeroni(num_proc, num_rec, avail, alloc, req)
			print("Status: Unsafe")
			exit()

	print("Status: Safe")


def main():
	contents = open_sesame()
	num_proc, num_rec, avail, alloc, req = assign(contents)
	printeroni(num_proc, num_rec, avail, alloc, req)
	diddlydo(num_proc, num_rec, avail, alloc, req)

	return 0


if __name__ == "__main__":
	main() 

