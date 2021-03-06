# 
# Copyright (C) 2020 Jordan Hendl
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 

# 
# File:   CMakeLists.h
# Author: Jordan Hendl
# 
# Created on December 31, 2020, 11:30 PM
# 

CMAKE_MINIMUM_REQUIRED( VERSION 3.8.0 )

LIST( APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )


# Build options
OPTION( BUILD_NYXMAKER "Whether or not the nyxmaker executable will be built" ON  )
OPTION( BUILD_RELEASE "Whether or not the to build for release."              OFF )

PROJECT( nyxfile CXX )
INCLUDE( Message  )

STRING( TIMESTAMP Date "%m %d %Y"    )
STRING( TIMESTAMP Time "%Hh %Mm %Ss" )

MESSAGE( INFO "Nyx File Prebuild" ) 
MESSAGE( INFO "Date: ${Date}"     )
MESSAGE( INFO "Time: ${Time}"     )
MESSAGE( INFO " " ) 


IF( BUILD_RELEASE  )
    MESSAGE( INFO "Building for release" )
    IF( MSVC )
      ADD_COMPILE_OPTIONS( /W2 /03 )
    ELSEIF( UNIX AND NOT APPLE )
      ADD_COMPILE_OPTIONS( -fPIC -O3 )
    ENDIF()
ELSE()
    MESSAGE( INFO "Building for debug" )
    IF( MSVC )
      ADD_COMPILE_OPTIONS( /DEBUG )
    ELSEIF( UNIX AND NOT APPLE )
      ADD_COMPILE_OPTIONS( -fPIC -g )
    ENDIF()
ENDIF()

# Print build options
MESSAGE( STATUS "" ) 
MESSAGE( INFO "Build Options:" ) 
MESSAGE( INFO "├─BUILD_NYXMAKER ${BUILD_NYXMAKER} " )
MESSAGE( INFO "└─BUILD_RELEASE  ${BUILD_RELEASE}  " )
MESSAGE( STATUS "" ) 

# Set build config.
SET( ARCHITECTURE "64bit" CACHE STRING "The system architecture."                     )
SET( CXX_STANDARD "17"    CACHE STRING "The C++ standard to use for building."        )
SET( MAJOR        "0"     CACHE STRING "The major version of this build."             )
SET( MINOR        "2"     CACHE STRING "The minor version of this build."             )
SET( BRANCH       "0"     CACHE STRING "The branch version of this build."            )
SET( REVISION     "0"     CACHE STRING "The revision of this build."                  )
SET( GENERATOR    "RPM"   CACHE STRING "The Package Generator to use for this build." )

IF( WIN32 )
  SET( INSTALL_LOCATION "C:/Program Files" CACHE STRING "The default NSIS install location of this library" )
ELSEIF( UNIX AND NOT APPLE )
  SET( INSTALL_LOCATION "/usr/local/lib64" CACHE STRING "The RPM install location of this library." ) 
ENDIF()

SET(CMAKE_CXX_STANDARD          17 )
SET(CMAKE_CXX_STANDARD_REQUIRED ON )

SET( PROJECT_VERSION "${MAJOR}.${MINOR}.${BRANCH}" )

# Print build configurations.
MESSAGE( INFO " " ) 
MESSAGE( INFO "Build Configuration:"                      )
MESSAGE( INFO "├─ARCHITECTURE      : ${ARCHITECTURE}"     )
MESSAGE( INFO "├─INSTALL GENERATOR : ${GENERATOR}"        )
MESSAGE( INFO "├─INSTALL LOCATION  : ${INSTALL_LOCATION}" )
MESSAGE( INFO "├─CXX_STANDARD      : ${CXX_STANDARD}"     )
MESSAGE( INFO "└─VERSION           : ${PROJECT_VERSION}"  )
MESSAGE( INFO "  ├─MAJOR           : ${MAJOR}"            )
MESSAGE( INFO "  ├─MINOR           : ${MINOR}"            )
MESSAGE( INFO "  ├─BRANCH          : ${BRANCH}"           )
MESSAGE( INFO "  └─REVISION        : ${REVISION}"         )

# Handle compiler information
STRING( TOLOWER ${CMAKE_CXX_COMPILER_ID} CXX_COMPILER_NAME )
SET( CXX_COMPILER  "${CXX_COMPILER_NAME}${CMAKE_CXX_COMPILER_VERSION}" )

SET( CLANG FALSE )
SET( INTEL FALSE )
SET( GNU   FALSE )
SET( MSVC  FALSE )
IF( CXX_COMPILER_NAME MATCHES "clang" )
  SET( CLANG TRUE )
ELSEIF( CXX_COMPILER_NAME MATCHES "gnu" )
  SET( GNU TRUE )
ELSEIF( CXX_COMPILER_NAME MATCHES "intel" )
  SET( INTEL TRUE )
ELSEIF( CXX_COMPILER_NAME MATCHES "msvc" )
  SET( MSVC TRUE )
ENDIF()

MESSAGE( INFO " " ) 
MESSAGE( INFO  "System Configuration:"                     )
MESSAGE( INFO  "├─CXX_COMPILER_NAME: ${CXX_COMPILER_NAME}" )
MESSAGE( INFO  "├─CXX_COMPILER:      ${CXX_COMPILER}"      )
MESSAGE( INFO  "├─INTEL:             ${INTEL}"             )
MESSAGE( INFO  "├─GNU:               ${GNU}"               )
MESSAGE( INFO  "└─MSVC:              ${MSVC}"              )
MESSAGE( INFO " " ) 


SET( BIN_DIR          "bin"                            )
SET( INCLUDE_DIR      "include/${CMAKE_PROJECT_NAME}"  )
SET( LIB_DIR          "lib64"                          )
SET( DOC_DIR          "doc"                            )
SET( CONFIG_DIR        ${CMAKE_PROJECT_NAME}           )
SET( DOXYGEN_DIR       ${CMAKE_CURRENT_SOURCE_DIR}/doc )
SET( BUILD_DIR         ${CMAKE_BINARY_DIR}             )

SET( EXPORT_BIN_DIR     "${BIN_DIR}"     )
SET( EXPORT_INCLUDE_DIR "${INCLUDE_DIR}" )
SET( EXPORT_LIB_DIR     "${LIB_DIR}"     )
SET( EXPORT_DOC_DIR     "${DOC_DIR}"     )
SET( EXPORT_CONFIG_DIR  "${CONFIG_DIR}"  )

# Set output directories.
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib64 )
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib64 )
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin   )
SET(DOCUMENTATION_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/doc   )

IF( MSVC )
    SET( WINDOWS_EXPORT_ALL_SYMBOLS       TRUE )
    SET( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE )
    SET( BUILD_SHARED_LIBS TRUE                )
ENDIF()

INCLUDE( KPackage ) 

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/src ) 
ADD_SUBDIRECTORY( src )

# Install glslang license.
INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/glslang/LICENSE.txt DESTINATION licences/glslang/     COMPONENT dev )
INSTALL( EXPORT NyxFile FILE NyxFileConfig.cmake                   DESTINATION " " COMPONENT dev )
