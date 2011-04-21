#ifndef MODULELOADER_H
#define MODULELOADER_H

#include <vector>
#include <string>

#include <glib.h>
#include <gmodule.h>

class ModuleLoader
{

public:
  ModuleLoader();
  virtual ~ModuleLoader();

  void loadPackages(const std::string& directory);
private:
  void loadSinglePackage(const std::string& fileName);

  std::vector<GModule*> modules;

};

#endif // MODULELOADER_H
