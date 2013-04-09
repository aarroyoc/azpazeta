PROJECT(AZPAZETA_JUNO)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


SET(welcome,"Welcome to Azpazeta 2.0 (Juno)")
SET(PROJECT_NAME_SHORT   "Azpazeta")
SET(PROJECT_NAME_LONG    "Azpazeta 2.0 Juno")
SET(PROJECT_DESCRIPTION  "Azpazeta is the strategy-economic sandbox game")
SET(PROJECT_COPYRIGHT    "Copyright (C) 2013 Adrián Arroyo Calle")
SET(PROJECT_CONTACT      "adrian.arroyocalle@gmail.com")
SET(PROJECT_VENDOR       "Divel")
SET(ORG_WEBSITE          "sites.google.com/site/divelmedia")
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
MESSAGE(STATUS "Welcome to Azpazeta 2.0 (Juno)")
SET(CMAKE_CXX_FLAGS_DEBUG,"-O0 -g3 -Wall -Werror -W -Wno-return-type")
SET(CMAKE_CXX_FLAGS_RELEASE,"-O2 -pipe")
#SET(PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}/build)
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#SET(WXWINDOWS_USE_GL 1) 
SET(wxWidgets_USE_LIBS)
find_package(OpenGL QUIET)
#find_package(GLUT)
FIND_PACKAGE(wxWidgets COMPONENTS gl aui adv html core net base QUIET)
#FIND_PACKAGE(LIBVLC)
FIND_PACKAGE(Lua52 REQUIRED) #Comment if you are in Windows
FIND_PACKAGE(OpenGLES2)
FIND_PACKAGE(GLEW)

SET(A,${CMAKE_CURRENT_SOURCE_DIR})
SET(B,${CMAKE_SOURCE_DIR})
SET(OS_VERSION,${CMAKE_SYSTEM})
SET(OS_NAME, ${CMAKE_SYSTEM_NAME})
SET(PROCESSOR, ${CMAKE_SYSTEM_PROCESSOR})
SET(COMPILER, ${CMAKE_CXX_COMPILER})
SET(BUILD_CMAKE,${CMAKE_VERSION})

IF(NOT CMAKE_BUILD_TYPE )
   SET( CMAKE_BUILD_TYPE "Release" )
ENDIF()

IF(NOT CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/build")
ENDIF()


INCLUDE("${wxWidgets_USE_FILE}")
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR}) #Comment if you are in Windows
#INCLUDE(${LIBVLC_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${OPENGLES2_INCLUDE_DIRS})
LINK_DIRECTORIES(${OPENGLES2_LIBRARY_DIRS})
#ADD_EXECUTABLE(AZPAZETA_JUNO src/app.cpp)
# Se puede usar asi ADD_LIBRARY(start src/start.cpp)
#TARGET_LINK_LIBRARIES(AZPAZETA_JUNO start ${wxWidgets_LIBRARIES}) o con SRC multiples

#SET(AZP_CORE
#src/core/core.cpp
#)
#ADD_LIBRARY(AAZPCORE SHARED ${AZP_CORE})

#IF(${CMAKE_COMPILER_IS_GNUCXX} )
#	set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-rpath='\$\$ORIGIN'")
#ENDIF()
#SET_TARGET_PROPERTIES(AAZPCORE PROPERTIES RUNTIME "${CMAKE_CURRENT_SOURCE_DIR}/libazpcore.so")

#SET (AZP_API
#src/azpscript/azpapi.cpp
#)
#AzpAPI Library
#ADD_LIBRARY(AZPAPI SHARED ${AZP_API})






SET(AZP_SERVER
src/core/server.cpp
)
ADD_EXECUTABLE(AZPSERVER ${AZP_SERVER})
SET_TARGET_PROPERTIES(AZPSERVER PROPERTIES RUNTIME "${CMAKE_CURRENT_SOURCE_DIR}/AZPSERVER")
#TARGET_LINK_LIBRARIES(AZPSERVER ${AZP_LIB} ) Nothing, yet...

SET (AZP_SRC
src/app.cpp
src/start.cpp
src/azpscript/azpvm.cpp
src/azpscript/azpapi.cpp
src/azpmarket/azpmarket.cpp
src/core/core.cpp
src/sprite/sprite.cpp
src/start/startgui.cpp
src/maploader/map.cpp
src/maploader/azpmap.cpp
src/window/options.cpp
src/window/alert.cpp
src/version.cpp
src/display/opengl/gl.cpp
src/display/opengl/shader.cpp
src/window/testgl.cpp
src/pathfinder/pathfinder.cpp
src/window/console.cpp
src/xml/tinyxml.cpp
src/xml/tinystr.cpp
src/xml/tinyxmlerror.cpp
src/xml/tinyxmlparser.cpp)
SET (AZP_LIB
${wxWidgets_LIBRARIES}
#${GLUT_LIBRARY}
${OPENGL_LIBRARIES}
#${LIBVLC_LIBRARY}
#${LIBVLCCORE_LIBRARY}
${LUA_LIBRARY}
${OPENGL_LIBRARIES}
#${AAZP_CORE}
${GLEW_LIBRARIES}
)


#If you can't use GLEW, add -DGL_GLEXT_PROTOTYPES
add_definitions(-DLANGUAGE=SPANISH -DOS_WX="${OS_VERSION}" -DPROCESSOR_WX="${PROCESSOR}" -DCOMPILER_WX="${COMPILER}" -DCMAKE_WX_VERSION="${BUILD_CMAKE}")
MESSAGE(STATUS ${welcome})
ADD_EXECUTABLE(AZPAZETA_JUNO ${AZP_SRC})
SET_TARGET_PROPERTIES(AZPAZETA_JUNO PROPERTIES RUNTIME "${CMAKE_CURRENT_SOURCE_DIR}/AZPAZETA_JUNO")
TARGET_LINK_LIBRARIES(AZPAZETA_JUNO ${AZP_LIB} )

INSTALL(TARGETS AZPAZETA_JUNO
RUNTIME          DESTINATION    azpazeta
ARCHIVE          DESTINATION    azpazeta/lib/static
LIBRARY          DESTINATION    azpazeta/lib
PUBLIC_HEADER    DESTINATION    azpazeta/include
)
INSTALL(FILES lang/es/azpazeta.mo         DESTINATION    azpazeta/lang/es/)
INSTALL(FILES lang/fr/azpazeta.mo         DESTINATION    azpazeta/lang/fr/)
INSTALL(FILES options/options.xml DESTINATION azpazeta/options/)
INSTALL(DIRECTORY media DESTINATION azpazeta/)
INSTALL(FILES scripts/Init.azps DESTINATION azpazeta/scripts/)
INSTALL(FILES maps/data.xml DESTINATION azpazeta/maps/)
INSTALL(DIRECTORY maps/core DESTINATION azpazeta/maps/)
INSTALL(DIRECTORY maps/orwell DESTINATION azpazeta/maps/)
INSTALL(DIRECTORY shaders DESTINATION azpazeta/)

