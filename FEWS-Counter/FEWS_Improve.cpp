
#include "FEWS_Improve.h"
void FEMW_Improve(char *input_graph_filename) {
    clock_t start = clock();

    p_reservoir = (pair<unsigned, unsigned> *) malloc(sizeof(pair<unsigned, unsigned>) * M);
    neighbor.resize(M);

    res_cur_size = 0;
    globalN_improve = 0;
    for (unsigned i = 0; i < M; i++) {
        neighbor[i].clear();

    }
    cur_popBack_pos = 0;
    cur_graph_size = 0;
    pair<int,int> edge;

    struct timeval tvs, tve;
    gettimeofday(&tvs, NULL);
    FILE *fp;
    int N = 30;
    char str[N + 1];
    string line;
    //判断文件是否打开失败
    if ((fp = fopen(input_graph_filename, "r")) == NULL) {
        puts("Fail to open file!");
        exit(0);
    }
    vector<unsigned> node1;
    vector<unsigned> node2;


    while (fgets(str, N, fp) != NULL) {
        string line1;
        string line2;

        bool  flag = false;
        //String vector  size   hangshu
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
    for(int i=0;i<node1.size();i++){

        edge=make_pair(node1[i],node2[i]);
        cur_graph_size++;
        if(cur_graph_size%100000==0)
        {
            gettimeofday(&tve,NULL);
            double span = tve.tv_sec-tvs.tv_sec + (tve.tv_usec-tvs.tv_usec)/1000000.0;

            cout << "M" << M <<endl;
            cout << "res_cur_size:" << res_cur_size <<endl;
            cout << "NBsize:" <<NeighborSize <<endl;


            cout <<"time cost for " << cur_graph_size/100000 << ":" <<span<<endl;
            cout << "the number of triangles:" << globalN_improve <<endl;
        }
        SampleEdge_improve(edge);
        UpdateNeiborNodeList_improve(edge);

    }
    cout << M << endl;
    cout << globalN_improve << endl;
    cout << cur_graph_size << endl;

    cout<<(clock() - start)/1000<<endl;

    free(p_reservoir);
    neighbor.clear();

}
