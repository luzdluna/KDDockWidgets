find_package(Qt5Test)


add_executable(tst_multisplitter tst_multisplitter.cpp)
target_link_libraries(tst_multisplitter kddockwidgets_multisplitter Qt5::Test)
