Jonathan Woolf, 10808626
Language Used: C++
OS Used: Linux (Ubuntu)

Structure (I wasn't sure what to include here so here is a lengthy description of the code):
  There are two header files which define two node types: MapNode and TreeNode. MapNode is used for representing a node from the map loaded from the input file. TreeNode is used when branching out on the uniform-search algorithm. main.cpp is where the main function is located and where the search takes place.
  First the program checks if there are 4 arguments. After it reads in the inputs and stores them into a map data structure consisting of city names for keys and MapNode pointers for values. The MapNode structure contains the information about edges for any given node. After the data is read from the file, the program checks if the two city arguments are valid (that is they exist in the input file). After these perliminary steps the uniform search begins.
  First a initial node is created with the start city. This is pushed into the queue which is simply a linked list. A while loop begins which will only break when the current node is the goal or the goal is unreachable. Instead of using a preliminary DFS to determine if the paths are connected, a max length is caluculated from the input file. This length is equal to the summation of all edges, as the longest possible path would be a straight line with the goal and start on opposite ends. So if the current path exceeds that max length, there is no way for the cities to be connected.
  The current node is popped from the queue (equal to the node with the shortest accumulated path). From this, a child node is created for each edge branching from the current nodes city. The child nodes accumulated path is set to the length of the edge plus the current nodes accumulated path. The parent node of the child is set to the current node. After this a few optimization steps occur to prevent flooding of the queue. The queue is check if it already contains a node with the same city as a child node. If it does, it is then checked if the child nodes accumulated path length is less than the queues. If it is, the queues is replaced with the child.
  Finally, the queue is sorted to have the first element be the node with the shortest path and the loop is repeated.

Compilation and Execution:
  To compile, execute "make" in the directory. This will create the find_route program in the same directory from which execution can be preformed. Running is exactly as specified:
  
  ./find_route input_filename origin_city destination_city
