from itertools import permutations

cores = (32, 192, 32)
combinacoes = set(permutations(cores))

for c in combinacoes:
    print(c)
