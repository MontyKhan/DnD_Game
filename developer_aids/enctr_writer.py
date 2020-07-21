import re

filepath = "/home/robert/DnD_Helper/stats/encounter1.csv"
output = open("/home/robert/DnD_Helper/stats/encounter1.enctr", "w")

# print input.read()

output.write("<encounter>\n")									# First encapsulating tag
with open(filepath) as input:
	line = input.readline()									# Discard headings
	line = input.readline()
	count = 1
	while line:
		line = line.replace("\n", "")
		line_contents = re.split(",", line)
		
		output.write("\t<monster>\n")							# Start monster tag.

		output.write("\t\t<name>{}</name>\n".format(line_contents[0]))			# Set name string.
		output.write("\t\t<ac>{}</ac>\n".format(line_contents[1]))			# Set AC value.
		output.write("\t\t<hp>{}</hp>\n".format(line_contents[2]))			# Set HP value.
		output.write("\t\t<speed>{}</speed>\n".format(line_contents[3]))			# Set Speed value.
		output.write("\t\t<initiative>{}</initiative>\n".format(line_contents[4]))	# Set Initiative value.
		
		# Set weapon variables
		output.write("\t\t<weapon>\n")							# Start weapon tag.
		output.write("\t\t\t<name>default</name>\n")					# Set weapon name to default.
		output.write("\t\t\t<range>5</range>\n")						# Set weapon range.
		output.write("\t\t\t<attack>{}</attack>\n".format(line_contents[5]))		# Set weapon attack modifier.
		output.write("\t\t\t<damage>{}</damage>\n".format(line_contents[6]))		# Set damage roll.
		output.write("\t\t</weapon>\n")							# End tag.

		output.write("\t</monster>\n\n")							# End monster tag

		line = input.readline()
		
		print(line)									# Print to console for debugging.
output.write("</encounter>")

output.close()
