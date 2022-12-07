cmake_minimum_required(VERSION 3.12)
project(oksconfig VERSION 0.0.0)

find_package(daq-cmake REQUIRED)

find_package(config REQUIRED)
find_package(oks_utils REQUIRED)
find_package(oks REQUIRED)

daq_setup_environment()

daq_add_library(OksConfiguration.cpp OksConfigObject.cpp LINK_LIBRARIES config::config oks_utils::oks_utils oks::oks)

# tdaq_add_library(roksconfig
#   src/ROksConfiguration.cpp
#   LINK_LIBRARIES roks oksconfig)

# tdaq_add_executable(test_oksdb NOINSTALL
#   test/test_oksdb.cpp
#   LINK_LIBRARIES config)

# tdaq_add_executable(test_create_oksdb NOINSTALL
#   test/test_create_oksdb.cpp
#   LINK_LIBRARIES config)

# add_test(NAME oksconfig_check  COMMAND ${TDAQ_RUNNER} ${CMAKE_CURRENT_SOURCE_DIR}/cmt/test.sh ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
