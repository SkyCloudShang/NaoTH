/* 
 * File:   Configuration.cpp
 * Author: thomas
 * 
 * Created on 8. November 2010, 12:47
 */

#include "Configuration.h"

#include <iostream>
#include <string.h>

Configuration::Configuration()
{
  keyFile = g_key_file_new();
}

Configuration::Configuration(const Configuration& orig)
{
  keyFile = g_key_file_new();
  
  gsize bufferLength;
  gchar* buffer = g_key_file_to_data(orig.keyFile, &bufferLength, NULL);

  g_key_file_load_from_data(keyFile, buffer, bufferLength, G_KEY_FILE_NONE, NULL);

  g_free(buffer);

}

void Configuration::loadFromDir(std::string dirlocation, std::string platformName, std::string macAddress)
{
  if(!g_str_has_suffix(dirlocation.c_str(), "/"))
  {
    dirlocation = dirlocation + "/";
  }

  clear();

  loadFromSingleDir(dirlocation + "general/");
  loadFromSingleDir(dirlocation + "platforms/" + platformName + "/");
  loadFromSingleDir(dirlocation + "robots/" + macAddress + "/");
  loadFromSingleDir(dirlocation + "private/");
}

void Configuration::clear()
{
  if(keyFile != NULL)
  {
    g_key_file_free(keyFile);
  }
  keyFile = g_key_file_new();
}

void Configuration::loadFromSingleDir(std::string dirlocation)
{
  // iterate over all files in the folder

  if(!g_str_has_suffix(dirlocation.c_str(), "/"))
  {
    dirlocation = dirlocation + "/";
  }

  GDir* dir = g_dir_open(dirlocation.c_str(), 0, NULL);
  if(dir != NULL)
  {
    const gchar* name; 
    while((name = g_dir_read_name(dir)) != NULL)
    {
      if(g_str_has_suffix(name, ".cfg"))
      {
        gchar* group = g_strndup(name, strlen(name)-strlen(".cfg"));
        std::string completeFileName = dirlocation + name;
        if(g_file_test(completeFileName.c_str(), G_FILE_TEST_EXISTS)
          && g_file_test(completeFileName.c_str(), G_FILE_TEST_IS_REGULAR))
        {
          loadFile(completeFileName, std::string(group));
        }
        g_free(group);
      }

      
    }
    g_dir_close(dir);
  }
}

void Configuration::loadFile(std::string file, std::string groupName)
{
  GError* err = NULL;

  GKeyFile* tmpKeyFile = g_key_file_new();
  g_key_file_load_from_file(tmpKeyFile, file.c_str(), G_KEY_FILE_NONE, &err);
  if(err != NULL)
  {
    std::cerr << "ERROR " << file << ": "
      << err->message << std::endl;
    g_error_free(err);
  }
  else
  {
    // syntactically correct, check if there is only one group with the same 
    // name as the file
    bool groupOK = true;
    gsize length;
    gchar** groups = g_key_file_get_groups(tmpKeyFile, &length);
    for(int i=0; groupOK && i < length; i++)
    {
      if(g_strcmp0(groups[i], groupName.c_str()) != 0)
      {
        groupOK = false;
        std::cerr << "ERROR " << file << ": config file contains illegal group \""
          << groups[i] << "\"" << std::endl;
        break;
      }
    }
    g_strfreev(groups);

    if(groupOK)
    {
      if(g_key_file_load_from_file(keyFile, file.c_str(), G_KEY_FILE_KEEP_COMMENTS, NULL))
      {
        std::cout << "INFO loaded " << file << std::endl;
      }
    }
  }

  g_key_file_free(tmpKeyFile);
}

bool Configuration::hasKey(std::string group, std::string key)
{
  return g_key_file_has_key(keyFile, group.c_str(), key.c_str(), NULL);
}

std::string Configuration::getString(std::string group, std::string key)
{
  gchar* buf = g_key_file_get_string(keyFile, group.c_str(), key.c_str(), NULL);
  if(buf != NULL)
  {
    std::string result(buf);
    g_free(buf);
    return result;
  }
  return "";
}

Configuration::~Configuration()
{
  if(keyFile != NULL)
  {
    g_key_file_free(keyFile);
  }
}
