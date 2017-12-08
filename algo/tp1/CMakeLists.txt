add_definitions(-std=c++11)

configure_file(jules.txt jules.txt COPYONLY)
add_executable(algo_tp1 main.cpp)
