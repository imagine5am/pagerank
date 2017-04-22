This is parallelization of the Pagerank implementation. Multiple graphs can be taken as input. Pagerank of each graph is calculated simultaneously.

The Pagerank implementation does not belong to me.

The project uses OpenMP to parallelize the code.

The 'graphs' folder consists of all the input graphs. 'all-graphs.txt' consists of all the filenames. The pagerank of all the files and stored in folder './graphs/results'. 

To add graphs to be calculate pagerank, add the graph file to 'graphs' folder and add its entry in 'all-graphs.txt'.

The graph file consists of &lt;from&gt;&lt;delim&gt;&lt;to&gt;. The delim is a space(' ') character.
<hr>

<h1>Building:</h1>
To build the file:

<code>g++ -o pagerank -fopenmp runPagerank.cpp table.cpp table.h</code>

To run the program:

<code>./pagerank ./graphs/all-graphs.txt</code>
