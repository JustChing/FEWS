
#include "FEWS_FullyDynamic.h"

void FEMW_FullyDynamic(char * input_graph_filename){
    clock_t start=clock();
    globalN_FD=0;
    res_cur_size=0;
    nb=0;
    ng=0;
    p_reservoir=(pair<unsigned,unsigned> *)malloc(sizeof(pair<unsigned,unsigned>)*M);
    neighbor_FD.resize(M);
    localN=(unsigned *)malloc(sizeof(unsigned)*M);


    for(unsigned i=0;i<M;i++)
    {
        neighbor_FD[i].clear();
        localN[i]=0;

    }
    cur_popBack_pos=0;
    cur_graph_size=0;
    delete_sum=0;
    int T=0;


    pair<int,int> edge;


    struct timeval tvs,tve;
    gettimeofday(&tvs,NULL);
    FILE* fp;
    int N=50;
    char str[N];
    string line;

    if ((fp = fopen(input_graph_filename, "r")) == NULL) {
        puts("Fail to open file!");
        exit(0);
    }

    vector<unsigned > node1;
    vector<unsigned > node2;
    vector<int > node3;

    while (fgets(str, N, fp) != NULL) {
        string line1;
        string line2;
        int w;

        bool  flag = false;
        bool  flag2 = false;

        for (int i = 0; i < N; i++) {
            if (str[i] >= '0' && str[i] <= '9' ||str[i] == '-')
            {
                if (flag == false)
                {
                    line1 += str[i];
                    continue;
                }
                else if (flag == true && flag2 == false)
                {
                    line2 += str[i];
                    continue;
                }
                else if (flag == true && flag2 == true)
                {
                    if(str[i]=='-'||str[i]=='0')
                    {
                        w=-1;
                        break;
                    } else if(str[i]=='1')
                    {
                        w=1;
                        break;
                    }
                }
            }
            else {
                if (flag == false)
                {
                    flag = true;
                }
                else if (flag == true && flag2 == false)
                {
                    flag2 = true;
                }
            }
        }
        unsigned  n1 = atoi(line1.c_str());
        unsigned  n2 = atoi(line2.c_str());
        unsigned u=Randome_hash_func(n1);
        unsigned v=Randome_hash_func(n2);

        node1.push_back(u);
        node2.push_back(v);
        node3.push_back(w);
    }
    fclose(fp);


    for(int i=0;i<node1.size();i++){

        edge=make_pair(node1[i],node2[i]);
        T++;
        if(T%1000000==0)
        {
            gettimeofday(&tve,NULL);
            double span = tve.tv_sec-tvs.tv_sec + (tve.tv_usec-tvs.tv_usec)/1000000.0;

            cout << "M" << M <<endl;
            cout << "res_cur_size:" << res_cur_size <<endl;
            cout << "NBsize:" <<NeighborSize <<endl;

            cout<< "delete_sum"<<delete_sum<<endl;
            cout<< "cur_graph_size+delete_sum"<<delete_sum<<endl;
            cout <<"time cost for " << T/100000 << ":" <<span<<endl;
            cout << "the local number of triangles:" << globalN_FD<<endl;
        }
        if(node3[i]!=1)
        {
            cur_graph_size--;
            delete_sum++;
            removeSample(edge);
            continue;
        }else {
            cur_graph_size++;
            SampleEdge_FullyDynamic(edge);
        }
    }

    double ST=1;
    for(uint32_t i=0;i<M;i++)
    {
        ST*=((float)delete_sum-i)/((float)(delete_sum+cur_graph_size)-i);
    }
    ST=1-ST;

    float tmp=((float)cur_graph_size)/((float)M);

    double real=2*tmp *globalN_FD* (1/F_N_weight)*(1/ST);

    cout<< "delete_sum: "<<delete_sum<<endl;
    cout<< "cur_graph_size"<<cur_graph_size<<endl;
    cout<< "cur_graph_size+delete_sum: "<<cur_graph_size+delete_sum<<endl;
    cout << "M: "<<M << endl;
    cout << "final_Count :"<<real << endl;

    cout<<"useTime(ms) :"<<(clock() - start)/1000<<endl;

    free(p_reservoir);
    neighbor_FD.clear();
    free(localN);

}