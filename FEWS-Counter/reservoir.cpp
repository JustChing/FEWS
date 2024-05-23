
#include "reservoir.h"

void SampleEdge(pair<unsigned,unsigned> edge)
{
    double rand_ = (double)rand() / ((double)RAND_MAX+1.0);
    unsigned mIDS=minIds(edge);
    unsigned maxIDS=maxIds(edge);
    if(res_cur_size<M)
    {
        p_reservoir[cur_popBack_pos]=edge;

        auto it=reservoir_minIDS_map.find(mIDS);
        if(it!=reservoir_minIDS_map.end())
        {
           int a=reservoir_minIDS_map[mIDS];
           a+=1;
           reservoir_minIDS_map[mIDS]=a;

        }else {
            reservoir_minIDS_map[mIDS]=1;
        }

        char max_str[15];
        sprintf(max_str,"%u", maxIDS);
        BloomSet2(max_str);
        cur_popBack_pos++;
        res_cur_size++;

    }
    else if(rand_<(((float)M)/((float)cur_graph_size)))
    {
        cur_popBack_pos = rand()%M;
        pair<unsigned,unsigned> replaceEdge=p_reservoir[cur_popBack_pos];
        unsigned replaceEdge_minIDS=minIds(replaceEdge);

        auto it2=reservoir_minIDS_map.find(replaceEdge_minIDS);
        if(it2!=reservoir_minIDS_map.end())
        {
            unsigned a=reservoir_minIDS_map[replaceEdge_minIDS];
            a-=1;
            if(a==0)
            {
                reservoir_minIDS_map.erase(it2);
            }else{
                reservoir_minIDS_map[replaceEdge_minIDS]=a;
            }
        }
        p_reservoir[cur_popBack_pos]=edge;

        auto it=reservoir_minIDS_map.find(mIDS);
        if(it!=reservoir_minIDS_map.end())
        {
            int a=reservoir_minIDS_map[mIDS];
            a+=1;
            reservoir_minIDS_map[mIDS]=a;

        }else {
            reservoir_minIDS_map[mIDS]=1;
        }


        char max_str[15];
        sprintf(max_str,"%u", maxIDS);
        BloomSet2(max_str);

        NeighborSize-=0.5*neighbor[cur_popBack_pos].size();
        neighbor[cur_popBack_pos].clear();
        neiborSet[cur_popBack_pos].clear();

        weight_map[cur_popBack_pos]=F_N_weight;

    }
}
void SampleEdge_improve(pair<unsigned,unsigned> edge)
{
    double rand_ = (double)rand() / ((double)RAND_MAX+1.0);
    unsigned mIDS=minIds(edge);
    unsigned maxIDS=maxIds(edge);

    if(res_cur_size<M)
    {
        p_reservoir[cur_popBack_pos]=edge;

        // insert into bloomFilter
        char min_str[15];
        sprintf(min_str,"%u", mIDS);
        BloomSet1(min_str);

        char max_str[15];
        sprintf(max_str,"%u", maxIDS);
        BloomSet2(max_str);
        cur_popBack_pos++;
        res_cur_size++;

    }
    else if(rand_<(((float)M)/((float)cur_graph_size)))
    {
        cur_popBack_pos = rand()%M;

        p_reservoir[cur_popBack_pos]=edge;

        char min_str[15];
        sprintf(min_str,"%u", mIDS);
        BloomSet1(min_str);

        char max_str[15];
        sprintf(max_str,"%u", maxIDS);
        BloomSet2(max_str);

        NeighborSize-=0.5*neighbor[cur_popBack_pos].size();
        neighbor[cur_popBack_pos].clear();


    }

}
void removeSample(pair<unsigned ,unsigned >  edge)
{
    bool flag=false;
    for (int i = 0; i < res_cur_size; i++)
    {
        if((edge.first==p_reservoir[i].first && edge.second==p_reservoir[i].second)
        ||(edge.second==p_reservoir[i].first && edge.first==p_reservoir[i].second))
        {

            p_reservoir[i].first=0;
            p_reservoir[i].second=0;
            nb+=1;
            NeighborSize-=0.5 * neighbor_FD[i].size();
            neighbor_FD[i].clear();
            globalN_FD-=localN[i];
            localN[i]=0;

            flag=true;

            continue;
        }

        if(edge.first == minIds(p_reservoir[i]))
        {

            for(int j=0;j<neighbor_FD[i].size();j++)
            {
                if(neighbor_FD[i][j].first==edge.second)
                {

                    if(neighbor_FD[i][j].second)
                    {
                        localN[i]-=1;
                        globalN_FD-=1;

                        //reset to false
                        neighbor_FD[i][j].second=false;
                    }
                    NeighborSize-=0.5;
                    neighbor_FD[i].erase(neighbor_FD[i].begin()+j);

                    break;
                }
            }
            continue;
        }
        if(edge.second == minIds(p_reservoir[i]))
        {

            for(int j=0;j<neighbor_FD[i].size();j++)
            {
                if(neighbor_FD[i][j].first==edge.first)
                {
                    if(neighbor_FD[i][j].second)
                    {
                        localN[i]-=1;
                        globalN_FD-=1;
                        //reset to false
                        neighbor_FD[i][j].second=false;
                    }
                    NeighborSize-=0.5;
                    neighbor_FD[i].erase(neighbor_FD[i].begin()+j);
                    break;
                }
            }
            continue;
        }

        if(edge.first == maxIds(p_reservoir[i])||edge.second == maxIds(p_reservoir[i]))
        {
            if(isClosed_FD(i,edge,0)==1){
                    localN[i]-=1;
                    globalN_FD-=1;
            }
        }
    }
    if(flag== false)
    {
        ng=ng+1;
    }
}
void SampleEdge_FullyDynamic(pair<unsigned,unsigned> edge)
{
    double rand_ = (double)rand() / ((double)RAND_MAX+1.0);
    if(nb+ng==0)
    {

        unsigned mIDS=minIds(edge);
        unsigned maxIDS=maxIds(edge);

        if(res_cur_size<M)
        {
            p_reservoir[cur_popBack_pos]=edge;

            char min_str[15];
            sprintf(min_str,"%u", mIDS);
            BloomSet1(min_str);

            char max_str[15];
            sprintf(max_str,"%u", maxIDS);
            BloomSet2(max_str);

            cur_popBack_pos++;
            res_cur_size++;
            UpdateNeiborNodeList_FullyDynamic(edge);
        }
        else if(rand_<(((float)M)/((float)cur_graph_size)))
        {
            cur_popBack_pos = rand()%M;
            p_reservoir[cur_popBack_pos]=edge;
            char min_str[15];
            sprintf(min_str,"%u", mIDS);
            BloomSet1(min_str);
            char max_str[15];
            sprintf(max_str,"%u", maxIDS);
            BloomSet2(max_str);

            NeighborSize-=0.5*neighbor_FD[cur_popBack_pos].size();
            neighbor_FD[cur_popBack_pos].clear();

            globalN_FD-=localN[cur_popBack_pos];
            localN[cur_popBack_pos]=0;

            UpdateNeiborNodeList_FullyDynamic(edge);
        }else
        {
            UpdateNeiborNodeList_FullyDynamic(edge);
        }
    }else if(rand_<(nb/(nb+ng)))
    {
        for (int i = 0; i < res_cur_size; i++)
        {
              if(p_reservoir[i].first==0 && p_reservoir[i].second==0 )
              {
                  p_reservoir[i]=edge;

                  //bloom filter
                  unsigned mIDS=minIds(edge);
                  unsigned maxIDS=maxIds(edge);

                  char min_str[15];
                  sprintf(min_str,"%u", mIDS);
                  BloomSet1(min_str);

                  char max_str[15];
                  sprintf(max_str,"%u", maxIDS);
                  BloomSet2(max_str);

                  nb=nb-1;
                  break;
              }
        }
        UpdateNeiborNodeList_FullyDynamic(edge);
    }else
    {
        ng=ng-1;

        UpdateNeiborNodeList_FullyDynamic(edge);
    }
}




