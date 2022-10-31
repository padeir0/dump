def isprime(num):
    i = 2
    while i < num:
        if num % i == 0:
            return False
        i += 1
    else:
        return True

def primelist(mx):
    output, num = [], 2
    while len(output) < mx:
        if isprime(num):
            output.append(num)
        num += 1
    return output

def primorial(mx):
    output = 1
    for item in primelist(mx):
        output *= item
    return output

# print(sum(primelist(100)))
# print(primorial(100))
print(primelist(100))