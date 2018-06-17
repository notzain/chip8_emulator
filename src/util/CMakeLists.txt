set(UTIL_FILES
        logger.h
        logger.cpp
        )

add_library(util ${UTIL_FILES})

target_link_libraries(util PRIVATE fmt-header-only)