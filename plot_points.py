import sys
import matplotlib.pyplot as plt

def plot_ordered_pairs(pairs, cost):
    # Separa os pares ordenados em coordenadas X e Y
    x_vals, y_vals = zip(*pairs)
    
    # Cria o gráfico
    plt.figure()
    
    # Plota os pontos conectados por linhas
    plt.plot(x_vals, y_vals, marker='o', linestyle='-', color='b')
    
    # Adiciona rótulos e grade
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title(f'Custo: {cost}')
    plt.grid(True)
    
    # Mostra o gráfico
    plt.show()

def main():
    # Verifica se os parâmetros foram passados corretamente
    if len(sys.argv) < 2:
        print("Uso: python plot_points.py custo x1,y1 x2,y2 ...")
        sys.exit(1)

    # O primeiro parâmetro é o custo
    try:
        cost = float(sys.argv[1])
    except ValueError:
        print(f"Custo inválido: {sys.argv[1]}")
        sys.exit(1)

    # Converte os argumentos restantes em pares ordenados
    pairs = []
    for arg in sys.argv[2:]:  # Começa a partir do segundo argumento
        try:
            x, y = map(float, arg.split(','))
            pairs.append((x, y))
        except ValueError:
            print(f"Par inválido: {arg}")
            sys.exit(1)
    
    # Plota os pares ordenados
    plot_ordered_pairs(pairs, cost)

if __name__ == "__main__":
    main()
