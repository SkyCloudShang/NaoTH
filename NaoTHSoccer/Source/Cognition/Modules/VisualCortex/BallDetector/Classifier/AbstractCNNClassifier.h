#ifndef ABSTRACTCNNCLASSIFIER_H
#define ABSTRACTCNNCLASSIFIER_H

#include "Representations/Perception/BallCandidates.h"

class AbstractCNNClassifier
{
public:
    AbstractCNNClassifier(){}

    virtual ~AbstractCNNClassifier(){}

    virtual bool classify(const BallCandidates::Patch& p) = 0;
};

#endif // ABSTRACTCNNCLASSIFIER_H
