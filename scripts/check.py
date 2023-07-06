import networkx as nx
import argparse


def read_graph(filename):
	g = nx.Graph()
	for row in open(filename, 'r'):
		lines = [i for i in row.split()]
		g.add_edge(lines[0], lines[1])
	return g


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Returns True if a subgraph of G1 is isomorphic to G2.')
    parser.add_argument('--g1', type=str, default='', help='graph1')
    parser.add_argument('--g2', type=str, default='', help='graph2')
    args = parser.parse_args()
    g1 = read_graph(args.g1)
    g2 = read_graph(args.g2)
    matcher = nx.isomorphism.GraphMatcher(g1, g2)
    result = matcher.subgraph_is_isomorphic()
    print(result)