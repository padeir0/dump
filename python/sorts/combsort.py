a = [9, 2, 1, 3, 5, 4, 6, 8, 7, 0, 10]

def combSort(array):
    sorted = False
    k = 1.3
    lenght = len(array)
    gap = lenght - 1

    while not sorted:
        gap /= k
        roundGap = round(gap)
        if gap <= 1:
            gap = 1
            sorted = True
        for i in range(lenght - roundGap):
            if array[i] > array[i + roundGap]:
                a = array[i]
                array[i] = array[i+roundGap]
                array[i+roundGap] = a
                sorted = False
    return array

print(combSort(a))