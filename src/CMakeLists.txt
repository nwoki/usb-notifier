set(usb-notifier_SRCS
    usbdevice.cpp
    usbnotifier.cpp
)


# final lib
add_library(usbnotifier SHARED ${usb-notifier_SRCS})

# https://en.wikipedia.org/wiki/Application_binary_interface
set_target_properties(usbnotifier PROPERTIES
                           OUTPUT_NAME usbnotifier
                           SOVERSION ${USBNOTIFIER_VERSION_ABI}
                           VERSION ${USBNOTIFIER_LIB_VERSION})

qt5_use_modules(usbnotifier Core)

# link with libusb
target_link_libraries(usbnotifier usb-1.0)

