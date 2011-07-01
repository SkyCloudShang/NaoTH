/**
* @file CanopyClustering.h
*
* @author <a href="mailto:holzhaue@informatik.hu-berlin.de">Florian Holzhauer</a>
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
* Declaration of class CanopyClustering
*/

#ifndef __CanopyClustering_h_
#define __CanopyClustering_h_

#include "SampleSet.h"
#include "MCSLParameters.h"

// debug
#include "Tools/Debug/DebugRequest.h"
#include "Tools/Debug/DebugDrawings.h"

template<class C>
class CanopyClustering
{
public: 
  CanopyClustering(C& sampleSet, MCSLParameters& parameters)
    :
    sampleSet(sampleSet),
    parameters(parameters)
  {
  }

  ~CanopyClustering() {}

  void cluster();
  int getClusterSize(const Vector2<double> start);

private:
  C& sampleSet;
  
  class CanopyCluster
  {
  public:
    ~CanopyCluster(){}
    CanopyCluster():size(0){}

    double size;
    Vector2<double> clusterSum;
    Vector2<double> center;

    void add(const Sample2D& sample);
    double distance(const Sample2D& sample) const;
  
  private:
    double manhattanDistance(const Sample2D& sample) const;
    double euclideanDistance(const Sample2D& sample) const;
  };

  bool isInCluster(const CanopyCluster& cluster, const Sample2D& sample) const;

  static const int maxNumberOfClusters = 100;
  CanopyCluster clusters[maxNumberOfClusters];  //FIXME

  MCSLParameters& parameters;

};

#endif //__CanopyClustering_h_
