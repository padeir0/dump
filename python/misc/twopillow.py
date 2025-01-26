from PIL import Image
import random as rnd

size = [10, 100]
pi_mage = Image.new("RGB", size)

file = open(r"C:\Users\Usuario\Desktop\pyscripts\Challenges\scyenv\fibbonacci.txt", 'r')

def color(number):
    if int(number) % 2 == 0:
        return (0, 150, 150)
    else:
        return (0, 0, 0)

for i in range(10):
    for j in range(100):
        n = file.readline()
        if n != "":
            pi_mage.putpixel([i, j], color(n))

pi_mage.show()

file.close()
if not file.closed:
    file.close()