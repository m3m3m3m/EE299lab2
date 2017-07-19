
import sys

inputfile = sys.argv[1]

def format(parts):
	for part in parts[:-1]:
		tabsize = len(part) // 4 * 4 - len(part) + 4
		yield part + ' ' * tabsize
	yield parts[-1]

with open(inputfile, 'r') as file:
	lines = file.readlines()

outputfile = 'format/' + inputfile.split('\\')[-1]
with open(outputfile, 'w') as file:
	for line in lines:
		parts = line.split('\t')
		# print(parts)
		reform = ''.join(format(parts))
		print(reform, end='')
		file.write(reform)
