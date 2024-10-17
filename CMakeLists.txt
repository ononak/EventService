cmake_minimum_required(VERSION 3.20.0)
project(EvSer VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

file(GLOB APP_SRC "bin/*.cpp")
file(GLOB PROJ_SRC "src/EventService/*.cpp")
file(GLOB TEST_SRC "test/*.cpp")
 
include(CTest)
include(FetchContent)
################################
# Google Test Framework
################################
find_package(PkgConfig)
pkg_search_module(GTEST REQUIRED gtest_main)
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})
 
#----------------------------------------------------------------
# Application
#----------------------------------------------------------------
include_directories(src)
add_executable(EvSer ./bin/EvServiceApp.cpp ${PROJ_SRC})
target_link_libraries(EvSer)


#----------------------------------------------------------------
# Unit Tests
#----------------------------------------------------------------
add_executable( TestEventService ${TEST_SRC} ${PROJ_SRC})
target_link_libraries(
    TestEventService
    PRIVATE
    ${GTEST_LDFLAGS}
    gtest
    gmock
)
 
include(GoogleTest)
gtest_discover_tests(TestEventService)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
