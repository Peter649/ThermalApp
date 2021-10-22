file(GLOB src
        src/ctrl.c
        src/device.c
        src/diag.c
        src/frame.c
#        src/frame-mjpeg.c
        src/init.c
        src/stream.c
        src/ctrl-gen.c

        src/ctrl-add.c
        )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DANDROID_NDK")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUVC_DEBUGGING")

add_library(uvc
        STATIC
        ${src}
        )

target_include_directories(uvc
        PRIVATE
        .
        include
        include/libuvc
        ../libusb
        ../libjpeg-turbo-1.5.0
        ../libjpeg-turbo-1.5.0/include
        ..
        )

target_link_libraries(uvc
        PRIVATE
        usb100
#        jpeg-turbo1500
        log
        )
