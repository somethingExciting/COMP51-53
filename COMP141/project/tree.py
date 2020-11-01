punctuation = ["+", "-", "*", "/", "(", ")", ":=", ";"]

class Node:
	def __init__(self, data):
		self.left = None
		self.right = None
		self.center = None
		self.data = None

	def insert_left(self, data):
		if self.data:
			if self.left is None:
				self.left = Node(data)
			else:
				self.left.insert(data) 

	def insert_right(self, data):
		if self.data:
			if self.right is None:
				self.right = Node(data)
			else:
				self.right.insert(data)

	def insert_center(self, data):
		if self.data:
			if data in punctuation:
				if self.center is None:
					self.center = Node(data)
				else:
					self.center.insert(data)

	def write_tree(self, file_eval):
		if self.left:
			self.left.write_tree(file_eval)
		file_eval.write(self.data)
		if self.center:
			self.center.write_tree(file_eval)
		file_eval.write(self.data)
		if self.right:
			self.right.write_tree(file_eval)

	def preorder(self, root):
		pre = []
		if root:
			pre.append(root.data)
			pre = pre + self.preorder(root.left)
			pre = pre + self.preorder(root.right)
		return pre

	def print_tree(self):
		if self.left:
			self.left.print_tree()
		print(self.data)
		if self.center:
			self.center.print_tree()
		print(self.data)
		if self.right:
			self.right.print_tree()

	def print_node(self):
		print(self.data)

