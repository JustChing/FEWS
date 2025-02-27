
#ifndef RESERVOIR_H_
#define RESERVOIR_H_

#include "Basic.h"
#include "hash.h"
#include "MinIds.h"
#include "neighbor.h"

void SampleEdge(pair<unsigned,unsigned> edge);
void SampleEdge_improve(pair<unsigned,unsigned> edge);
void removeSample(pair<unsigned ,unsigned >  edge);
void SampleEdge_FullyDynamic(pair<unsigned,unsigned> edge);
#endif /* RESERVOIR_H_ */
