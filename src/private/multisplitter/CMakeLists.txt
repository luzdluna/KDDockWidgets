set(MULTISPLITTER_SRCS
    Config.cpp
    Config.h
    Item.cpp
    Item_p.h
    Widget.h
    Logging.cpp
    Logging_p.h
    Separator.cpp
    Separator_p.h

    multisplitter_export.h

    # QWidget frontend:
    Widget_qwidget.cpp
    Widget_qwidget.h
    Separator_qwidget.cpp
    Separator_qwidget.h
)

add_library(kddockwidgets_multisplitter SHARED ${MULTISPLITTER_SRCS})
add_library(KDAB::kddockwidgets_multisplitter ALIAS kddockwidgets_multisplitter)
target_link_libraries(kddockwidgets_multisplitter Qt5::Core Qt5::Widgets)

target_compile_definitions(kddockwidgets_multisplitter PRIVATE BUILDING_MULTISPLITTER_LIBRARY)

if (OPTION_DEVELOPER_MODE)
    add_subdirectory(tests)
#    add_subdirectory(examples)
endif()

target_include_directories(kddockwidgets_multisplitter
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
