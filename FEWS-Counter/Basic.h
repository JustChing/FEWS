
#ifndef BASIC_H_
#define QQQQ 100000000 //bian da cyy
#define BASIC_H_

#include <bitset>
#include <time.h>
#include<iostream>
#include<string.h>
#include <stdlib.h>
#include<stdio.h>
#include<cstdio>
#include<vector>
#include<fstream>
#include<algorithm>
#include<map>
#include <math.h>
#include <sstream>
 #include <sys/time.h>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>


using namespace std;

extern pair<unsigned, unsigned>* p_reservoir;


extern unsigned M;
extern unsigned Budget;
extern double NeighborSize;//用来记录邻居列表所花费的内存
extern int Threshold;
extern unsigned res_cur_size;
extern double F_N_weight;// 初始w

extern boost::unordered_map<unsigned,int> reservoir_minIDS_map;

extern vector<boost::unordered_set<unsigned>> neiborSet;  //邻居列表



extern bitset<QQQQ> _bitset1;
extern bitset<QQQQ> _bitset2;
extern bitset<QQQQ> _bitset3;


extern vector< vector <unsigned> > neighbor;
extern vector <double> weight_map;


extern unsigned globalN;
extern unsigned* localN;
extern unsigned cur_graph_size;
extern unsigned cur_popBack_pos;

//for Improve
extern float globalN_improve;

//for Fully Dynamic
extern unsigned nb;
extern unsigned ng;
extern vector< vector <   pair<unsigned ,bool>   > > neighbor_FD;
extern int  delete_sum;

extern float globalN_FD;

#endif /* BASIC_H_ */
