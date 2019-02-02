cmake_minimum_required(VERSION 3.0.0)
project(AG_PKG VERSION 0.1.0)


add_executable(AG_PKG main.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

# find_package(Nana REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation Net Util Zip NetSSL)

target_link_libraries(AG_PKG PRIVATE Poco::Net Poco::Foundation Poco::Util Poco::Zip Poco::NetSSL)
#target_link_libraries(AG_PKG PRIVATE ${NANA_LIBRARY})
#target_include_directories(AG_PKG PRIVATE ${NANA_INCLUDE_DIR})