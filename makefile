CPPFLAGS = -std=c++17 -Wall

a.out: adjacency_matrix.o random_graph_generator.o graphBuilder.o bellman_ford.o SPFA.o pape.o Dijkstra.o main.o
	g++ ${CPPFLAGS} adjacency_matrix.o random_graph_generator.o graphBuilder.o bellman_ford.o SPFA.o pape.o Dijkstra.o main.o

graphBuilder.o: RandomGraph/graphBuilder.cpp RandomGraph/graphBuilder.hpp
	g++ ${CPPFLAGS} -c RandomGraph/graphBuilder.cpp

adjacency_matrix.o: DataStructures/adjacency_matrix.cpp DataStructures/adjacency_matrix.hpp
	g++ ${CPPFLAGS} -c DataStructures/adjacency_matrix.cpp

random_graph_generator.o: RandomGraph/random_graph_generator.cpp RandomGraph/random_graph_generator.hpp
	g++ ${CPPFLAGS} -c RandomGraph/random_graph_generator.cpp

bellman_ford.o: Algorithms/bellman_ford.cpp Algorithms/bellman_ford.hpp
	g++ ${CPPFLAGS} -c Algorithms/bellman_ford.cpp

SPFA.o: Algorithms/SPFA.cpp Algorithms/SPFA.hpp
	g++ ${CPPFLAGS} -c Algorithms/SPFA.cpp

pape.o: Algorithms/pape.cpp Algorithms/pape.hpp
	g++ ${CPPFLAGS} -c Algorithms/pape.cpp

Dijkstra.o: Algorithms/Dijkstra.cpp Algorithms/Dijkstra.hpp
	g++ ${CPPFLAGS} -c Algorithms/Dijkstra.cpp

main.o: main.cpp
	g++ ${CPPFLAGS} -c main.cpp
