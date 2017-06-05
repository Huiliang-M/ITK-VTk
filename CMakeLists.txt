cmake_minimum_required(VERSION 3.8)
PROJECT(testcode)    // testcode is file name

FIND_PACKAGE(ITK REQUIRED)
IF(ITK_FOUND)
    INCLUDE(${ITK_USE_FILE})
ENDIF(ITK_FOUND)

IF(ITKVtkGlue_LOADED)
    FIND_PACKAGE(VTK REQUIRED)
    INCLUDE(${VTK_USE_FILE})
ELSE()
    FIND_PACKAGE(ItkVtkGlue REQUIRED)
    INCLUDE(${ItkVtkGlue_USE_FILE})
    SET(Glue ItkVtkGlue)
ENDIF()

ADD_EXECUTABLE(3Dtest 3Dtest.cxx  ClippingPlaneMaker.cxx  DefaultPipeline.cxx)

TARGET_LINK_LIBRARIES(3Dtest ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${Glue})
