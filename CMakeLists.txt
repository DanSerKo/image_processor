cmake_minimum_required(VERSION 3.0)

project(image_processor CXX)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_compile_options(-fsanitize=undefined)
add_link_options(-fsanitize=undefined)

add_executable(image_processor image_processor.cpp interface.cpp interface.h 
               bmp_utilities/bmp_reader.h bmp_utilities/bmp_writer.h bmp_utilities/picture.h
               bmp_utilities/bmp_reader.cpp bmp_utilities/bmp_writer.cpp bmp_utilities/picture.cpp
               filters/filter.h filters/crop.h filters/edge_detection.h filters/grayscale.h
               filters/negative.h filters/sharpening.h filters/fisheye.h filters/blur.h
               filters/filter.cpp filters/crop.cpp filters/edge_detection.cpp filters/grayscale.cpp
               filters/negative.cpp filters/sharpening.cpp filters/fisheye.cpp filters/blur.cpp)