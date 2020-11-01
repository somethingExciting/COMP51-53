import os
import string
import random
import sys

MEM_FILE = 512 #size of the "memory" file (512KB)
FRAME_SIZE = 512 #size of each frame (512 bytes)
FRAMES = 1024 #number of frames
NUM_PAGES = 2**13 #number of pages needed where 1 page = 1024 bytes 


def open_sesame():
	print("Opening a memory file...")
	while True:
		filename = input("Enter the name of the file you would like to open: ")
		if os.path.isfile(filename):
			break
		print("error opening file or file non-existent\n")
	file = open(filename, "r")
	contents = file.read().split()
	file.close()
	return contents


def create_or_open():
	decision = input("Open file? (Y/N)")
	decision = decision.upper()
	if decision == 'Y':
		items = []
		for item in os.listdir():
			if item.endswith(".txt"):
				items.append(item)
		print("List of default files:\n", items)
		contents = open_sesame()

		listoftuples = []
		for word in range(len(contents)):
			if word%2 == 0:
				l = contents[word:word+2]
				listoftuples.append(l)
		listing = dict(listoftuples)
	else:
		print("Creating a memory file...")
		items = random.randint(0, 15)
		exe = ["dflds", "aefal", "dmfawef", "sdkln", "skfk", "ewoirp", "smflks", "snkdls", "qoepfo", "zsdfk", "skzns", "weopcm", "qpmefe", "mfqefo"]
		listing = {}
		weee = random.shuffle(exe)
		for x in range(items):
			listing[exe[x]] = random.randint(0,NUM_PAGES)
	return listing


def main():
	listing = create_or_open()				

	print("\nMemory file size: %dKB" % MEM_FILE)
	print("Size of each frame: %d bytes" % FRAME_SIZE)
	print("Nunmber of free frames: %d frames\n" % FRAMES)

	print("Loading an executable...")
	print("List of all executable files currently in the memory file: ")
	for word in listing:
		print("%s: page - %d; frame number - %d; program size - %d" % (word, int(listing[word]), len(word), sys.getsizeof(word)))

	print("Free frames: ", FRAMES - len(listing))

	while True:
		decision = input("Open a page table of a process? (Y/N)")
		decision = decision.upper()
		if decision != 'Y':
			break
		else:
			while True:
				decision = input("Which program's page table would you like to open? ")
				if decision in listing:
					break
				print("Invalid program name")
			index = list(listing.keys()).index(decision)
			for x in range(NUM_PAGES):
				print(x, ": ", end='')
				if x == index:
					if type(listing[decision]) is int:
						print(listing[decision])
					else:
						print(len(listing[decision]))
				print()
	print("Exiting...")			


if __name__ == "__main__":
	main()
