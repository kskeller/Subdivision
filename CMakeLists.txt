cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
set(GLUT_ROOT_PATH "D:\\Programme\\freeglut")

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Qt4 REQUIRED)
find_package(GLEW REQUIRED)

# -*- cmake -*-
# written by Darren Ha(darren.ha@samsung.com)

# replace Subdivision with binary name. e.g. mbase or FBase
SET (subdivision_target Subdivision)
#PROJECT(${subdivision_target})

## section: include directory

INCLUDE_DIRECTORIES(
  
  )

## section: source files
# Add your source files here (one file per line), please SORT in alphabetical order for future maintenance
SET (${subdivision_target}_SOURCE_FILES
	./Subdivision/Face.cpp
	./Subdivision/HalfEdge.cpp
	./Subdivision/LoopSubdivision.cpp
	./Subdivision/MyObject.cpp
	./Subdivision/Point3d.cpp
	./Subdivision/Subdivision.cpp
	./Subdivision/Texture.cpp
	./Subdivision/TwoManifold.cpp
	./Subdivision/Vertex.cpp
	)

## section: header files
# Add your header files here(one file per line), please SORT in alphabetical order for future maintenance!
SET(${subdivision_target}_HEADER_FILES
	./Subdivision/Defines.h
	./Subdivision/Face.h
	./Subdivision/HalfEdge.h
	./Subdivision/HalfEdgeDataStructure.h
	./Subdivision/LoopSubdivision.h
	./Subdivision/MyObject.h
	./Subdivision/Point3d.h
	./Subdivision/Subdivision.h
	./Subdivision/Texture.h
	./Subdivision/TwoManifold.h
	./Subdivision/Vertex.h
	)

SET_SOURCE_FILES_PROPERTIES(${subdivision_target}_HEADER_FILES
                            PROPERTIES HEADER_FILE_ONLY TRUE)
LIST(APPEND ${subdivision_target}_SOURCE_FILES ${${subdivision_target}_HEADER_FILES})

## section: add definitions
# 	add prefix -D. example> -DSHP
#  - DO NOT add  the following definitions(already defined in ${OSP_DEFINITIONS}:
# 	-DSHP, -DWIN32, -D_WINDOWS, -D_DEBUG, -D_USRDLL, -D_CRT_SECURE_NO_DEPRECATE
ADD_DEFINITIONS(
	 
	)

## section: add target
ADD_LIBRARY (${subdivision_target} STATIC ${${subdivision_target}_SOURCE_FILES} )

## section: add dependency
# dependency determines overall build order.
#ADD_DEPENDENCIES(${subdivision_target} )

## section: set link libraries
TARGET_LINK_LIBRARIES( ${subdivision_target}
		)
        
# -*- cmake -*-
# written by Darren Ha(darren.ha@samsung.com)

# replace Visualization2 with binary name. e.g. mbase or FBase
SET (visualization2_target Visualization2)
#PROJECT(${visualization2_target})

## section: include directory

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${QT_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_PATH}
  ${GLUT_INCLUDE_DIR}
  )

## section: source files
# Add your source files here (one file per line), please SORT in alphabetical order for future maintenance
SET (${visualization2_target}_SOURCE_FILES
	./Visualization2/main.cpp
	./Visualization2/MainWindow.cpp
	./Visualization2/MyGLWidget.cpp
	./Visualization2/ObjectDrawer.cpp
	./Visualization2/TextureDisplay.cpp
	)

## section: header files
# Add your header files here(one file per line), please SORT in alphabetical order for future maintenance!
SET(${visualization2_target}_HEADER_FILES
	./Visualization2/MainWindow.h
	./Visualization2/MyGLWidget.h
	./Visualization2/ObjectDrawer.h
	./Visualization2/TextureDisplay.h
	)

QT4_WRAP_CPP(${visualization2_target}_HEADERS_MOC ${${visualization2_target}_HEADER_FILES})
QT4_WRAP_UI(${visualization2_target}_FORMS_HEADERS ./Visualization2/MainWindow.ui)


SET(QT_USE_QTOPENGL 1)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

## section: add target
ADD_EXECUTABLE (${visualization2_target} ${${visualization2_target}_SOURCE_FILES} ${${visualization2_target}_HEADERS_MOC} ${${visualization2_target}_FORMS_HEADERS})

## section: add dependency
# dependency determines overall build order.
ADD_DEPENDENCIES(${visualization2_target} ${subdivision_target})

## section: set link libraries
TARGET_LINK_LIBRARIES( ${visualization2_target} ${QT_LIBRARIES} ${OPENGL_LIBRARIES}
		${subdivision_target})
