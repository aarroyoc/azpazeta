PROJECT(AZPAZETA)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


SET(welcome,"Welcome to Azpazeta 2.1 (Link)")
SET(PROJECT_NAME_SHORT   "Azpazeta")
SET(PROJECT_NAME_LONG    "Azpazeta 2.1 Link")
SET(PROJECT_DESCRIPTION  "Azpazeta is the strategy-economic sandbox game")
SET(PROJECT_COPYRIGHT    "Copyright (C) 2013-2014 Adrián Arroyo Calle")
SET(PROJECT_CONTACT      "adrian.arroyocalle@gmail.com")
SET(PROJECT_VENDOR       "Divel")
SET(ORG_WEBSITE          "http://sites.google.com/site/divelmedia")
SET(BUILD_SHARED_LIBS OFF)
SET(AZP_SYSTEM ${CMAKE_SYSTEM})
SET(AZP_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR})
SET(AZP_COMPILER ${CMAKE_CXX_COMPILER})
SET(AZP_CMAKE_VERSION ${CMAKE_VERSION})
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
SET(AZP_AUDIO true CACHE BOOL "Build with audio libraries")
SET(AZP_DEBUG true CACHE BOOL "Build the debug version of Azpazeta")
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
MESSAGE(STATUS "Welcome to Azpazeta 2.1 (Link)")
SET(CMAKE_CXX_FLAGS_DEBUG,"-O0 -g3 -Wall -Werror -W -Wno-return-type")
SET(CMAKE_CXX_FLAGS_RELEASE,"-O2 -pipe")

SET(AZP_SERVER
src/core/server.cpp
src/core/server_commands.cpp
)
SET (AZP_SRC
src/app.cpp
src/start.cpp
src/azpscript/azpvm.cpp
src/azpscript/azpapi.cpp
src/azpscript/event.cpp
src/azpmarket/azpmarket.cpp
src/core/core.cpp
src/network/telemetry.cpp
src/sound/sound.cpp
src/savefile/savefile.cpp
src/sprite/sprite.cpp
src/start/startgui.cpp
src/physics/battle.cpp
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

ADD_EXECUTABLE(AZPSERVER ${AZP_SERVER})
ADD_EXECUTABLE(AZPAZETA ${AZP_SRC})

CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/src/config/config.h.in"
	"${PROJECT_BINARY_DIR}/src/config/config.h"
)
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/src/config")

SET(wxWidgets_USE_LIBS)
FIND_PACKAGE(OpenGL QUIET)
TARGET_LINK_LIBRARIES(AZPAZETA ${OPENGL_LIBRARIES})
FIND_PACKAGE(wxWidgets COMPONENTS gl aui adv html core net base QUIET)
INCLUDE("${wxWidgets_USE_FILE}")
TARGET_LINK_LIBRARIES(AZPAZETA ${wxWidgets_LIBRARIES})
FIND_PACKAGE(Lua52 REQUIRED) #Comment if you are in Windows
INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(AZPAZETA ${LUA_LIBRARY})
FIND_PACKAGE(OpenGLES2)
INCLUDE_DIRECTORIES(${OPENGLES2_INCLUDE_DIRS})
FIND_PACKAGE(GLEW)
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(AZPAZETA ${GLEW_LIBRARIES})
IF(AZP_AUDIO)
	FIND_PACKAGE(PortAudio)
	INCLUDE_DIRECTORIES(${PORTAUDIO_INCLUDE_DIRS})
	TARGET_LINK_LIBRARIES(AZPAZETA ${PORTAUDIO_LIBRARIES})
	FIND_PACKAGE(Ogg)
	INCLUDE_DIRECTORIES(${OGG_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(AZPAZETA ${OGG_LIBRARIES})
	FIND_PACKAGE(Vorbis)
	INCLUDE_DIRECTORIES(${VORBIS_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(AZPAZETA ${VORBIS_LIBRARIES})
	FIND_PACKAGE(VorbisFile)
	INCLUDE_DIRECTORIES(${VORBISFILE_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(AZPAZETA ${VORBISFILE_LIBRARIES})
ENDIF()


IF(NOT CMAKE_BUILD_TYPE )
   SET( CMAKE_BUILD_TYPE "Release" )
ENDIF()



SET(TARGETS AZPAZETA AZPSERVER)

INSTALL(TARGETS ${TARGETS}
RUNTIME          DESTINATION    azpazeta
ARCHIVE          DESTINATION    azpazeta/lib/static
LIBRARY          DESTINATION    azpazeta/lib
PUBLIC_HEADER    DESTINATION    azpazeta/include
)
#INSTALL(FILES AZPSERVER                   DESTINATION    azpazeta/)
INSTALL(FILES lang/es/azpazeta.mo         DESTINATION    azpazeta/lang/es/)
INSTALL(FILES lang/fr/azpazeta.mo         DESTINATION    azpazeta/lang/fr/)
INSTALL(FILES options/options.xml DESTINATION azpazeta/options/)
INSTALL(DIRECTORY media DESTINATION azpazeta/)
INSTALL(FILES scripts/Init.azps DESTINATION azpazeta/scripts/)
INSTALL(FILES maps/data.xml DESTINATION azpazeta/maps/)
INSTALL(DIRECTORY maps/core DESTINATION azpazeta/maps/)
INSTALL(DIRECTORY maps/orwell DESTINATION azpazeta/maps/)
INSTALL(DIRECTORY shaders DESTINATION azpazeta/)
