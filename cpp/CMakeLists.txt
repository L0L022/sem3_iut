add_definitions(-std=c++11)

find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})

configure_file(cat.pgm cat.pgm COPYONLY)
configure_file(cat.ppm cat.ppm COPYONLY)
configure_file(little_cat.ppm little_cat.ppm COPYONLY)

add_executable(GreyImage GreyImage_test.cpp Image.cpp GreyImage.cpp Toolbox.cpp)
add_executable(ColorImage ColorImage_test.cpp Image.cpp ColorImage.cpp Toolbox.cpp)
target_link_libraries(ColorImage ${JPEG_LIBRARIES})
