cmake_minimum_required(VERSION 2.8.4)
project(camrem)

FIND_PACKAGE( Threads )
FIND_PACKAGE( Boost COMPONENTS system filesystem thread log log_setup unit_test_framework REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES_CAMREM src/camrem.cpp  src/Helpers.cpp)
add_executable(camrem ${SOURCE_FILES_CAMREM})
TARGET_LINK_LIBRARIES(camrem ${Boost_LIBRARIES} ${Boost_LOG_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})