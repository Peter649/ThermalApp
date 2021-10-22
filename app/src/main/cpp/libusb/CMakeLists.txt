set(src
        libusb/core.c
        libusb/descriptor.c
        libusb/hotplug.c
        libusb/io.c
        libusb/sync.c
        libusb/strerror.c
        libusb/os/android_usbfs.c
        libusb/os/poll_posix.c
        libusb/os/threads_posix.c
        libusb/os/android_netlink.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DANDROID_NDK")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DACCESS_RAW_DESCRIPTORS")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fstrict-aliasing")
# -fprefetch-loop-arrays")

add_library(usb100
        SHARED
        ${src}
        )

target_include_directories(usb100
        PRIVATE
        .
        libusb
        libusb/os
        android
        ..
        )

target_link_libraries(
        usb100
        PRIVATE
        log
)

