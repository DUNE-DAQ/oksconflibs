cmake_minimum_required(VERSION 3.12)
project(oksconfig VERSION 0.0.0)

find_package(daq-cmake REQUIRED)

find_package(oksdbinterfaces REQUIRED)
find_package(oks_utils REQUIRED)
find_package(oks REQUIRED)
find_package(logging REQUIRED)

daq_setup_environment()

daq_add_library(OksConfiguration.cpp OksConfigObject.cpp LINK_LIBRARIES oksdbinterfaces::oksdbinterfaces oks_utils::oks_utils oks::oks logging::logging)

daq_add_application(test_oksdb test_oksdb.cxx TEST LINK_LIBRARIES oksdbinterfaces::oksdbinterfaces)
daq_add_application(test_create_oksdb test_create_oksdb.cxx TEST LINK_LIBRARIES oksdbinterfaces::oksdbinterfaces)

daq_install()
