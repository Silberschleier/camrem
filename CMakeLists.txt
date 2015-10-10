cmake_minimum_required(VERSION 2.8.4)
project(camrem)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

FIND_PACKAGE( Threads REQUIRED )
FIND_PACKAGE( Microhttpd REQUIRED )
FIND_PACKAGE( Boost COMPONENTS system filesystem thread log log_setup unit_test_framework REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} {$MICROHTTPD_INCLUDE_DIR})

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
ADD_DEFINITIONS(-DBOOST_NO_CXX11_SCOPED_ENUMS=1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES_CAMREM src/Helpers.cpp src/ConfigHandler.cpp src/Http/Http.cpp src/Http/Daemon.cpp src/Http/Request.cpp src/Http/Response.cpp src/Http/Response.h src/Http/ApiBindings.cpp src/Http/ApiBindings.h src/Http/FileResponse.cpp src/Http/FileResponse.h src/Http/MemoryResponse.cpp src/Http/MemoryResponse.h)


add_library(camremobjects STATIC ${SOURCE_FILES_CAMREM})
add_executable(camremd src/camrem.cpp)
add_executable(camrem_tests tests/tests.cpp tests/tests.h)

TARGET_LINK_LIBRARIES(camremd camremobjects ${Boost_LIBRARIES} ${Boost_LOG_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${MICROHTTPD_LIBRARY})
TARGET_LINK_LIBRARIES(camrem_tests camremobjects ${Boost_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${MICROHTTPD_LIBRARY})
