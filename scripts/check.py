import networkx as nx
import matplotlib.pyplot as plt

g = nx.Graph()
for row in open('data/gowalla.txt', 'r'):
    lines = [i for i in row.split()]
    g.add_edge(lines[0], lines[1])
g.number_of_edges()
nx.draw(g)
plt.show()


