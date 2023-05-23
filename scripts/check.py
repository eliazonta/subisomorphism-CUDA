import networkx as nx
import matplotlib.pyplot as plt
# [WIP]

G = nx.path_graph(5)
G.add_edge(2, 5)

H = nx.path_graph(5)
H.add_edge(3, 5)
print(nx.is_isomorphic(G, H))

plt.subplot(221)
nx.draw_shell(G)
plt.title("G", fontweight="bold")
plt.subplot(222)
nx.draw(H, node_color="r")
plt.title("H", fontweight="bold")
plt.show()


