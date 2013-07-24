cmake_minimum_required (VERSION 2.6) 
add_library (Image Image.cpp Image.h)
SET(SOURCE
  main.cpp
  WeakClassifiers.cpp
  AdaBooster.cpp 
)

SET(HEADERS
  WeakClassifiers.h
  AdaBooster.h
)
 
add_executable (sex_identification ${SOURCE} ${HEADERS})
target_link_libraries (sex_identification Image)