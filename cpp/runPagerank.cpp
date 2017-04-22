#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <errno.h>
#include <dirent.h>

#include "table.h"

using namespace std;

const double EPSILON = 0.000001;

void error(const char *p,const char *p2) {
    cerr << p <<  ' ' << p2 <<  '\n';
    exit(1);
}

void error(const string p,const string p2) {
    cerr << p <<  ' ' << p2 <<  '\n';
    exit(1);
}

void usage() {
    cerr << "Usage: pagerank_test [-jp] <test_suite>" << endl
         << " -j use Java test results" << endl
         << " -p use Python test results (default)" << endl;
}

int main(int argc, char *argv[]) {

    //Table t;

    if (argc < 1) {
        usage();
        exit(1);
    }

    string tests_filename = argv[argc - 1];

    //cout<<"*****"<<tests_filename<<endl;

    ifstream tests_file(tests_filename.c_str());

    if (!tests_file.is_open()) {
        error("Cannot open file", tests_filename);
    }

    cout.precision(numeric_limits<double>::digits10);

    vector<string> inputFilesVector;
  	
    while(!tests_file.eof()){
    	string test_line;
    	getline(tests_file, test_line);
    	//cout<<test_line<<endl;
    	//graph_filename = test_line + ".txt";
    	inputFilesVector.push_back(test_line);
    }
    
    int limit=inputFilesVector.size();

    #pragma omp parallel for num_threads(2)
    for(int i=0;i<limit;i++){
    	Table t;
    	string file=inputFilesVector[i];
    	string graph_filename="graphs//" + file + ".txt";
    	//cout<<graph_filename<<endl;
    	string pagerank_filename="graphs//results//" + file + "-result.txt";
    	ifstream pagerank_file(graph_filename.c_str());
    	if (!pagerank_file.is_open()) {
            cerr << endl;
            error("Cannot open pagerank file", pagerank_filename);
        }
        
        ofstream fout;
        fout.open(pagerank_filename);

        t.set_numeric(true);
        t.set_delim(" ");
        t.set_trace(false);
        t.read_file(graph_filename);
        t.pagerank();

        
        if(fout.is_open()){
        	t.print_pagerank_v(fout);
        	fout.close();
        } 	
    }
    return 0;
}