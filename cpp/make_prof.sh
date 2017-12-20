#!/bin/bash
cat prof_Image.hpp Image.hpp GreyImage.hpp ColorImage.hpp Toolbox.hpp > escales_l/Image.hpp
cat Image.cpp GreyImage.cpp ColorImage.cpp Toolbox.cpp > escales_l/Image.cpp
sed -i '/.hpp/d' escales_l/Image.hpp
sed -i '/.hpp/d' escales_l/Image.cpp
sed -i '1 i\#include "Image.hpp"' escales_l/Image.cpp

cd escales_l && make
