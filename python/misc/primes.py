import time

mx, curr, n, div = 10000, 0, 1, 2

start = time.clock()

while curr < mx:
    div = 2
    while div <= n:
        if div == n:
            curr += 1
            break
        elif n % div == 0: 
            break
        div += 1
    n += 1

print(n)

end = time.clock()

print("%s s" % (end - start))