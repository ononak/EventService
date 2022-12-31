cmake_minimum_required(VERSION 3.0.0)
project(EvSer VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(EvSer main.cpp EventService.cpp Subscriber.cpp)
    target_link_libraries(EvSer ${Boost_LIBRARIES})
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
