set( KARMA_FILE_SOURCES 
     KgFile.cpp
   )
     
set( KARMA_FILE_HEADERS
     KgFile.h
   )

set( KARMA_FILE_INCLUDE_DIRS
   )

set( KARMA_FILE_LIBRARIES
     stdc++fs
    )

add_library               ( karma_kgfile SHARED   ${KARMA_FILE_SOURCES} ${KARMA_FILE_HEADERS} )
target_include_directories( karma_kgfile PRIVATE  ${KARMA_FILE_INCLUDE_DIRS}                  )
target_link_libraries     ( karma_kgfile PUBLIC   ${KARMA_FILE_LIBRARIES}                     )