cmake_minimum_required(VERSION 3.12)
project(oksconflibs VERSION 1.1.0)

find_package(daq-cmake REQUIRED)

find_package(conffwk REQUIRED)
find_package(oksutils REQUIRED)
find_package(oks REQUIRED)
find_package(logging REQUIRED)

daq_setup_environment()

daq_add_library(OksConfiguration.cpp OksConfigObject.cpp LINK_LIBRARIES conffwk::conffwk oksutils::oksutils oks::oks logging::logging)

daq_add_application(test_oksdb test_oksdb.cxx TEST LINK_LIBRARIES conffwk::conffwk)
daq_add_application(test_create_oksdb test_create_oksdb.cxx TEST LINK_LIBRARIES conffwk::conffwk)

daq_install()
