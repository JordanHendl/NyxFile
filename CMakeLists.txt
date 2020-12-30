include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( CMAKE_CXX_STANDARD          17  )
set( CMAKE_CXX_STANDARD_REQUIRED ON  )
set( CMAKE_CXX_EXTENSIONS        OFF )

add_subdirectory( glslang  ) 
add_subdirectory( kgwriter ) 
add_subdirectory( kgmaker  ) 
add_subdirectory( shader   ) 


