/*
 * File:   Test.cpp
 * Author: thomas
 *
 * Created on 11. November 2010, 18:32
 */

#include "Test.h"

#include <gmodule.h>

extern "C++"
{
  #include <ModuleFramework/ModuleManager.h>
}

Test::Test()
{

}

void Test::execute()
{ 
  std::cout << "Hello Test" << std::endl << std::endl;

}


Test::~Test()
{
}



