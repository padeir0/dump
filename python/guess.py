import random, time
# Q1w0-E2r9
print("\n" + "Think of a number and enter a range.")
enter = [int(x) for x in input("Enter range: ").split(', ')]
min, max = enter[0], enter[1]

num = random.randint(min, max)
print(num)

while True:
    ask = input('Is it correct? (y/n) ')
    if ask == 'y':
        print('HELL YEAH')
        time.sleep(1)
        break
    elif ask == 'n':
        highlow = input('Is the guess to high or too low? (h/l) ')
        if highlow == 'l':
            min = num + 1
            num = random.randint(min, max)
        elif highlow == 'h':
            max = num - 1
            num = random.randint(min, max)
        print(num)

print('Goodbye!')
time.sleep(5)