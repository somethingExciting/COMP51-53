import re
import time 
import sys
from anytree import Node, RenderTree

#global variables
MAX_ARGS = 3		 # maximum amount of arguments in terminal
token_list = []		 # list of tokens
root = Node("")		 # root node
prev_node = Node("") # previous node in tree
word_count = 0		 # current token number in tree

#grammar
"""
statement → basestatement { ; basestatement }
basestatement → assignment | ifstatement | whilestatement | skip
assignmet → IDENTIFIER := expression
ifstatement → "if" expression "then" statement "else" statement "endif"
whilestatement → "while" expression "do" statement "endwhile"

expression → term { + term }
term → factor { - factor }
factor → piece { / piece }
piece → element { * element }
element → ( expression ) | NUMBER | IDENTIFIER
"""

"""
function:	creates a parse tree with given tokens
input:		word - the token that is being added to the parse tree
output: 	N/A 
"""
def node_gen(word):
	if word_count == 0:
		root = Node(word)
	elif word_count >= 1 and word_count <= 2: 
		child = Node(word, parent=root)
		prev_node = child
	else:
		child = Node(word, parent=prev_node)
	

"""
function:	creates a parse tree from valid grammars
input:		token_list - list of tokens to generate the parse tree with
output:		N/A
"""
def expression(token_list, parser_output):
	for tok in token_list:
		if tok != ' ' or not tok.isspace():
			if tok.startswith("IDENTIFIER", 0, len(tok)) and word_count == 0:
				node_gen(tok)
				word_count += 1
			if tok.startswith("NUMBER", 0, len(tok)) and (word_count == 0 or word_count == 1):
				node_gen(tok)
				word_count += 1
			if tok.startswith("PUNCTUATION", 0, len(tok)) and (word_count == 0 or word_count == 1 or word_count == 2):
				node_gen(tok)
				word_count += 1
			if tok.startswith("KEYWORD", 0, len(tok)) and (word_count == 0 or word_count == 1 or word_count == 2 or word_count == 3):
				node_gen(tok)
				word_count += 1
			if (not tok.startswith("IDENTIFIER", 0, len(tok))) or (not tok.startswith("NUMBER", 0, len(tok))) or (not tok.startswith("PUNCTUATION", 0, len(tok))) or (not tok.startswith("KEYWORD", 0, len(tok))):
				print("<%s>: Invalid in grammar or invalid token" % tok)
		if tok is ' ' or tok == ' ' or tok.isspace() or not tok.isalpha() or not tok.isnumeric():
			word_count = 0
			for pre,fill, node in RenderTree(root):
				print(root)
				print("%s %s" % (pre, node.name))
				parser_output.write("%s %s" % (pre, node.name))


"""
function:	creates a list of tokens
input:		line - a single line from the file read in
output:		N/A
"""
def check_toks(line):
	ok = ["IDENTIFIER", "NUMBER", "PUNCTUATION", "KEYWORD"]
	if (line in ok) or (line.startswith("ERROR")):
		return
	else:
		token_list.append(line) 


"""
function: reads input from specified file, writes to specified output file, calls parsing functions on generated token list
input:	  N/A
output:   scanner_ouput - name of specified scanner output file (a.k.a input file)
		  parser_output - name of specified parser output file (a.k.a output file)
		  parser		- name of parser source file
"""
def input_check():
	scanner_output = ""
	parser_output = ""
	parser = sys.argv[0]
	NoneType = type(None)

	while(1):
		if len(sys.argv) != MAX_ARGS:
			print("Error: Input is <parser> <scanner_output> <parser_output>")
			exit(0)
		scanner_output = sys.argv[1]
		parser_output = sys.argv[2]
		if scanner_output:
			break
		print("File non-existent or no read-write access")
	file_o = open(parser_output, 'w+')	
	with open(scanner_output, 'r') as file_i:
		contents = file_i.readlines()
		for line in contents:
			line = (line.strip('\n')).split(",")
			line = (''.join(line)).strip()
			not_ok = ["SKIP", "\n"] 
			#print("the current line is: %s" % line)
			if (line in not_ok) or (isinstance(line, NoneType)):
				pass
			else:
				check_toks(line)
		#print("token_list: %s & len(token_list): %i" % (token_list, len(token_list)))
		if len(token_list) <= 0:
			print("Expression not in grammar or no tokens given")
			return
		expression(token_list, file_o)
		#file_o.write(RenderTree(root)) 		
	file_i.close()
	file_o.close()

	return scanner_output, parser_output, parser


#main driver
def main():
	start = time.time()
	scanner_output, parser_output, parser = input_check()
	finish = time.time()
	print("%s took %3fs to create a parse tree with %s. Written to file %s" % (parser, (float(finish) - float(start)), scanner_output, parser_output))


#run main
if __name__ == "__main__":
	main()
