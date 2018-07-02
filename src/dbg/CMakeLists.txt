set(DBG_FILES
    debugger.h
    debugger.cpp)

add_library(dbg ${DBG_FILES})

target_link_libraries(dbg fmt-header-only)

