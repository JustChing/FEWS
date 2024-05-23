
#include "neighbor.h"
void adjust(int i)
{
    double new_weight=0.8 * weight_map[i];
    vector <unsigned> temp;
    boost::unordered_set<unsigned> setTemp;
    for(int j=0;j<neighbor[i].size();j++)
    {
        double rand_2 = (double)rand() / ((double)RAND_MAX+1.0);
        if(rand_2<0.8)
        {
            temp.push_back(neighbor[i][j]);
            setTemp.insert(neighbor[i][j]);
        }
    }
    weight_map[i]=new_weight;
    NeighborSize-=0.5*(neighbor[i].size()-temp.size());
    neighbor[i]=temp;
    neiborSet[i]=setTemp;
}

void deleteEdgeAndNeighbor(int delete_pos) {

    pair<unsigned,unsigned> removeEdge=p_reservoir[cur_popBack_pos];
    unsigned remove_minIDS=minIds(removeEdge);
    auto it2=reservoir_minIDS_map.find(remove_minIDS);
    if(it2!=reservoir_minIDS_map.end())
    {
        unsigned a=reservoir_minIDS_map[remove_minIDS];
        a-=1;
        if(a==0)
        {
            reservoir_minIDS_map.erase(it2);
        }else{
            reservoir_minIDS_map[remove_minIDS]=a;
        }
    }

    for (int j = delete_pos; j <= res_cur_size - 2; j++) {//-2 cyy
        p_reservoir[j] = p_reservoir[j + 1];
    }

    M = M - 1;
    res_cur_size--;

    NeighborSize -= 0.5*neighbor[delete_pos].size();
    neiborSet.erase(neiborSet.begin() + delete_pos);
    neighbor.erase(neighbor.begin() + delete_pos);
    weight_map.erase(weight_map.begin() +delete_pos);

}
void deleteEdgeAndNeighbor_IMPR(int delete_pos) {

    for (int j = delete_pos; j <= res_cur_size - 2; j++) {
        p_reservoir[j] = p_reservoir[j + 1];
    }
    M = M - 1;
    res_cur_size--;
    NeighborSize -= 0.5*neighbor[delete_pos].size();

    neighbor.erase(neighbor.begin() + delete_pos);
}

void UpdateNeiborNodeList(pair<unsigned,unsigned> edge,unsigned mIDS) {
    char nodeStr1[15];
    char nodeStr2[15];
    sprintf(nodeStr1,"%u", edge.first);
    sprintf(nodeStr2,"%u", edge.second);
    auto  it1 =reservoir_minIDS_map.find(edge.first);
    auto  it2 =reservoir_minIDS_map.find(edge.second);

    if(it1!=reservoir_minIDS_map.end()||it2 !=reservoir_minIDS_map.end())
    {
        for (int i = 0; i < res_cur_size; i++)
        {
            unsigned  cur_minIds=minIds(p_reservoir[i]);
            unsigned  cur_maxIds=maxIds(p_reservoir[i]);
            if (edge.first == cur_minIds)
            {
                double rand_ = (double)rand() / ((double)RAND_MAX+1.0);
                //chose the neighbor with  weight
                if (rand_ < weight_map[i]) {
                    if(neighbor[i].size()+1>=Threshold)
                    {
                        NeighborSize += 0.5;
                        neighbor[i].push_back(edge.second);

                        neiborSet[i].insert(edge.second);

                        while(neighbor[i].size()>=Threshold)
                        {
                            adjust(i);
                        }
                    }else
                    {
                        if((res_cur_size + NeighborSize) < Budget) {
                            NeighborSize += 0.5;
                            neighbor[i].push_back(edge.second);

                            neiborSet[i].insert(edge.second);
                        }else
                        {
                            unsigned delete_pos = rand() % res_cur_size;
                            deleteEdgeAndNeighbor(delete_pos);
                            if (i> delete_pos) {
                                i--;
                                NeighborSize += 0.5;
                                neighbor[i].push_back(edge.second);
                                neiborSet[i].insert(edge.second);
                            } else if ((i) == delete_pos) {
                                i--;
                                continue;
                            } else {
                                NeighborSize += 0.5;
                                neighbor[i].push_back(edge.second);

                                neiborSet[i].insert(edge.second);
                            }
                        }
                    }
                }
            }
            if (edge.second == cur_minIds)
            {
                double rand_ = (double)rand() / ((double)RAND_MAX+1.0);
                if (rand_ < weight_map[i]) {

                    int start_weight =weight_map[i];//weight  before adjust
                    if(neighbor[i].size()+1>=Threshold)
                    {
                        while(neighbor[i].size()+1>=Threshold)
                        {
                            adjust(i);
                        }
                        double rand_2 = (double)rand() / ((double)RAND_MAX+1.0);

                        double ttt=(weight_map[i]/start_weight);
                        if(rand_2<ttt)
                        {
                            NeighborSize += 0.5;

                            neighbor[i].push_back(edge.first);
                            neiborSet[i].insert(edge.first);
                        }
                    }else
                    {
                        if((res_cur_size + NeighborSize) < Budget) {
                            NeighborSize += 0.5;
                            neighbor[i].push_back(edge.first);
                            neiborSet[i].insert(edge.first);

                        }else
                        {
                            unsigned delete_pos = rand() % res_cur_size;
                            deleteEdgeAndNeighbor(delete_pos);

                            if (i> delete_pos) {
                                i--;
                                NeighborSize += 0.5;
                                neighbor[i].push_back(edge.first);
                                neiborSet[i].insert(edge.first);
                            } else if ((i) == delete_pos) {
                                i--;
                                continue;
                            } else {
                                NeighborSize += 0.5;
                                neighbor[i].push_back(edge.first);
                                neiborSet[i].insert(edge.first);
                            }
                        }
                    }
                }
            }
            if((edge.first == cur_maxIds)||(edge.second == cur_maxIds))
            {
                if(isClosed(i,edge)==1){
                    float tmp=((float)cur_graph_size)/((float)res_cur_size);
                    if(res_cur_size<M){
                        globalN+= 2*(1/weight_map[i]);
                    }
                    else
                    {
                        tmp=tmp*2*(1/weight_map[i]);
                        globalN+=tmp;
                    }
                }
            }
        }
    }
   else if(Bloom_reservoir(nodeStr1,2)||Bloom_reservoir(nodeStr2,2)){

            for (int i = 0; i < res_cur_size; i++) {
                if(edge.first == maxIds(p_reservoir[i])||edge.second == maxIds(p_reservoir[i]))
                {
                    if(isClosed(i,edge)==1){
                        float tmp=((float)cur_graph_size)/((float)res_cur_size);
                        if(res_cur_size<M){
                            globalN += 2*(1/weight_map[i]);
                        }
                        else
                        {
                            tmp=tmp*2*(1/weight_map[i]);
                            globalN+=tmp;
                        }
                    }
                }
            }
    }
}
void UpdateNeiborNodeList_improve(pair<unsigned,unsigned> edge){
    char nodeStr1[15];
    char nodeStr2[15];

    sprintf(nodeStr1,"%u", edge.first);
    sprintf(nodeStr2,"%u", edge.second);

    if(Bloom_reservoir(nodeStr1,1)||Bloom_reservoir(nodeStr2,1)){

        for (int i = 0; i < res_cur_size; i++)
        {

            if (edge.first == minIds(p_reservoir[i]))
            {

                if ((res_cur_size + NeighborSize) < Budget) {
                    NeighborSize += 0.5;
                    neighbor[i].push_back(edge.second);

                }else {
                    unsigned delete_pos = rand() % res_cur_size;
                    deleteEdgeAndNeighbor_IMPR(delete_pos);

                    if (i> delete_pos) {
                        i--;
                        NeighborSize += 0.5;
                        neighbor[i].push_back(edge.second);
                    } else if ((i) == delete_pos) {
                        i--;
                        continue;

                    } else {
                        NeighborSize += 0.5;
                        neighbor[i].push_back(edge.second);
                    }
                }
            }
            if (edge.second == minIds(p_reservoir[i]))
            {

                if ((res_cur_size + NeighborSize) < Budget) {
                    NeighborSize += 0.5;
                    neighbor[i].push_back(edge.first);

                }else {
                    unsigned delete_pos = rand() % res_cur_size;
                    deleteEdgeAndNeighbor_IMPR(delete_pos);

                    if (i> delete_pos) {
                        i--;
                        NeighborSize += 0.5;
                        neighbor[i].push_back(edge.first);
                    } else if ((i) == delete_pos) {
                        i--;
                        continue;

                    } else {
                        NeighborSize += 0.5;
                        neighbor[i].push_back(edge.first);
                    }
                }
            }
            if(edge.first == maxIds(p_reservoir[i])||edge.second == maxIds(p_reservoir[i]))
            {
                if(isClosed_IMPR(i,edge)==1){
                    float tmp=((float)cur_graph_size)/((float)res_cur_size);
                    if(res_cur_size<M){
                        globalN_improve+= 2;
                    }
                    else
                    {
                        tmp=tmp*2;
                        globalN_improve+=tmp;
                    }
                }
            }
        }
    }else if(Bloom_reservoir(nodeStr1,2)||Bloom_reservoir(nodeStr2,2)){

        for (int i = 0; i < res_cur_size; i++) {
            if(edge.first == maxIds(p_reservoir[i])||edge.second == maxIds(p_reservoir[i]))
            {
                if(isClosed_IMPR(i,edge)==1){
                    float tmp=((float)cur_graph_size)/((float)res_cur_size);
                    if(res_cur_size<M){
                        globalN_improve += 2;
                    }
                    else
                    {
                        tmp=tmp*2;
                        globalN_improve+=tmp;
                    }

                }
            }
        }
    }

}
void deleteEdgeAndNeighbor_FD(int delete_pos) {
    if(p_reservoir[delete_pos].first==0 && p_reservoir[delete_pos].second==0)
    {
        nb=nb-1;
        ng=ng+1;
    }
    globalN_FD-=localN[delete_pos];

    for (int j = delete_pos; j <= res_cur_size - 2; j++) {
        p_reservoir[j] = p_reservoir[j + 1];
        localN[j]=localN[j+1];
    }

    M = M - 1;
    res_cur_size--;
    NeighborSize -= 0.5*neighbor_FD[delete_pos].size();

    neighbor_FD.erase(neighbor_FD.begin() + delete_pos);
}

void UpdateNeiborNodeList_FullyDynamic(pair<unsigned,unsigned> edge){

    char nodeStr1[15];
    char nodeStr2[15];

    sprintf(nodeStr1,"%u", edge.first);
    sprintf(nodeStr2,"%u", edge.second);

    if(Bloom_reservoir(nodeStr1,1)||Bloom_reservoir(nodeStr2,1)){

        for (int i = 0; i < res_cur_size; i++)
        {
            if (edge.first == minIds(p_reservoir[i]))
            {
                double rand_ = (double)rand() / ((double)RAND_MAX+1.0);
                if(rand_<F_N_weight)
                {
                    pair<unsigned,bool> node;
                    node.first=edge.second;
                    node.second=false;

                    if ((res_cur_size + NeighborSize) < Budget)
                    {
                        NeighborSize += 0.5;
                        neighbor_FD[i].push_back(node);
                    }
                    else
                    {
                        unsigned delete_pos = rand() % res_cur_size;
                        deleteEdgeAndNeighbor_FD(delete_pos);

                        if (i> delete_pos) {
                            i--;
                            NeighborSize += 0.5;
                            neighbor_FD[i].push_back(node);
                        } else if ((i) == delete_pos) {

                            i--;
                            continue;
                        } else {

                            NeighborSize += 0.5;
                            neighbor_FD[i].push_back(node);
                        }
                    }
                }
            }
            if (edge.second == minIds(p_reservoir[i]))
            {
                double rand_ = (double)rand() / ((double)RAND_MAX+1.0);
                if(rand_<F_N_weight)
                {
                    pair<unsigned,bool> node;
                    node.first=edge.first;
                    node.second=false;


                    if ((res_cur_size + NeighborSize) < Budget)
                    {
                        NeighborSize += 0.5;
                        neighbor_FD[i].push_back(node);
                    }
                    else
                    {
                        unsigned delete_pos = rand() % res_cur_size;
                        deleteEdgeAndNeighbor_FD(delete_pos);
                        if (i> delete_pos) {
                            i--;
                            NeighborSize += 0.5;
                            neighbor_FD[i].push_back(node);
                        } else if ((i) == delete_pos) {

                            i--;
                            continue;
                        } else {

                            NeighborSize += 0.5;
                            neighbor_FD[i].push_back(node);
                        }
                    }
                }
            }
            if(edge.first == maxIds(p_reservoir[i])||edge.second == maxIds(p_reservoir[i]))
            {
                if(isClosed_FD(i,edge,1)==1){
                    localN[i]+=1;
                    globalN_FD+=1;
                }
            }
        }
    }else if(Bloom_reservoir(nodeStr1,2)||Bloom_reservoir(nodeStr2,2)){

        for (int i = 0; i < res_cur_size; i++) {
            if(edge.first == maxIds(p_reservoir[i])||edge.second == maxIds(p_reservoir[i]))
            {
                if(isClosed_FD(i,edge,1)==1){
                    localN[i]+=1;
                    globalN_FD+=1;
                }
            }
        }
    }
}


