cmake_minimum_required(VERSION 3.21)
project(Server)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

add_executable(${PROJECT_NAME} main.cpp ClientSession.h Global.h DataBase.h Client.h Server.h Order.h Book.h Person.h Author.h)

set(CMAKE_CXX_STANDARD 23)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Boost COMPONENTS thread system REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads ${Boost_LIBRARIES})
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC /home/xink/Загрузки/connectorSQL/include/jdbc
        /home/xink/Загрузки/connectorSQL/include/
        /home/xink/Загрузки/connectorSQL/include/jdbc/cppconn)
target_link_libraries(${PROJECT_NAME} PRIVATE /home/xink/Загрузки/connectorSQL/lib64/libmysqlcppconn.so.9.8.0.28
        )
target_compile_features(${PROJECT_NAME} PUBLIC cxx_range_for)
