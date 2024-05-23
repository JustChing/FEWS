
#include "Basic.h"

pair<unsigned,unsigned> *p_reservoir;

unsigned M;
unsigned Budget;
double NeighborSize;
unsigned res_cur_size;
int Threshold;
double F_N_weight;


boost::unordered_map<unsigned ,int> reservoir_minIDS_map;

vector<boost::unordered_set<unsigned>> neiborSet;  //邻居列表


bitset<QQQQ> _bitset1;
bitset<QQQQ> _bitset2;
bitset<QQQQ> _bitset3;

vector< vector <unsigned> > neighbor;
vector <double> weight_map;



unsigned globalN;
unsigned * localN;
unsigned cur_graph_size;
unsigned cur_popBack_pos;

//for FEMW_improve
float globalN_improve;

//for FEMW_FullyDynamic
unsigned nb;
unsigned ng;
float globalN_FD;
int  delete_sum;

vector< vector <pair<unsigned ,bool > > > neighbor_FD;

