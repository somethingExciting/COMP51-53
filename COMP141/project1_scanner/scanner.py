import re
import sys
import time
import collections

MAX_ARGS = 3
Token = collections.namedtuple('Token', ['tag', 'value'])

"""  
([a-z] | [A-Z])([a-z] | [A-Z] | [0-9])*   #IDENTIFIER
[0-9]+									  #NUMBER
\+ | \- | \* | / | \( | \) | := | ;		  #PUNCTUATION
if | then | else | endif | while | do | endwhile | skip  #KEYWORD
"""
#
def tokenize(line):
	#keywords = { 'if', 'then', 'else', 'endif', 'while', 'do', 'endwhile', 'skip' }
	lang_tok = [
	('KEYWORD', r'if|then|else|endif|while|do|endwhile|skip'), #keywords
	('IDENTIFIER', r'[a-z]|[A-Z](\w|\d)*'), #a-z or A-Z or an int -> 0 or more 
	('NUMBER', r'\d+'),			 #int -> 1 or more
	('PUNCTUATION', r'\+|\-|\*|/|\(|\)|\:=|;'), #punctuation
	('SKIP', r'\s'), #whitespace, newline, tab, etc.
	('ERROR', r'.') #anything else
	]
	tokens = '|'.join('(?P<%s>%s)' % pair for pair in lang_tok)
	for x in re.finditer(tokens, line):
		tag = x.lastgroup
		value = x.group()
		if tag == 'ERROR':
			value = ("Invalid token on value %s" % value)
		yield Token(tag, value)


#checks input and calls scanner on each line of the input if it is a valid file
def input_check():
	input_file = ""
	output_file = ""
	scanner_file = sys.argv[0]
	
	#print("args: ", sys.argv)
	while(1):
		if len(sys.argv) != MAX_ARGS:
			print("Error: Input must be <scanner> <input> <output>")
			exit(0)
		input_file = sys.argv[1]
		output_file = sys.argv[2]
		if input_file:
			break
		print("File nonexistent or no read-write access")
	file_o = open(output_file, 'w+')
	with open(input_file, 'r') as file_i:
		line = file_i.readline()
		while line:
			file_o.write(line)
			#tok_list = scanner(lang, line)
			uh_oh = list(tokenize(line))
			for token in tokenize(line):
				print(token)
			for x in uh_oh:
				file_o.write("%s, %s" % (x[0], x[1]))
				file_o.write('\n')
			line = file_i.readline()
	file_i.close()
	file_o.close()
	
	return scanner_file, input_file, output_file


#calls 
def main():
	start = time.time()
	scanner_file, input_file, output_file = input_check()
	finish = time.time()
	print("%s took %3fs to execute with %s \n output written to %s" % (input_file, (float(finish)-float(start)), scanner_file, output_file))



if __name__ == "__main__":
	main()
