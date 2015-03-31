set(usb-notifier_SRCS
    usbnotifier.cpp
)


# final lib
add_library(usbnotifier SHARED ${usb-notifier_SRCS})

qt5_use_modules(usbnotifier Core)

# link with libusb
target_link_libraries(usbnotifier usb)

