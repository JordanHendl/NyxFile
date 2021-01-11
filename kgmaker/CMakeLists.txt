SET( KARMA_GPU_MAKER_LIBRARIES
     kgfile
     kgwriter
     glslang
     SPIRV
     stdc++fs
    )

ADD_EXECUTABLE       ( kgmaker main.cpp ArgumentParser.cpp ArgumentParser.h )
TARGET_LINK_LIBRARIES( kgmaker PUBLIC  ${KARMA_GPU_MAKER_LIBRARIES}         )
