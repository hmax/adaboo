cmake_minimum_required (VERSION 2.6) 

SET(IMAGE_HEADERS
  image.hpp
  image_impl.hpp
)

SET(ADABOOST_HEADERS
  weak_classifiers.hpp
  AdaBooster.hpp
  AdaBooster_impl.hpp
)
 

SET(SEX_IDENTIFICATION_SOURCE
  main.cpp
)

SET(SEX_IDENTIFICATION_HEADERS
  weak_classifiers.hpp ${IMAGE_HEADERS} ${ADABOOST_HEADERS}
)

SET(CMAKE_CXX_FLAGS "-Weffc++ -Wall -pedantic -std=c++11")

add_executable (sex_identification ${SEX_IDENTIFICATION_SOURCE} ${SEX_IDENTIFICATION_HEADERS} ${IMAGE_HEADERS})
