# [WIP] A Parallel Algorithm for Subgraph Isomorphism

## Description
Subgraph isomorphism is the problem of determining whether a given graph G is isomorphic to a subgraph of a larger graph H, where an isomorphism is a bijective function that preserves adjacency relations between vertices. 

Formally, given two undirected graphs G and H, the subgraph isomorphism problem is to determine whether there exists a subgraph of H that is isomorphic to G. An isomorphism between two graphs is a bijective function that maps the vertices of one graph to the vertices of the other graph in such a way that the adjacency relations are preserved.

## Usage
```shell
cmake CMakeLists.txt
```
```shell
make 
```

### Download the datasets:

```shell
make download_datasets
```