set( KARMA_KGMAKER_LIBRARIES
     karma_kgfile
     karma_kgwriter
     glslang
     SPIRV
     stdc++fs
    )

add_executable       ( kgmaker main.cpp ArgumentParser.cpp ArgumentParser.h )
target_link_libraries( kgmaker PUBLIC  ${KARMA_KGMAKER_LIBRARIES}           )
