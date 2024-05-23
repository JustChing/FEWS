

#include "FEWS_Count.h"
#include <time.h>
void FEMW(char *input_graph_filename) {
    clock_t start=clock();

    p_reservoir=(pair<unsigned,unsigned> *)malloc(sizeof(pair<unsigned,unsigned>)*M);
    neiborSet.resize(M);
    neighbor.resize(M);
    weight_map.resize(M);
    res_cur_size=0;
    globalN=0;
    for(unsigned i=0;i<M;i++)
    {
        neiborSet[i].clear();
        neighbor[i].clear();
        weight_map[i]=F_N_weight;
    }
    cur_popBack_pos=0;
    cur_graph_size=0;


    pair<int,int> edge;
    struct timeval tvs,tve;
    gettimeofday(&tvs,NULL);
    FILE* fp;
    int N=30;
    char str[N + 1];
    string line;
    if ((fp = fopen(input_graph_filename, "r")) == NULL) {
        puts("Fail to open file!");
        exit(0);
    }

    vector<unsigned > node1;
    vector<unsigned > node2;


    while (fgets(str, N, fp) != NULL) {
        string line1;
        string line2;

        bool  flag = false;
        for (int i = 0; i < N; i++) {
            if (str[i] >= '0' && str[i] <= '9')
            {
                if (flag == false)
                {
                    line1 += str[i];
                }
                else
                {
                    line2 += str[i];

                    if((i+1)==N|| str[i+1]< '0'|| str[i] > '9')
                    {
                        break;
                    }
                }
            }
            else {
                flag = true;
            }
        }
        unsigned  n1 = atoi(line1.c_str());
        unsigned  n2 = atoi(line2.c_str());
        unsigned u=Randome_hash_func(n1);
        unsigned v=Randome_hash_func(n2);
        node1.push_back(u);
        node2.push_back(v);
    }
    fclose(fp);

    double span;

    for(int i=0;i<node1.size();i++){

        edge=make_pair(node1[i],node2[i]);
        cur_graph_size++;//流过的图的大小
        if(cur_graph_size%3000000==0)
        {
            gettimeofday(&tve,NULL);
            span = tve.tv_sec-tvs.tv_sec + (tve.tv_usec-tvs.tv_usec)/1000000.0;
            double real=globalN;
            cout << "M" << M <<endl;
            cout << "res_cur_size:" << res_cur_size <<endl;
            cout << "NBsize:" <<NeighborSize <<endl;


            cout <<"time cost for " << cur_graph_size/100000 << ":" <<span<<endl;
            cout << "the number of triangles:" << real <<endl;
        }

        SampleEdge(edge);
        unsigned mIDS=minIds(edge);
        UpdateNeiborNodeList(edge,mIDS);

    }

    double real=globalN;

    cout << "final_M: "<< M << endl;
    cout << "final_count: "<< real << endl;
    cout << "cur_graph_size:" << cur_graph_size << endl;

    cout<< "timeCost:"<<(clock() - start)/1000<<endl;

    free(p_reservoir);
    neiborSet.clear();
    neighbor.clear();
    weight_map.clear();
}