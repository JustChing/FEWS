
#ifndef NEIGHBOR_H_
#define NEIGHBOR_H_
#include "Basic.h"
#include "hash.h"
#include "MinIds.h"
#include "IsClosed.h"


void UpdateNeiborNodeList(pair<unsigned,unsigned> edge,unsigned mIDS);
void UpdateNeiborNodeList_improve(pair<unsigned,unsigned> edge);
void UpdateNeiborNodeList_FullyDynamic(pair<unsigned,unsigned> edge);
#endif /* NEIGHBOR_H_ */
