
1.Introduction

FEWS is a First_Edge_Wedge Sampling sampling algorithm, which is used to approximate count global triangles in large sparse graph streams. 

	We all assume that the graphs are undirected, and the graphs themselves have no self-loops.
	FEWS can accurately and quickly count triangles in large sparse graph streams. 


2.Test Data

	The FEWS algorithm approximately counts global triangles in large graph streams. The datasets are in .txt format, where each dataset contains three pieces of information {source node, destination node, edge addition/deletion}. The real datasets we use in the paper can be downloaded from the following website: http://snap.stanford.edu.


3.The usage attention

    Make sure your C++ build environment has the boost 1_55_0 library.
    CMake,Build and run our program in the 'FEWS_Counter/cmake-build-debug' directory.
    
4.Parameter Settings

The format of a parameter of FEWS in the command line is a pair of strings, here we denote the pair as (-p : [q]) or (-p : q). String p is the name of the parameter. String q is the value of the parameter input in the command line. [q] represents that the parameter is a optional parameter. q represents that the parameter is a necessary parameter.

@parameter (-g : [graph.txt])

	Parameter 'g' gives the file name of a dataset. For example, '-g'="exapmle.txt", example.txt is a text file.

@parameter (-method: [method])

	Parameter 'method' selects the counting method during the experimental test.

@parameter (-budget : [memory-cost])

	The maximum number of edges our program can store.
	
@parameter (-M :[reservoir-size])

	The initial allocated size of our reservoir, its length should not exceed budget.
	
@parameter (-seed:  [random seed])

	Parameter 'seed' determines the number of experiments for this method. In fact, it is for multiple experiments to reduce experimental errors. 

@parameter (-T:  max-neighborList-size)

	The max size of NeiborList
	
@parameter (-fw:  first-weight of neighborList)

	the probability of a neighbor sampled in NeiborList

5.Usage Notes
1)O method. 

Running test:

	$ ./FEWS_Counter -g example.txt -method O -budget 20000 -M 18000 -fw 0.8 -T 10 -seed 1

    Input files:
		A insertion-only graph dataset: example.txt
    Output files:
		When the reservoir capacity is 20000, the approximate result of the global triangle in the graph.

2)I method. 

Running test:

	$ ./FEWS_Counter -g example.txt -method I -budget 20000 -M 18000  -fw 0.8 -seed 1

    Input files:
		A insertion-only graph dataset: example.txt
    Output files:
		When the reservoir capacity is 20000, the approximate result of the global triangle in the graph.


3)F method. 

Running test:

	$ ./FEWS_Counter -g example_FD.txt -method F -budget 20000 -fw 0.8 -M 18000 -seed 1.

	Input files:
		A fully-dynamic graph dataset: example_FD.txt
	Output files:
		When the reservoir capacity is 20000, the approximate result of the global triangle in the graph.


    



