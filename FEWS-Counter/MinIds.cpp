
#include "MinIds.h"
unsigned minIds(pair<unsigned,unsigned> edge){
    if(edge.first<edge.second){
        return edge.first;
    }else{
        return edge.second;
    }
}
unsigned maxIds(pair<unsigned,unsigned> edge){
    if(edge.first>edge.second){
        return edge.first;
    }else{
        return edge.second;
    }
}
