
SET( KARMA_GPU_WRITER_SOURCES 
     KgWriter.cpp
   )
     
SET( KARMA_GPU_WRITER_HEADERS
     KgWriter.h
   )

SET( KARMA_GPU_WRITER_INCLUDE_DIRS
     
   )

SET( KARMA_GPU_WRITER_LIBRARIES
     glslang
     SPIRV
     stdc++fs
    )

ADD_LIBRARY               ( kgwriter SHARED   ${KARMA_GPU_WRITER_SOURCES}  ${KARMA_GPU_WRITER_HEADERS} )
TARGET_INCLUDE_DIRECTORIES( kgwriter PRIVATE  ${KARMA_GPU_WRITER_INCLUDE_DIRS}                         )
TARGET_LINK_LIBRARIES     ( kgwriter PUBLIC   ${KARMA_GPU_WRITER_LIBRARIES}                            )

