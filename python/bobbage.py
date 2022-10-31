string = ""

for n in range(100000):
    s = n ** 2
    if str(s)[-6:] == "269696":
        string += str(n) + "  :  " + str(s) + "\n"

with open("output.txt", 'w') as output:
    output.write(string)