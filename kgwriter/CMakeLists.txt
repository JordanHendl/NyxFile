
set( KARMA_KGWRITER_SOURCES 
     KgWriter.cpp
   )
     
set( KARMA_KGWRITER_HEADERS
     KgWriter.h
   )

set( KARMA_KGWRITER_INCLUDE_DIRS
     
   )

set( KARMA_KGWRITER_LIBRARIES
     glslang
     SPIRV
     stdc++fs
    )

add_library               ( karma_kgwriter SHARED   ${KARMA_KGWRITER_SOURCES}  ${KARMA_KGWRITER_HEADERS} )
target_include_directories( karma_kgwriter PRIVATE  ${KARMA_KGWRITER_INCLUDE_DIRS}                       )
target_link_libraries     ( karma_kgwriter PUBLIC   ${KARMA_KGWRITER_LIBRARIES}                          )

