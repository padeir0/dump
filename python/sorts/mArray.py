import random
def unordArray(lenght):
    output = []
    i = lenght
    while i:
        rnd = random.randint(1, lenght)
        if rnd not in output:
            output.append(rnd)
            i -= 1
    return output

def ordArray(lenght):
    output = []
    for i in range(1, lenght + 1):
        output.append(i)
    return output

if __name__ == "__main__":
    print(ordArray(10))
    print(unordArray(10))