cmake_minimum_required (VERSION 2.6) 

SET(IMAGE_HEADERS
  image.hpp
  image_impl.hpp
)

SET(ADABOOST_SOURCE
  WeakClassifiers.cpp
  AdaBooster.cpp 
)

SET(ADABOOST_HEADERS
  WeakClassifiers.h
  AdaBooster.h
)
 
add_library (AdaBoost ${ADABOOST_SOURCE} ${ADABOOST_HEADERS} ${IMAGE_HEADERS})

SET(SEX_IDENTIFICATION_SOURCE
  main.cpp
  ComparingClassifiers.cpp
)

SET(SEX_IDENTIFICATION_HEADERS
  ComparingClassifiers.h
)

add_executable (sex_identification ${SEX_IDENTIFICATION_SOURCE} ${SEX_IDENTIFICATION_HEADERS} ${IMAGE_HEADERS})
target_link_libraries (sex_identification AdaBoost)
