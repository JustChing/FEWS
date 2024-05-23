#include "IsClosed.h"


int isClosed(int index,pair<unsigned,unsigned> edge){
    pair<unsigned,unsigned> edge1= p_reservoir[index];
    unsigned maxId=maxIds(edge1);
    auto  t1=neiborSet[index].find(edge.first);
    if(t1!=neiborSet[index].end() && edge.second==maxId)
    {
        return 1;
    }
    auto  t2=neiborSet[index].find(edge.second);
    if(t2!=neiborSet[index].end() && edge.first==maxId)
    {
        return 1;
    }
    return 0;

}
int isClosed_IMPR(int index,pair<unsigned,unsigned> edge){
    pair<unsigned,unsigned> edge1= p_reservoir[index];
    unsigned maxId=maxIds(edge1);
    for(int i=0;i<neighbor[index].size();i++){
        if(edge.first==maxId && edge.second==neighbor[index][i] || edge.second==maxId && edge.first==neighbor[index][i]){
            return 1;
        }
    }
    return 0;

}

int isClosed_FD(int index,pair<unsigned,unsigned> edge,int status){
    pair<unsigned,unsigned> edge1= p_reservoir[index];
    unsigned maxId=maxIds(edge1);


    for(int i=0;i<neighbor_FD[index].size();i++){
        if((edge.first==maxId && edge.second==neighbor_FD[index][i].first)||(edge.second==maxId && edge.first==neighbor_FD[index][i].first)){
            if(status==1)
            {
                neighbor_FD[index][i].second=true;
                return  1;
            }else {
                if(neighbor_FD[index][i].second)
                {
                    //rest to false;
                    neighbor_FD[index][i].second= false;
                    return 1;
                }
            }
        }
    }
    return 0;
}


