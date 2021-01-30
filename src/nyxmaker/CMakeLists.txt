SET( NYX_FILE_MAKER_LIBRARIES
     nyxfile
     nyxwriter
     glslang
     SPIRV
     stdc++fs
    )

ADD_EXECUTABLE       ( nyxmaker main.cpp ArgumentParser.cpp ArgumentParser.h )
TARGET_LINK_LIBRARIES( nyxmaker PUBLIC  ${NYX_FILE_MAKER_LIBRARIES}          )

INSTALL( TARGETS nyxmaker EXPORT NyxFile 
         RUNTIME  DESTINATION ${EXPORT_BIN_DIR}
         ARCHIVE  DESTINATION ${EXPORT_LIB_DIR}
         LIBRARY  DESTINATION ${EXPORT_LIB_DIR} 
       )