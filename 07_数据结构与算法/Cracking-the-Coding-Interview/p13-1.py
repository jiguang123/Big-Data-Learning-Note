import sys
import os
import os.path

if __name__ == '__main__':
	if len(sys.argv) == 1 or len(sys.argv) > 3:
		print "Usage: python p13-1.py [FILE NAME] [k]"
		print "Description: output the last k lines of a file."
		sys.exit(0);
	if len(sys.argv) == 2:
		k = 5
	if len(sys.argv) == 3:
		k = int(sys.argv[2])
		k = 5 if k <= 0 else k
	file_name = sys.argv[1]
	if os.path.isfile(file_name) == False:
		print "File \"%s\" is not found." % file_name
		sys.exit(1)
	file = open(file_name, 'r')
	lines = file.readlines()
	file.close()
	k = len(lines) if k > len(lines) else k
	line_count = len(lines)
	for i in range(line_count - k, line_count):
		print lines[i],
	