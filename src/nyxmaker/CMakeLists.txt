SET( NYX_FILE_MAKER_LIBRARIES
     nyxfile
     nyxwriter
     glslang
     SPIRV
     stdc++fs
    )

ADD_EXECUTABLE       ( nyxmaker main.cpp ArgumentParser.cpp ArgumentParser.h )
TARGET_LINK_LIBRARIES( nyxmaker PUBLIC  ${NYX_FILE_MAKER_LIBRARIES}          )

IF( UNIX AND NOT APPLE )
  EXECUTE_PROCESS( COMMAND ln -s ${INSTALL_LOCATION}/${CMAKE_PROJECT_NAME}/${EXPORT_BIN_DIR}/nyxmaker nyxmaker )
  INSTALL( FILES ${CMAKE_BINARY_DIR}/nyxmaker DESTINATION /usr/bin/ COMPONENT NyxFile )
ENDIF() 

INSTALL( TARGETS nyxmaker EXPORT NyxFile 
         RUNTIME  DESTINATION ${EXPORT_BIN_DIR}
         ARCHIVE  DESTINATION ${EXPORT_LIB_DIR}
         LIBRARY  DESTINATION ${EXPORT_LIB_DIR} 
       )