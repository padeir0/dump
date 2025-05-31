import matplotlib.pyplot as plt

# constante gravitacional
G = 1

class Vetor:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return f"({self.x}, {self.y})"

    def __add__(self, other):
        return Vetor(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Vetor(self.x - other.x, self.y - other.y)

    def escalar(self, other):
        return Vetor(other * self.x, other * self.y)

    def produto_interno(self, other):
        return self.x * other.x + self.y * other.y

    def norma(self):
        return (self.x ** 2 + self.y ** 2) ** 0.5

    def nova_norma(self, valor):
        return self.unit().escalar(valor)

    def eh_nulo(self):
        return self.x == 0 and self.y == 0

    def unit(self):
        if self.eh_nulo():
            raise Exception("vetor não deveria ser nulo")
        return self.escalar(1/self.norma())

    def coordenadas(self):
        coord = (self.x, self.y)
        return coord

class Particula:
    def __init__(self, posicao, velocidade, massa):
        self.pos = posicao
        self.vel = velocidade
        self.massa = massa

    def calcular_aceleracao(self, particulas):
        a = Vetor(0, 0)
        for other in particulas:
            if other is not self:
                desloc = other.pos - self.pos
                dist = max(desloc.norma(), 1e-3)
                a_inc = G * other.massa / (dist ** 2)
                a = a + desloc.unit().escalar(a_inc)
        return a

    def atualizar(self, acel, dt):
        self.vel = self.vel + acel.escalar(dt)
        self.pos = self.pos + self.vel.escalar(dt)

def passo(particulas, dt):
    para_atualizar = []
    for p in particulas:
        par = (p, p.calcular_aceleracao(particulas))
        para_atualizar += [par]
    for par in para_atualizar:
        p = par[0]
        acel = par[1]
        p.atualizar(acel, dt)
    return [p.pos.coordenadas() for p in particulas]

# recebemos uma lista onde cada elemento
# é uma lista das posições das particulas naquele passo.
# para podermos plotar, queremos uma lista onde cada
# elemento corresponde às posições de uma única particula
def transpose(posições):
    return [list(linha) for linha in zip(*posições)]

def simular(particulas, num_passos, dt=0.01):
    out = []
    for i in range(num_passos):
        if i % 100 == 0:
            print(f"\r{i}/{num_passos}", end="", flush=True)
        out += [passo(particulas, dt)]
    return transpose(out)

def perm(rgb):
    from itertools import permutations
    return list(set(permutations(rgb)))

cores = (
        []
        + perm((0.8, 0.2, 0.2))
        + perm((0.8, 0.8, 0.2))
        + [(0.8, 0.8, 0.8)]
)
escolha = 0

def rgb():
    global escolha
    cor = cores[escolha]
    escolha = (escolha + 1) % len(cores)
    return cor

def gerar_plot(posições, nome):
    fig, ax = plt.subplots()
    for particula in posições:
        x, y = zip(*particula)
        ax.plot(x, y, color = rgb())
        ax.plot(x[-1], y[-1], 'o')

    ax.set(xlabel="", ylabel="",
           title="")
    ax.grid()
    fig.savefig(nome)

def print_cond(cond):
    for key in cond:
        obj = cond[key]
        print(key, ":", obj)

def pvi(cond):
    for key in cond:
        obj = cond[key]
        if isinstance(obj, tuple) and len(obj) == 2:
            cond[key] = Vetor(obj[0], obj[1])

    p1 = Particula(cond["r1"], cond["v1"], cond["m1"])
    p2 = Particula(cond["r2"], cond["v2"], cond["m2"])
    p3 = Particula(cond["r3"], cond["v3"], cond["m3"])
    particulas = [p1, p2, p3]
    return simular(particulas, 100_000, dt=0.005)

def orbita_euler_instavel():
    cond = {
        "r1": (-10, 0), "v1": (0, -0.3),   "m1": 1,
        "r2": (0, 0),   "v2": (0, 0),      "m2": 1,
        "r3": (10, 0),  "v3": (0, 0.3001), "m3": 1,
    }
    gerar_plot(pvi(cond), "euler_instavel.png")

def orbita_euler_estavel():
    cond = {
        "r1": (-10, 0), "v1": (0, -0.3), "m1": 1,
        "r2": (0, 0),   "v2": (0, 0),    "m2": 1,
        "r3": (10, 0),  "v3": (0, 0.3),  "m3": 1,
    }
    gerar_plot(pvi(cond), "euler_estavel.png")

if __name__ == "__main__":
    orbita_euler_estavel()
    orbita_euler_instavel()
