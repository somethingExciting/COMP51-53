import re
import sys
import time
import collections
import string
import operator
import tree

#global variables
MAX_ARGS = 3			# max amount of arguments in terminal
Token = collections.namedtuple('Token', ['tag', 'value'])	# identifying tokens
token_list = []		 	# list of tokens]
iterator = 0		 	# current token number in tree
root = None				# root node

# language
"""  
([a-z] | [A-Z])([a-z] | [A-Z] | [0-9])*   #IDENTIFIER
[0-9]+									  #NUMBER
\+ | \- | \* | / | \( | \) | := | ;		  #PUNCTUATION
if | then | else | endif | while | do | endwhile | skip  #KEYWORD
"""

"""
function:	tags characters with an indentifier label
input:		line - current line that is being read in from file
output:		Token(tag, value) - a tuple named Token that contains a tag and value
"""
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


"""
function: checks input and calls scanner on each line of the input if it is a valid file
input: N/A
output: scanner_file - name of the scanner file
	s_input_file - name of the sample input file
	s_output_file - name of the sample output file
"""
def input_check_scanner():
	s_input_file = ""
	s_output_file = ""
	scanner_file = sys.argv[0]
	
	#print("args: ", sys.argv)
	while(1):
		if len(sys.argv) != MAX_ARGS:
			print("Error: Input must be <scanner> <input> <output>")
			exit(0)
		s_input_file = sys.argv[1]
		s_output_file = sys.argv[2]
		if s_input_file:
			break
		print("File nonexistent or no read-write access")
	file_o = open(s_output_file, 'w+')
	with open(s_input_file, 'r') as file_i:
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
	
	return scanner_file, s_input_file, s_output_file


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
function: checks if current token has ;
input: file_o - evaluator file that is being written to
output: N/A
"""
def statement(file_o):
	global iterator
	if token_list[0] == ";":
		iterator+=1
		basestatement(file_o)
	else:
		basestatement(file_o)
	return


"""
function: checks if the current token belongs in assignment or ifstatement or whilestatement or skip
input: file_o - evaluator file that is being written to
output: N/A
"""
def basestatement(file_o):
	global iterator
	if token_list[iterator] == "if":
		iterator+=1
		ifstatement(file_o)
	elif token_list[iterator] == "while":
		iterator+=1
		whilestatement(file_o)
	elif token_list[iterator] == ":=":
		iterator+=1
		assignment(file_o)
	elif token_list[iterator] == "SKIP":
		iterator+=1
		basestatement()
	else:
		print("2 error at base: ", token_list[iterator])
		return	
	return


"""
function: checks if the current token has := 
input: file_o - evaluator file that is being written to
output: N/A
"""
def assignment(file_o):
	global iterator
	if token_list[iterator] == ":=":
		iterator+=2
		root = Node("base")
		root.insert_left("IDENTIFIER")
		root.insert_center(":=")
		expression(file_o)
	else:
		print("3 error at assignment: ", token_list[iterator])
		return
	return


"""
function: checks if the current token has "if" or "then" or "else" or "endif"
input: file_o - evaluator file that is being written to
output: N/A
"""
def ifstatement(file_o):
	global iterator
	if token_list[iterator] == "if":
		iterator+=4
		root = Node("base")
		root.insert_left("if")
		expression(file_o)
		root.insert_right("then")
		statement(file_o)
		root.insert_left("else")
		statement(file_o)
		root.insert_right("endif")
	else:
		print("4 error at if: ", token_list[iterator])
		return
	return


"""
function: checks if the current token has/is "while" or "do" or "endwhile"
input: file_o - evaluator file that is being written to
output: N/A
"""
def whilestatement(file_o):
	global iterator
	if token_list[iterator] == "while":
		iterator+=3
		root = Node("base")
		root.insert_left("while")
		expression(file_o)
		root.insert_right("do")
		statement(file_o)
		root.insert_left("endwhile")
	else:
		print("5 error at while: ", token_list[iterator])
		return
	return


"""
function: checks if the current token has/is +
input: file_o - evaluator file that is being written to
output: N/A
"""
def expression(file_o):
	global iterator
	if token_list[iterator] == "+":
		iterator+=1
		root.insert_center("+")
		term(file_o)
	else:
		print("6 error at expression: ", token_list[iterator])
		return
	return


"""
function: checks if the current token has/is -
input: file_o - evaluator file that is being written to
output: N/A
"""
def term(file_o):
	global iterator
	if token_list[iterator] == "-":
		iterator+=1
		root.insert_center("-")
		factor(file_o)
	else:
		print("7 error at term: ", token_list[iterator])
		return
	return


"""
function: checks if the current token has/is /
input: file_o - evaluator file that is being written to
output: N/A
"""
def factor(file_o):
	global iterator
	if token_list[iterator] == "/":
		iterator+=1
		root.insert_center("/")
		piece(file_o)
	else:
		print("8 error at factor: ", token_list[iterator])
		return 
	return


"""
function: checks if the current token has/is *
input: file_o - evaluator file that is being written to
output: N/A
"""
def piece(file_o):
	global iterator
	if token_list[iterator] == "*":
		iterator+=1
		root.insert_center("*")
		element(file_o)
	else:
		print("9 error at piece: ", token_list[iterator])
		return 
	return


"""
function: checks if the current token has/is ( ) or NUMBER or IDENTIFIER
input: file_o - evaluator file that is being written to
output: N/A
"""
def element(file_o):
	global iterator
	if token_list[iterator] == "(":
		iterator+=1
		root.insert_left("(")
		expression(file_o)
		root.insert_right(")")
	elif token_list[iterator].isdigit():
		root.insert_left("NUMBER")
		root.print_tree()
		root.write_tree(file_o)
		return
	elif token_list[iterator].isalpha():
		root.insert_left("IDENTIFIER")
		root.print_tree()
		root.write_tree(file_o)
		return
	else:
		print("10 error at element: ", token_list[iterator])
		return
	return
	

"""
function:	creates a list of tokens
input:		line - a single line from the file read in
output:		N/A
"""
def check_toks(line):
	ok = ["IDENTIFIER", "NUMBER", "PUNCTUATION", "KEYWORD", "SKIP"]
	if (line in ok) or (line.startswith("ERROR")):
		return
	else:
		token_list.append(line) 


"""
function: reads input from scanner, writes to parser output file, calls parsing functions on generated token list
input:	  scanner_ouput - name of specified scanner output file (a.k.a input file)
		  parser_output - name of specified parser output file (a.k.a output file)
output:   N/A
"""
def input_check_parser(scanner_output, parser_output):
	NoneType = type(None)

	file_o = open(parser_output, 'w+')	
	with open(scanner_output, 'r') as file_i:
		contents = file_i.readlines()
		for line in contents:
			line = (line.strip('\n')).split(",")
			line = (''.join(line)).strip()
			if (isinstance(line, NoneType)):
				pass
			else:
				check_toks(line)
		if len(token_list) <= 0:
			print("Expression not in grammar or no tokens given")
			return
		statement(file_o)
	file_i.close()
	file_o.close()


"""
function: transforms string operator from array into a math operator
input: op - string operator to be transformed into math operator
output: [op] - mapping of character to math operator
"""
def get_operator(op):
	return { "+": operator.add, 
			"-": operator.sub, 
			"*": operator.mul, 
			"/": operator.truediv, 
			":=": operator.setitem 
			} [op]


"""
function: turns the equation array into a math equation to solve
input: eq - equation in array format
output: the integer answer of the evaluated math equation
"""
def evaluator(eq):
	ans = 0
	for x in eq:
		if x in string.punctuation:
			val1, val2 = int(eq[x-1]), int(eq[x+1])
			ans = get_operator(eq[x])(val1, val2) 
	return ans


"""
function: creates an equation array 
input: tree - the parse tree to be evaluated
output: equation - the generated equation to be evaluated
"""
def gen_eq(tree):
	equation = []
	for x in tree:
		if tree[x].isdigit():
			equation.append(int(tree[x]))
		elif tree.data in string.punctuation:
			equation.append(tree[x])
		else:
			print("not a thing")
	return equation


"""
function: reads input from parser output and writes to evaluator output file
input: parser_output - parse tree written to output file
eval_output - evaluation of the parse tree written to output file
output: N/A
"""
def input_check_eval(parser_output, eval_output):
	file_o = open(eval_output, 'w+')
	with open(parser_output, 'r') as file_i:
		contents = file_i.readlines()
		eq = gen_eq(contents)
		ans = evaluator(eq)
		print("Evaluator got solution ", ans)
		file_o.write(str(ans))
	file_i.close()
	file_o.close()			


# driver
def main():
	# scanner
	scanner_file, s_input_file, s_output_file = input_check_scanner()
	print("%s executed with %s. Output written to %s.\n" % (s_input_file, scanner_file, s_output_file))

	# parser
	parser_output = "parser_output.txt"
	input_check_parser(s_output_file, parser_output)
	print("Created a parse tree with %s. Written to file %s.\n" % (s_output_file, parser_output))	

	# evaluator
	eval_output = "evaluator_output.txt" 
	input_check_eval(parser_output, eval_output)
	print("Evaluated the parse tree with %s. Written to file %s.\n" % (parser_output, eval_output));	


# run main
if __name__ == "__main__":
	main()
