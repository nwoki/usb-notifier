include_directories(${PROJECT_SOURCE_DIR}/include)

set(example_SRCS
    inherit.cpp
    main.cpp
    testconnect.cpp
)

# final application
add_executable(example ${example_SRCS})

qt5_use_modules(example Core)

target_link_libraries(example usbnotifier)

