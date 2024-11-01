import matplotlib.pyplot as plt
import pandas as pd

# Ler o arquivo CSV gerado pelo programa C++
data = pd.read_csv('costs.csv')

# Pegar os valores de geração e custo
generations = data['Generation']
costs = data['Cost']

# Criar o gráfico
plt.figure(figsize=(10, 6))
plt.plot(generations, costs, label='Best Individual Cost', color='b', marker='o')

# Adicionar título e rótulos
plt.title('Cost per Generation in TSP')
plt.xlabel('Generation')
plt.ylabel('Cost')
plt.grid(True)
plt.legend()

# Mostrar o gráfico
plt.show()
