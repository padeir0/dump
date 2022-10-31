import math, random as rnd

def pDistance(p0, p1):
    if len(p0) == 2:
        return ((p1[0] - p0[0]) ** 2 + (p1[1] - p0[1]) ** 2) ** 0.5
    elif len(p0) == 3:
        return ((p1[0] - p0[0]) ** 2 + (p1[1] - p0[1]) ** 2 + (p1[2] - p0[2]) ** 2) ** 0.5

def rightorleft(a, b):
    if b[0] - a[0] == 0:
        return 1
    else:
        return (b[0] - a[0])/abs(b[0] - a[0])

def pAngle(p0, p1, p2):
    a = pDistance(p1, p2)
    b = pDistance(p0, p2)
    c = pDistance(p0, p1)
    return rightorleft(p1, p2) * math.degrees(math.acos((c ** 2 + b ** 2 - a ** 2) / (2 * b * c)))

def nPoint(posstart, step, angle):
    return int(posstart[0] - math.sin(math.radians(angle)) * step), int(posstart[1] - math.cos(math.radians(angle)) * step)

def rVel(x, y, z = 0):
    return ((x ** 2) + (y ** 2) + (z ** 2)) ** 0.5

if __name__ == "__main__":
    a = (0, 0)
    b = (5, 0)
    c = (5, 5)
    d = (5, -5)
    e = (-5, 0)
    f = (0, 5)
    g = (0, -5)
    h = (-5, 5)
    i = (-5, -5)

    print(rightorleft(b, c))
    print(rightorleft(b, d))
    print(rightorleft(e, h))
    print(rightorleft(e, i))

    print(pAngle(a, b, c))  #-45
    print(pAngle(a, b, d))  #+45
    print(pAngle(a, e, c))  #+135
    print(pAngle(a, e, d))  #-135