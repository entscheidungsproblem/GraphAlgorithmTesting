This project focused on the single source shortest path problem (SSSP) and compares multiple algorithms against each other. The algorithms of interest can solve the general case where graphs can have negative edges. A random graph generator was constructed to create large batches of graphs which were used to compare the algorithms average runtimes. This project was written in C++ and makes heavy use of templates to achieve generics for the algorithms and data structures.

Guide:
The program can be broken down into 4 main components:
1. Data Structures: There are currently 2 graph implementations, adjacency matrix and adjacency lists, that share a parent GraphADT. Graphs can be created manually by adding vertices and setting edges but there is no support for removing vertices and edges can only be removed by setting edges to infinity.
2. Algorithms: There are several different types of single source shortest path (SSSP) algorithm implementations. All, except Dijkstras, work with graphs with negative edges. A SSSP template is used to run several algorithms on the same graph and check that the solutions are consistent. 
3. Random Graph Generator: There is a random graph generator that specifies many attributes including acyclic, directed and weights but a Builder is included and encouraged to use instead. It allows for default values and easy parameter selections. A graph convertor is also included to convert between graph implementations.
4. Timer: Compares the speed of different algorithms and graph implementations. Multiple algorithms can be selected to compare using tempate parameters. The number of graphs generated used to test the algorithms is selected when running the timer.



TODO:
1. Implement templates for edge weight value types. 
2. Seperate template for containers to compare performance on each data structure. 
3. Database serialization
4. Create graph analyzer to gets stats on each graph (edge weight distribution, negative cycles, number of cycles). Fix negative cycles afterwards by removing or reweighting edges.
5. Install linter and fix code styling


Notes:
1. Create postgres with graphviz
	dot -Tps graph.dot -o graph.ps
	Or use gen_dot



