
#include "Basic.h"

#include "FEWS_Count.h"
#include "FEWS_Improve.h"
#include "FEWS_FullyDynamic.h"

void print_usage() {
    cout << "FEMW Reachability Index" << endl;
    cout << "a usage case :./FEMW_Counter -g roadNet-CA-U.txt -method O -budget 20000 -fw 0.8 -M 18000  -T 10 -seed 8 " << endl;
    cout << "Description:\n"
            "-g  the name of the input graph \n"
            "-budget  the maximum amount of memory space consumed by our program  \n"
            "-M  the initial allocation size of the reservoir \n"
            "-method  the FEWS version ,I:FEWS-IMPR,O:FEWS-OPT\n"
            "-T  the max size of NeiborList \n"
            "-fw the probability of a neighbor sampled in NeiborList\n"
            << endl;
}
int main(int argc, char *argv[])
{
    char *input_graph_filename;
    char Method=' ';
    string h="";
    int random_seed;
    F_N_weight=1;

    for (int i = 0; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-g") {         // graph file
            input_graph_filename = argv[++i];
        }else if (arg == "-method") {
            Method = argv[++i][0];
        }else if (arg == "-seed") {
            random_seed = atoi(argv[++i]);
        }else if (arg == "-h") {
            h = "help";
        }else if(arg == "-budget"){
            Budget =atoi(argv[++i]);
            M=Budget;
        }else if(arg == "-fw"){
            F_N_weight=atof(argv[++i]);
        }else if(arg == "-T"){
            Threshold =atoi(argv[++i]);
        }else if(arg == "-M"){
            M=atoi(argv[++i]);
        }
    }
   srand(random_seed);
    if(h == "help") {
        print_usage();
        return 1;
    }
    if(Method=='O')
    {
        FEMW(input_graph_filename);
    }
    else if(Method=='I')
    {
       FEMW_Improve(input_graph_filename);
    }
    else if(Method=='F')
    {
        FEMW_FullyDynamic(input_graph_filename);
    }
}


