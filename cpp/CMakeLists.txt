add_definitions(-std=c++11)

add_executable(GreyImage GreyImage_test.cpp Image.cpp GreyImage.cpp Toolbox.cpp)
add_executable(ColorImage ColorImage_test.cpp Image.cpp ColorImage.cpp Toolbox.cpp)
