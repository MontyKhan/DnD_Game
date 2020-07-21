import re

filepath = "/home/robert/DnD_Helper/stats/encounter1.csv"
output = open("/home/robert/DnD_Helper/stats/encounter1.enctr", "w")

# print input.read()

with open(filepath) as input:
	line = input.readline()
	line = input.readline()
	line_contents = re.split(",", line)
	count = 1
	while line:
		output.write("<monster name=\"")
		output.write(line_contents[0])
		output.write("\" AC=\"")
		output.write(line_contents[1])
		output.write("\" HP=\"")
		output.write(line_contents[2])
		output.write("\" Spd=\"")
		output.write(line_contents[3])
		output.write("\" Init=\"")
		output.write(line_contents[4])
		output.write("\">\n")
		output.write("\t<weapon name=\"")
		output.write("default")
		output.write("\" Range=\"5\" Attack=\"")
		output.write(line_contents[5])
		output.write("\" Damage=\"")
		line_contents[6] = line_contents[6].replace("\n", "")
		output.write(line_contents[6])
		output.write("\"/>\n")
		output.write("</monster>\n\n")
		line = input.readline()
		line_contents = re.split(",", line)
		
		print(line)

output.close()
