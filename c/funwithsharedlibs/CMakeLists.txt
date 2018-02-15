add_executable(myprogram hello.c)
#target_link_libraries(myprogram dl)
#target_link_libraries(myprogram myfirstlib)

add_library(myfirstlib SHARED myfirstlib.c)
target_link_libraries(myfirstlib dl)

add_library(mysecondlib SHARED mysecondlib.c)
target_link_libraries(mysecondlib mythirdlib)

add_library(mythirdlib SHARED mythirdlib.c)
