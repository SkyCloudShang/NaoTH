/**
* @file AStarSearch.h
* 
* Definition of class AStarSearch
*
* @author <a href="mailto:yasinovs@informatik.hu-berlin.de">Yasinovskiy Kirill</a>
*/

#ifndef _AStartSearch_h_
#define _AStartSearch_h_

// include standard library headers
#include <algorithm>
#include <set>
#include <vector>

// naoth framework headers
#include "Tools/Math/Common.h"
#include "Tools/Math/Vector2.h"
#include "Tools/Math/Pose2D.h"

#include "Tools/Debug/Stopwatch.h"

#include "AStarSearchParameters.h"

#define EPSILON 0.00000001


/**
* @class AStarNode
*
* A class describing a node in an A* search tree
*/
class AStarNode
{
public:
  /**Default constructor */
  AStarNode()
    :
  position(0.0,0.0)
  { 
    fValue = 0;
    gValue = 0;
    hValue = 0;
    parentNode = 0;
    expanded = false; 
    attractionValue = 0;
    expansionRadius = 0;
  }
  /** Constructor with Vector2d as parameter
  * @param position Position on a node
  */
  AStarNode(const Vector2d nodePosition)
  {
    position = nodePosition;
    fValue = 0;
    gValue = 0;
    hValue = 0;
    parentNode = 0;
    expanded = false; 
    attractionValue = 0;
    expansionRadius = 0;
  }

  /** Copy-Constructor
  * @param node Another node to copy data from
  */
  AStarNode(const AStarNode& node)
  {
    position = node.position;
    fValue = node.fValue;
	  gValue = node.gValue;
    hValue = node.hValue;
    parentNode = node.parentNode;  
    expanded = node.expanded;
    attractionValue = node.attractionValue;
    expansionRadius = node.expansionRadius;
  }

  /** Sets the index of the parent node of this node
  * @param parentNode The index of the parent node
  */
	void setParentNode(unsigned int parentNode)
  { this->parentNode = parentNode;}

  /** Returns the index of the parent node
  * @return The parent node
  */
	unsigned int getParentNode() const 
  { return parentNode;}

  /** Sets the function values
  * @param g The costs of the path to this node
  * @param h The heuristic costs from this node to the goal
  */
  void setFunctionValues(double g, double h)
  { gValue = g; hValue = h;fValue = g+h;}

  /** Returns the value of this node
  * @return The value f
  */
	double f() const
  { return fValue;}

  /** Returns the costs of the path to this node
  * @return The path costs g
  */
  double g() const
  { return gValue;}

    /** Returns the heuristics of the node
  * @return The heuristic h
  */
  double h() const
  { return hValue;}

  
  /** Sets the position of this node
  * @param position The position
  */
  void setPosition(const Vector2d& position) 
  { this->position = position;}

  /** Returns the position of this node
  * @return The position
  */
  Vector2d getPosition() const
  { return position;}

  /** The most important function: expands the current node by generating
  * successor nodes. 
  * @param searchTree The search tree of A* search, new nodes will be inserted
  * @param expandedNodes A list of previously expanded nodes
  * @param goal The goal of the search
  * @param parameterSet The parameter set for the search
  * @param ownNodeNum The index of this node (in the seachTree)
  */
	void successor(std::vector<AStarNode>& searchTree,
              const std::vector<unsigned int>& expandedNodes,
              const AStarNode& start,
              const AStarNode& goal,
              const AStarSearchParameters& parameterSet,
              unsigned int ownNodeNum);

  /** Checks if this node has been expanded
  * @return true, if the node has been expanded
  */
  bool hasBeenExpanded() const 
  { return expanded;}

  /** Checks if this node has reached the goal
  * @param goal The goal
  * @param parameterSet The parameter set
  * @return true, if the node has reached the goal
  */
  bool hasReached(const AStarNode& goal,
                  const AStarSearchParameters& parameterSet) const;

  /** Computes the distance to another node
  * @param other The other node
  * @return The distance
  */
  double distToOtherNode(const AStarNode& other)
  { return (position - other.getPosition()).abs();}

protected:
  /** The position of the node*/
	Vector2d position;
  /** The value of the node*/
  double fValue;
  /** The path costs to the node*/
	double gValue;
  /** The heuristic of the node */
  double hValue;
  /** The index of the parent node*/
  unsigned int parentNode;  
  /** Flag: true, if the node has been expanded*/
  bool expanded;
  /** The attraction value at the position of the node
  * could be the potential field value or just some value 
  * that describes how attractive is this point for the
  * search algorithm (it is used with the cost - function)
  */
  double attractionValue;
  /** The expansion radius of the node*/
  double expansionRadius;

  /** Returns the expansion radius of the node
  * @return The expansion radius
  */
  double getExpansionRadius() const
  { return expansionRadius;}

  /** Computes the path costs to another node
  * @param node The other node
  * @param parameterSet The parameter set
  * @return The path costs
  */
  double computeCostsTo(const AStarNode& node) const;

  /** Computes the heuristic costs between two positions
  * @param p1 The first position
  * @param p2 The second position
  * @param currentBranchingFactor The current branching factor
  * @return The heuristic costs
  */
  double computeHeuristicBetween(const Vector2d& p1, const Vector2d& p2) const;

  /** Computes current parameters for expansion
  * @param currentExpansionRadius The current expansion radius
  * @param currentBranchingFactor The current branching factor
  * @param parameterSet The parameter set
  */
  void computeCurrentParameters(double& currentExpansionRadius, 
                                double& currentBranchingFactor,
                                const AStarNode& start,
                                const AStarSearchParameters& parameterSet) const;

  /** Checks if a new node is too close to another previously expanded node
  * @param searchTree The search tree
  * @param expandedNodes A list containing all previously expanded nodes
  * @param position The position of the new node
  * @return true, if the position is too close
  */
  bool tooCloseToAnotherNode(std::vector<AStarNode>& searchTree,
                             const std::vector<unsigned int>& expandedNodes,
                             const Vector2d position) const;
};// end class AStarNode

/** For sorting the heap the STL needs compare function that lets us compare
* the f value of two nodes
*/
class HeapCompare
{
public:
  bool operator() ( const AStarNode *first, const AStarNode *second ) const
  {
    return first->f() > second->f();
  }
}; // end class HeapCompare

/**
* @class AStarSearch
*
* An abstract implementation of the A* search algorithm.
*/
class AStarSearch
{
public:
  /** Constructor 
  * @param minCacheSize The number of nodes to allocate memory for
  * @param maxTreeSize The maximum number of nodes to expand
  * @param parameterSet A parameter set to check the maximum number of nodes to expand
  */
  AStarSearch(long minCacheSize, long maxTreeSize)
  {
    unsigned int elementsToReserve;
    if(maxTreeSize != -1)
    {
      elementsToReserve = (maxTreeSize+(unsigned int)parameterSet.maxBranchingFactor);
      this->maxTreeSize = maxTreeSize;
    }
    else
    {
      elementsToReserve = minCacheSize;
      this->maxTreeSize = -1;
    }
    searchTree.reserve(elementsToReserve);
    expandedNodes.reserve(elementsToReserve);
    pathFound = false;
  }// end constructor


  /** The main search function
  * @param start The starting node
  * @param goal The goal node
  * @param parameterSet The current parameter set
  * @param pathLength Returns the length of the path to the goal
  * @return The next node to go to
  */
	AStarNode search(const AStarNode& start, const AStarNode& goal, double& pathLength)
	{
    if(start.hasReached(goal, parameterSet))
    {
      return start;
    }
    searchTree.clear();
    expandedNodes.clear();
    // push back the start node in vector
    searchTree.push_back(start);
    // sort the heap
    //push_heap(searchTree.begin(), searchTree.end(), HeapCompare());
    // set the parent node of the start node
    searchTree[0].setParentNode(0);
    unsigned int indexOfBestNode;
    unsigned int nextNodeToExpand;
    while(true)
    {
      // find next node to expand (the one with
      // the minimal function value)
      nextNodeToExpand = findIndexOfNextNode();
      // can we expand other nodes, or should we stop (memory bounding...)
      if(searchTree.size() >= (unsigned int)maxTreeSize)
      {
        indexOfBestNode = nextNodeToExpand;
        break;
      }
      else
      {
        unsigned int sizeBeforeExpand(searchTree.size());
        searchTree[nextNodeToExpand].successor(searchTree, expandedNodes, start,
                                            goal, parameterSet, nextNodeToExpand);
        expandedNodes.push_back(nextNodeToExpand);
        unsigned int sizeAfterExpand(searchTree.size());
        int result(testNewNodesAgainstGoal(sizeBeforeExpand, sizeAfterExpand-1,goal));
        if(result != -1)
        {
          indexOfBestNode = result;
          break;
        }
      }
    }
    AStarNode result = backtraceNode(indexOfBestNode, pathLength);
    // return the node
    return result;
  }

  /**
  * DebugDrawings:
  * draw Path in Field or Image Context
  */
  void drawAllNodesField();
  void drawPathFiled();
  void drawHeuristic();
  void drawCost();
  void drawFunction();


private:
  /** A container for all nodes*/
	std::vector<AStarNode> searchTree;
  /** Indices of all expanded nodes*/
  std::vector<unsigned int> expandedNodes;
  /** The maximum number of nodes to expand*/
  long maxTreeSize;
  /** The parameter set*/
  AStarSearchParameters parameterSet;
  /** Did we find the path to Goal? */
  bool pathFound;

  /** 
  * Finds the next node to be expanded
  * @return The index of the node
  */
  unsigned int findIndexOfNextNode()
  {
    unsigned int expandableNode(0);
    // find first unexpanded node
    while(searchTree[expandableNode].hasBeenExpanded())
    {
      ++expandableNode;
    }
    // store his function value (cost+heuristic)
    double f = searchTree[expandableNode].f();
    // actually, we don't need it... while searchTree is sorted...
    for(unsigned int i=(expandableNode+1); i<searchTree.size(); i++)
    {
      if((!searchTree[i].hasBeenExpanded()) && (searchTree[i].f() < f))
      {
        f = searchTree[i].f();
        expandableNode = i;
      }
    }
    return expandableNode;
  }


  /** Tests if any node has reached the goal
  * @param firstNode The first node to test
  * @param lastNode The last node to test
  * @param goal The goal to test against
  * @return -1, if no node has reached the goal, the number of the node otherwise
  */
  int testNewNodesAgainstGoal(unsigned int firstNode, unsigned int lastNode,
                              const AStarNode& goal)
  {
    for(unsigned int i = firstNode; i<= lastNode; i++)
    {
      if(searchTree[i].hasReached(goal, parameterSet))
      {
        return (int)i;
      }
    }
    return -1;
  }

  /** Back-traces the best node found to the first node after the start node
  * @param indexOfBestNode The index of the best node found
  * @param pathLength Returns the length of the back-traced path
  * @return The root node of the path to the node
  */
  AStarNode backtraceNode(unsigned int indexOfBestNode, double& pathLength)
  {
    unsigned int currentNode(indexOfBestNode);
    pathLength = searchTree[currentNode].distToOtherNode(searchTree[searchTree[currentNode].getParentNode()]);
    while(searchTree[currentNode].getParentNode() != 0)
    {
      currentNode = searchTree[currentNode].getParentNode();
      pathLength += searchTree[currentNode].distToOtherNode(searchTree[searchTree[currentNode].getParentNode()]);
    }
    pathFound = true;
    return searchTree[currentNode];
  }

};// end class AStartSearch


#endif //AStartSaerch_h_