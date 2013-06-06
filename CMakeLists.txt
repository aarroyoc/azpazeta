PROJECT(AZPAZETA_JUNO)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


SET(welcome,"Welcome to Azpazeta 2.0 (Juno)")
SET(PROJECT_NAME_SHORT   "Azpazeta")
SET(PROJECT_NAME_LONG    "Azpazeta 2.0 Juno")
SET(PROJECT_DESCRIPTION  "Azpazeta is the strategy-economic sandbox game")
SET(PROJECT_COPYRIGHT    "Copyright (C) 2013 Adrián Arroyo Calle")
SET(PROJECT_CONTACT      "adrian.arroyocalle@gmail.com")
SET(PROJECT_VENDOR       "Divel")
SET(ORG_WEBSITE          "http://sites.google.com/site/divelmedia")
#OperatingSystem-Explicit Category
#SET(OperatingSystem_EXPLICIT_BSD false CACHE BOOL "Compile with explicit BSD compatible")
#SET(OperatingSystem_EXPLICIT_SOLARIS false CACHE BOOL "Compile with explicit Solaris compatible")
#SET(OperatingSystem_EXPLICIT_HAIKU false CACHE BOOL "Compile with explicit Haiku compatible")
#SET(OperatingSystem_EXPLICIT_SYLLABLE false CACHE BOOL "Compile with explicit Syllable compatible")
#SET(OperatingSystem_EXPLICIT_REACTOS false CACHE BOOL "Compile with explicit ReactOS compatible")
#SET(OperatingSystem_EXPLICIT_ANDROID false CACHE BOOL "Compile with explicit Android compatible")
#SET(OperatingSystem_EXPLICIT_EMSCRIPTEN false CACHE BOOL "Compile with explicit Emscripten compatible")
#SET(OperatingSystem_EXPLICIT_IOS false CACHE BOOL "Compile with explicit iOS compatible")
#SET(OperatingSystem_EXPLICIT_WINPHONE false CACHE BOOL "Compile with explicit Windows Phone compatible")
#SET(OperatingSystem_EXPLICIT_IRIX false CACHE BOOL "Compile with explicit IRIX compatible")
#SET(OperatingSystem_EXPLICIT_HPUX false CACHE BOOL "Compile with explicit HP-UX compatible")
#SET(OperatingSystem_EXPLICIT_WINDOWS false CACHE BOOL "Compile with explicit Windows compatible")
#SET(OperatingSystem_EXPLICIT_HURD false CACHE BOOL "Compile with explicit Hurd compatible")
#SET(OperatingSystem_EXPLICIT_LINUX true CACHE BOOL "Compile with explicit Linux compatible")
#SET(OperatingSystem_EXPLICIT_ECOMSTATION false CACHE BOOL "Compile with explicit eComStation compatible")
#SET(OperatingSystem_EXPLICIT_OS2 false CACHE BOOL "Compile with explicit OS/2 compatible")
#Arch optimization
#SET(OperatingSystem_ARCH_ARMEL false CACHE BOOL "Compile with explicit ARMEL compatible")
#SET(OperatingSystem_ARCH_AVR false CACHE BOOL "Compile with explicit AVR compatible")
#SET(OperatingSystem_ARCH_POWERPC false CACHE BOOL "Compile with explicit PowerPC compatible")
#SET(OperatingSystem_ARCH_SPARC false CACHE BOOL "Compile with explicit SPARC compatible")
#SET(OperatingSystem_ARCH_ITANIUM false CACHE BOOL "Compile with explicit Itanium compatible")
#SET(OperatingSystem_ARCH_ARMHF false CACHE BOOL "Compile with explicit ARMHF compatible")
#SET(OperatingSystem_ARCH_x86 true CACHE BOOL "Compile with explicit x86 compatible")
#SET(OperatingSystem_ARCH_HPPA false CACHE BOOL "Compile with explicit HPPA compatible")
#SET(OperatingSystem_ARCH_ALPHA false CACHE BOOL "Compile with explicit Alpha compatible")
#SET(OperatingSystem_ARCH_MIPS false CACHE BOOL "Compile with explicit MIPS compatible")
#SET(OperatingSystem_ARCH_s390 false CACHE BOOL "Compile with explicit s390 compatible")
#SET(OperatingSystem_ARCH_BITS_32 true CACHE BOOL "Compile with explicit 32 Bits compatible")
#SET(OperatingSystem_ARCH_BITS_64 false CACHE BOOL "Compile with explicit 64 Bits compatible")
#Optional features
#SET(AZPFEATURES_MARKET true CACHE BOOL "Add Azpazeta Market to compilation")
#Azpazeta Versions
SET(AzpazetaVersion_StandardEdition true CACHE BOOL "Compile the standard edition of Azpazeta. Works on Linux, BSD, Solaris, Windows and Mac OS X")
SET(AzpazetaVersion_MinimalEditionHaiku false CACHE BOOL "Compile the Azpazeta Edition for Haiku (experimental)")
SET(AzpazetaVersion_MinimalEditionAndroid false CACHE BOOL "Compile the Azpazeta Edition for Android (experimental)")
SET(AzpazetaVersion_MinimalEditionEmscripten false CACHE BOOL "Compile the Azpazeta Edition for Emscripten (experimental)")



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
src/core/server_commands.cpp
)
ADD_EXECUTABLE(AZPSERVER ${AZP_SERVER})
SET_TARGET_PROPERTIES(AZPSERVER PROPERTIES RUNTIME "${CMAKE_CURRENT_SOURCE_DIR}/AZPSERVER")
#TARGET_LINK_LIBRARIES(AZPSERVER ${AZP_LIB} ) Nothing, yet...



IF(AzpazetaVersion_StandardEdition)
SET (AZP_SRC
src/app.cpp
src/start.cpp
src/azpscript/azpvm.cpp
src/azpscript/azpapi.cpp
src/azpscript/event.cpp
src/azpmarket/azpmarket.cpp
src/core/core.cpp
src/network/telemetry.cpp
src/savefile/savefile.cpp
src/sprite/sprite.cpp
src/start/startgui.cpp
src/database/database.cpp
src/maploader/map.cpp
src/maploader/azpmap.cpp
src/window/options.cpp
src/window/alert.cpp
src/window/loader.cpp
src/window/longtalk.cpp
src/window/newgame.cpp
src/window/startmission.cpp
src/window/feedback/feedback.cpp
src/version.cpp
src/log.cpp
src/display/opengl/gl.cpp
src/display/opengl/shader.cpp
src/window/testgl.cpp
src/pathfinder/pathfinder.cpp
src/window/console.cpp
src/xml/tinyxml.cpp
src/xml/tinystr.cpp
src/xml/tinyxmlerror.cpp
src/xml/tinyxmlparser.cpp)
#ELSEIF() For Haiku, Android, etc
#ELSE() Nothing specified



ENDIF()

IF(AzpazetaVersion_StandardEdition)
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
ENDIF()


#If you can't use GLEW, add -DGL_GLEXT_PROTOTYPES
add_definitions(-DLANGUAGE=SPANISH -DOS_WX="${CMAKE_SYSTEM}" -DPROCESSOR_WX="${CMAKE_SYSTEM_PROCESSOR}" -DCOMPILER_WX="${CMAKE_CXX_COMPILER}" -DCMAKE_WX_VERSION="${CMAKE_VERSION}")
MESSAGE(STATUS ${welcome})
MESSAGE(STATUS ${CMAKE_SYSTEM})
MESSAGE(STATUS ${CMAKE_SYSTEM_PROCESSOR})
MESSAGE(STATUS ${CMAKE_CXX_COMPILER})
MESSAGE(STATUS ${CMAKE_VERSION})
ADD_EXECUTABLE(AZPAZETA_JUNO ${AZP_SRC})
SET_TARGET_PROPERTIES(AZPAZETA_JUNO PROPERTIES RUNTIME "${CMAKE_CURRENT_SOURCE_DIR}/AZPAZETA_JUNO")
TARGET_LINK_LIBRARIES(AZPAZETA_JUNO ${AZP_LIB} )

SET(TARGETS AZPAZETA_JUNO AZPSERVER)

INSTALL(TARGETS ${TARGETS}
RUNTIME          DESTINATION    azpazeta
ARCHIVE          DESTINATION    azpazeta/lib/static
LIBRARY          DESTINATION    azpazeta/lib
PUBLIC_HEADER    DESTINATION    azpazeta/include
)
INSTALL(FILES AZPSERVER                   DESTINATION    azpazeta/)
INSTALL(FILES lang/es/azpazeta.mo         DESTINATION    azpazeta/lang/es/)
INSTALL(FILES lang/fr/azpazeta.mo         DESTINATION    azpazeta/lang/fr/)
INSTALL(FILES options/options.xml DESTINATION azpazeta/options/)
INSTALL(DIRECTORY media DESTINATION azpazeta/)
INSTALL(FILES scripts/Init.azps DESTINATION azpazeta/scripts/)
INSTALL(FILES maps/data.xml DESTINATION azpazeta/maps/)
INSTALL(DIRECTORY maps/core DESTINATION azpazeta/maps/)
INSTALL(DIRECTORY maps/orwell DESTINATION azpazeta/maps/)
INSTALL(DIRECTORY shaders DESTINATION azpazeta/)

