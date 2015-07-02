#!/usr/bin/python

# Simple script to normalize the trace results from PaciWar
#
# It takes the first time result and use it as time 0.

import sys
import os

if len(sys.argv) != 3:
	print "You should pass the trace file as argument to this script and the file to write"
	sys.exit(-1)

traceFileName = sys.argv[1]
outputFileName = sys.argv[2]
if not os.path.exists(traceFileName):
	print "The file you specified does not exists"
	sys.exit(-2)
if not os.path.isfile(traceFileName):
	print "You did not specified a file"
	sys.exit(-3)
	
baseTime = 0
outputFile = open(outputFileName,'w')
with open(traceFileName, 'r') as traceFile:
	for line in traceFile:
		values = line.split(';')
		if len(values) != 2:
			print "Looks as an invalid file"
			sys.exit(-4)
		
		try:
			if baseTime != 0:
				baseTime = int(values[0])
			outputFile.write(str(int(values[0])-baseTime) + ";" + values[1])
		except ValueError:
			print "Fail to convert value from file"
			sys.exit(-5)

outputFile.close()

sys.exit(0)
