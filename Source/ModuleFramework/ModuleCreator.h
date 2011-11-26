/**
* @file ModuleClassWraper.h
*
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
* Declaration of class ModuleCreator
*/

#ifndef __ModuleCreator_h__
#define __ModuleCreator_h__

#include "BlackBoardInterface.h"

namespace crf
{

class Module;

/**
 * AbstractModuleCreator is an interface.
 * It is used to create lists of modules.
 * Additionally it provides functionality to enable/disable the module
 */
class AbstractModuleCreator
{
public:
  virtual void setEnabled(bool value) = 0;
  virtual bool isEnabled() const = 0;
  virtual void execute() = 0;
  virtual Module* getModule() const = 0;
  virtual ~AbstractModuleCreator() {};
};

/**
 * ModuleInstance is needed to instantiate the 
 * BlackBoardInterface of the class V (if it has one)
 * with a blackboard.
 * We assume, that the class V already inherites from BlackBoardInterface.
 * Thereby 'virtual' inheritence is esential.
 * 
 * (in fact, what we are doing is to extend the default constructor of the class V
 *  by providing a pointer to a blackboard instance, i.e., we call another 
 *  constructor of the BlackBoardInterface)
 */
template<class V>
class ModuleInstance: virtual public BlackBoardInterface, virtual public V
{
public:
  ModuleInstance(BlackBoard& theBlackBoard)
    :
    BlackBoardInterface(&theBlackBoard)
  {
  }
};

/**
 * ModuleCreator implements the AbstractModuleCreator.
 * A module is deleted if it is disabled and created new if it is enabled.
 */
template<class V>
class ModuleCreator : public AbstractModuleCreator
{
private:
  BlackBoard& theBlackBoard;
  ModuleInstance<V>* theInstance;

  // cannot be copied
  ModuleCreator& operator=( const ModuleCreator& ) {}

public:

  ModuleCreator(BlackBoard& theBlackBoard)
    : 
      theBlackBoard(theBlackBoard),
      theInstance(NULL)
  {
  }

  virtual ~ModuleCreator()
  {
      delete theInstance;
  }


  bool isEnabled() const
  {
    return theInstance != NULL;
  }//end isEnabled

  void setEnabled(bool value)
  {
    if(value)
    {
      if( theInstance == NULL )
      {
        theInstance = new ModuleInstance<V>(theBlackBoard);
      }
    }else
    {
      if( theInstance != NULL )
      {
        delete theInstance;
        theInstance = NULL;
      }
    }
  }//end setEnabled

  void execute()
  {
    if( theInstance != NULL )
    {
      theInstance->execute();
    }//end if
  }//end execute

  Module* getModule() const
  {
    assert(isEnabled());
    // todo: check, the class V is not necessary a module
    return (Module*)(theInstance);
  }//end getModule

  V* getModuleT()
  {
    assert(isEnabled());
    return static_cast<V*>(theInstance);
  }//end getModule
};

}//crf
#endif //__ModuleCreator_h__
