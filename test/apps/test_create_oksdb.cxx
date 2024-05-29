#include <stdlib.h>
#include <iostream>

#include "conffwk/Configuration.hpp"
#include "conffwk/ConfigObject.hpp"

using namespace dunedaq;
using namespace dunedaq::conffwk;

int main(int argc, char *argv[])
{
  std::string dbname = "oksconflibs:../test/okstest.data.xml:../test/test2.data.xml";

  if(argc < 3) {
    std::cerr <<
      "Usage: test_create_oksdb out-file in-file-1 in-file-2 [...]\n"
      "  out-file   - existing or new file name\n"
      "  in-file1   - first file to be added to out-file\n"
      "  in-file2   - second file to be added to out-file\n"
      "  ...        - list of files to be added to out-file\n";
    return 1;
  }

  const char * db_name = argv[1];


      // start of real test program

  Configuration db("oksconflibs");


  try {
    bool db_exist = false;

    try {
      db.load(db_name);
      db_exist = true;
      std::cout << "database file " << db_name << " already created" << std::endl;
    }
    catch(dunedaq::conffwk::Exception & dummu) {
      std::cout << "create database file " << db_name << std::endl;
    }

      // create db if it does not exist
    if(!db_exist) {
      std::list<std::string> includes;
      for(int i = 2; i < argc; ++i) {
        std::cout << "- include file " << argv[i] << std::endl;
        includes.push_back(argv[i]);
      }

      db.create(db_name, includes);
    }
    else {
      for(int i = 2; i < argc; ++i) {
        std::cout << "- include file " << argv[i] << std::endl;
        db.add_include(db_name, argv[i]);
      }
    }

    db.commit("test application (oksconflibs/test/test_create_oksdb.cpp)");

    std::cout << "done, see file \'" << db_name << "\'\n";
  }
  catch(dunedaq::conffwk::Exception & ex) {
    std::cerr << "ERROR: " << ex << std::endl;
    return 1;
  }

  return 0;
}
