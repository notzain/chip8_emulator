set(UI_FILES
        GameWindow.h
        GameWindow.cpp
        ICanvas.h
        GameCanvas.cpp GameCanvas.h KeypadCanvas.cpp KeypadCanvas.h)

add_library(ui ${UI_FILES})

target_link_libraries(ui PRIVATE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} core)