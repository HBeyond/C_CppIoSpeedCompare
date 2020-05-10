# first we add the executable that generates the table
add_executable(1_C_Read 1_C_Read.cpp)

# add the binary tree directory to the search path 
# for include files
include_directories(1_C_Read ${DEPEND_INCLUDES})
 
# add the main library
target_link_libraries(1_C_Read ${DEPEND_LIBS})

# install configurations - if needed
set_target_properties(1_C_Read PROPERTIES
        OUTPUT_NAME ${APP_NAME}
        )
install (TARGETS 1_C_Read
        RUNTIME DESTINATION ${EXE_OUTPUT_PATH}
        ARCHIVE DESTINATION ${LIB_OUTPUT_PATH}
        LIBRARY DESTINATION ${LIB_OUTPUT_PATH})
