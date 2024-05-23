
#ifndef FEMW_COUNTER_ISCLOSED_H
#define FEMW_COUNTER_ISCLOSED_H
#include "Basic.h"
#include "MinIds.h"
#include "hash.h"
int isClosed(int index,pair<unsigned,unsigned> edge);
int isClosed_FD(int index,pair<unsigned,unsigned> edge,int status);
int isClosed_IMPR(int index,pair<unsigned,unsigned> edge);
#endif //FEMW_COUNTER_ISCLOSED_H
