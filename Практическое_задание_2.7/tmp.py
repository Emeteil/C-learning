import matplotlib.pyplot as plt
import numpy as np

sizes = [100, 300, 500, 700, 900]

thread_counts = [1, 2, 4, 8, 16, 32, 64, 128]

results = [
    [0.0084, 0.0069, 0.0045, 0.0033, 0.0038, 0.0058, 0.0112, 0.0114],
    [0.2693, 0.1293, 0.1015, 0.0866, 0.0915, 0.0834, 0.1034, 0.1001],
    [1.3277, 0.7970, 0.4366, 0.3396, 0.3467, 0.3367, 0.4257, 0.7105],
    [3.9283, 2.1012, 1.3894, 1.1705, 1.1117, 1.1799, 1.3045, 1.8100],
    [9.9049, 5.5175, 3.6889, 3.7509, 3.7577, 3.7469, 3.7161, 3.7414]
]

plt.figure(figsize=(12, 8))
for j in range(len(thread_counts)):
    plt.plot(sizes, [results[i][j] for i in range(len(sizes))], 
             marker='o', label=f'{thread_counts[j]} потоков')

plt.xlabel('Размер матрицы (N x N)')
plt.ylabel('Время выполнения (секунды)')
plt.legend()
plt.grid(True)
plt.savefig('graph.png')
