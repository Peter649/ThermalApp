#include <jni.h>
#include <string>
#include <libuvc/libuvc.h>
#include <pthread.h>
#include "utilbase.h"
#include <mylog.h>

//typedef struct { const uint8_t colormap[256 * 3]; } colormap_t;
//
//const colormap_t colormap_rainbow = { {1, 3, 74, 0, 3, 74, 0, 3, 75, 0, 3, 75, 0, 3, 76, 0, 3, 76, 0, 3, 77, 0, 3, 79, 0, 3, 82, 0, 5, 85, 0, 7, 88, 0, 10, 91, 0, 14, 94, 0, 19, 98, 0, 22, 100, 0, 25, 103, 0, 28, 106, 0, 32, 109, 0, 35, 112, 0, 38, 116, 0, 40, 119, 0, 42, 123, 0, 45, 128, 0, 49, 133, 0, 50, 134, 0, 51, 136, 0, 52, 137, 0, 53, 139, 0, 54, 142, 0, 55, 144, 0, 56, 145, 0, 58, 149, 0, 61, 154, 0, 63, 156, 0, 65, 159, 0, 66, 161, 0, 68, 164, 0, 69, 167, 0, 71, 170, 0, 73, 174, 0, 75, 179, 0, 76, 181, 0, 78, 184, 0, 79, 187, 0, 80, 188, 0, 81, 190, 0, 84, 194, 0, 87, 198, 0, 88, 200, 0, 90, 203, 0, 92, 205, 0, 94, 207, 0, 94, 208, 0, 95, 209, 0, 96, 210, 0, 97, 211, 0, 99, 214, 0, 102, 217, 0, 103, 218, 0, 104, 219, 0, 105, 220, 0, 107, 221, 0, 109, 223, 0, 111, 223, 0, 113, 223, 0, 115, 222, 0, 117, 221, 0, 118, 220, 1, 120, 219, 1, 122, 217, 2, 124, 216, 2, 126, 214, 3, 129, 212, 3, 131, 207, 4, 132, 205, 4, 133, 202, 4, 134, 197, 5, 136, 192, 6, 138, 185, 7, 141, 178, 8, 142, 172, 10, 144, 166, 10, 144, 162, 11, 145, 158, 12, 146, 153, 13, 147, 149, 15, 149, 140, 17, 151, 132, 22, 153, 120, 25, 154, 115, 28, 156, 109, 34, 158, 101, 40, 160, 94, 45, 162, 86, 51, 164, 79, 59, 167, 69, 67, 171, 60, 72, 173, 54, 78, 175, 48, 83, 177, 43, 89, 179, 39, 93, 181, 35, 98, 183, 31, 105, 185, 26, 109, 187, 23, 113, 188, 21, 118, 189, 19, 123, 191, 17, 128, 193, 14, 134, 195, 12, 138, 196, 10, 142, 197, 8, 146, 198, 6, 151, 200, 5, 155, 201, 4, 160, 203, 3, 164, 204, 2, 169, 205, 2, 173, 206, 1, 175, 207, 1, 178, 207, 1, 184, 208, 0, 190, 210, 0, 193, 211, 0, 196, 212, 0, 199, 212, 0, 202, 213, 1, 207, 214, 2, 212, 215, 3, 215, 214, 3, 218, 214, 3, 220, 213, 3, 222, 213, 4, 224, 212, 4, 225, 212, 5, 226, 212, 5, 229, 211, 5, 232, 211, 6, 232, 211, 6, 233, 211, 6, 234, 210, 6, 235, 210, 7, 236, 209, 7, 237, 208, 8, 239, 206, 8, 241, 204, 9, 242, 203, 9, 244, 202, 10, 244, 201, 10, 245, 200, 10, 245, 199, 11, 246, 198, 11, 247, 197, 12, 248, 194, 13, 249, 191, 14, 250, 189, 14, 251, 187, 15, 251, 185, 16, 252, 183, 17, 252, 178, 18, 253, 174, 19, 253, 171, 19, 254, 168, 20, 254, 165, 21, 254, 164, 21, 255, 163, 22, 255, 161, 22, 255, 159, 23, 255, 157, 23, 255, 155, 24, 255, 149, 25, 255, 143, 27, 255, 139, 28, 255, 135, 30, 255, 131, 31, 255, 127, 32, 255, 118, 34, 255, 110, 36, 255, 104, 37, 255, 101, 38, 255, 99, 39, 255, 93, 40, 255, 88, 42, 254, 82, 43, 254, 77, 45, 254, 69, 47, 254, 62, 49, 253, 57, 50, 253, 53, 52, 252, 49, 53, 252, 45, 55, 251, 39, 57, 251, 33, 59, 251, 32, 60, 251, 31, 60, 251, 30, 61, 251, 29, 61, 251, 28, 62, 250, 27, 63, 250, 27, 65, 249, 26, 66, 249, 26, 68, 248, 25, 70, 248, 24, 73, 247, 24, 75, 247, 25, 77, 247, 25, 79, 247, 26, 81, 247, 32, 83, 247, 35, 85, 247, 38, 86, 247, 42, 88, 247, 46, 90, 247, 50, 92, 248, 55, 94, 248, 59, 96, 248, 64, 98, 248, 72, 101, 249, 81, 104, 249, 87, 106, 250, 93, 108, 250, 95, 109, 250, 98, 110, 250, 100, 111, 251, 101, 112, 251, 102, 113, 251, 109, 117, 252, 116, 121, 252, 121, 123, 253, 126, 126, 253, 130, 128, 254, 135, 131, 254, 139, 133, 254, 144, 136, 254, 151, 140, 255, 158, 144, 255, 163, 146, 255, 168, 149, 255, 173, 152, 255, 176, 153, 255, 178, 155, 255, 184, 160, 255, 191, 165, 255, 195, 168, 255, 199, 172, 255, 203, 175, 255, 207, 179, 255, 211, 182, 255, 216, 185, 255, 218, 190, 255, 220, 196, 255, 222, 200, 255, 225, 202, 255, 227, 204, 255, 230, 206, 255, 233, 208} };
//const colormap_t colormap_grayscale = { {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 21, 22, 22, 22, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, 43, 44, 44, 44, 45, 45, 45, 46, 46, 46, 47, 47, 47, 48, 48, 48, 49, 49, 49, 50, 50, 50, 51, 51, 51, 52, 52, 52, 53, 53, 53, 54, 54, 54, 55, 55, 55, 56, 56, 56, 57, 57, 57, 58, 58, 58, 59, 59, 59, 60, 60, 60, 61, 61, 61, 62, 62, 62, 63, 63, 63, 64, 64, 64, 65, 65, 65, 66, 66, 66, 67, 67, 67, 68, 68, 68, 69, 69, 69, 70, 70, 70, 71, 71, 71, 72, 72, 72, 73, 73, 73, 74, 74, 74, 75, 75, 75, 76, 76, 76, 77, 77, 77, 78, 78, 78, 79, 79, 79, 80, 80, 80, 81, 81, 81, 82, 82, 82, 83, 83, 83, 84, 84, 84, 85, 85, 85, 86, 86, 86, 87, 87, 87, 88, 88, 88, 89, 89, 89, 90, 90, 90, 91, 91, 91, 92, 92, 92, 93, 93, 93, 94, 94, 94, 95, 95, 95, 96, 96, 96, 97, 97, 97, 98, 98, 98, 99, 99, 99, 100, 100, 100, 101, 101, 101, 102, 102, 102, 103, 103, 103, 104, 104, 104, 105, 105, 105, 106, 106, 106, 107, 107, 107, 108, 108, 108, 109, 109, 109, 110, 110, 110, 111, 111, 111, 112, 112, 112, 113, 113, 113, 114, 114, 114, 115, 115, 115, 116, 116, 116, 117, 117, 117, 118, 118, 118, 119, 119, 119, 120, 120, 120, 121, 121, 121, 122, 122, 122, 123, 123, 123, 124, 124, 124, 125, 125, 125, 126, 126, 126, 127, 127, 127, 128, 128, 128, 129, 129, 129, 130, 130, 130, 131, 131, 131, 132, 132, 132, 133, 133, 133, 134, 134, 134, 135, 135, 135, 136, 136, 136, 137, 137, 137, 138, 138, 138, 139, 139, 139, 140, 140, 140, 141, 141, 141, 142, 142, 142, 143, 143, 143, 144, 144, 144, 145, 145, 145, 146, 146, 146, 147, 147, 147, 148, 148, 148, 149, 149, 149, 150, 150, 150, 151, 151, 151, 152, 152, 152, 153, 153, 153, 154, 154, 154, 155, 155, 155, 156, 156, 156, 157, 157, 157, 158, 158, 158, 159, 159, 159, 160, 160, 160, 161, 161, 161, 162, 162, 162, 163, 163, 163, 164, 164, 164, 165, 165, 165, 166, 166, 166, 167, 167, 167, 168, 168, 168, 169, 169, 169, 170, 170, 170, 171, 171, 171, 172, 172, 172, 173, 173, 173, 174, 174, 174, 175, 175, 175, 176, 176, 176, 177, 177, 177, 178, 178, 178, 179, 179, 179, 180, 180, 180, 181, 181, 181, 182, 182, 182, 183, 183, 183, 184, 184, 184, 185, 185, 185, 186, 186, 186, 187, 187, 187, 188, 188, 188, 189, 189, 189, 190, 190, 190, 191, 191, 191, 192, 192, 192, 193, 193, 193, 194, 194, 194, 195, 195, 195, 196, 196, 196, 197, 197, 197, 198, 198, 198, 199, 199, 199, 200, 200, 200, 201, 201, 201, 202, 202, 202, 203, 203, 203, 204, 204, 204, 205, 205, 205, 206, 206, 206, 207, 207, 207, 208, 208, 208, 209, 209, 209, 210, 210, 210, 211, 211, 211, 212, 212, 212, 213, 213, 213, 214, 214, 214, 215, 215, 215, 216, 216, 216, 217, 217, 217, 218, 218, 218, 219, 219, 219, 220, 220, 220, 221, 221, 221, 222, 222, 222, 223, 223, 223, 224, 224, 224, 225, 225, 225, 226, 226, 226, 227, 227, 227, 228, 228, 228, 229, 229, 229, 230, 230, 230, 231, 231, 231, 232, 232, 232, 233, 233, 233, 234, 234, 234, 235, 235, 235, 236, 236, 236, 237, 237, 237, 238, 238, 238, 239, 239, 239, 240, 240, 240, 241, 241, 241, 242, 242, 242, 243, 243, 243, 244, 244, 244, 245, 245, 245, 246, 246, 246, 247, 247, 247, 248, 248, 248, 249, 249, 249, 250, 250, 250, 251, 251, 251, 252, 252, 252, 253, 253, 253, 254, 254, 254, 255, 255, 255} };
//const colormap_t colormap_ironblack = { {255, 255, 255, 253, 253, 253, 251, 251, 251, 249, 249, 249, 247, 247, 247, 245, 245, 245, 243, 243, 243, 241, 241, 241, 239, 239, 239, 237, 237, 237, 235, 235, 235, 233, 233, 233, 231, 231, 231, 229, 229, 229, 227, 227, 227, 225, 225, 225, 223, 223, 223, 221, 221, 221, 219, 219, 219, 217, 217, 217, 215, 215, 215, 213, 213, 213, 211, 211, 211, 209, 209, 209, 207, 207, 207, 205, 205, 205, 203, 203, 203, 201, 201, 201, 199, 199, 199, 197, 197, 197, 195, 195, 195, 193, 193, 193, 191, 191, 191, 189, 189, 189, 187, 187, 187, 185, 185, 185, 183, 183, 183, 181, 181, 181, 179, 179, 179, 177, 177, 177, 175, 175, 175, 173, 173, 173, 171, 171, 171, 169, 169, 169, 167, 167, 167, 165, 165, 165, 163, 163, 163, 161, 161, 161, 159, 159, 159, 157, 157, 157, 155, 155, 155, 153, 153, 153, 151, 151, 151, 149, 149, 149, 147, 147, 147, 145, 145, 145, 143, 143, 143, 141, 141, 141, 139, 139, 139, 137, 137, 137, 135, 135, 135, 133, 133, 133, 131, 131, 131, 129, 129, 129, 126, 126, 126, 124, 124, 124, 122, 122, 122, 120, 120, 120, 118, 118, 118, 116, 116, 116, 114, 114, 114, 112, 112, 112, 110, 110, 110, 108, 108, 108, 106, 106, 106, 104, 104, 104, 102, 102, 102, 100, 100, 100, 98, 98, 98, 96, 96, 96, 94, 94, 94, 92, 92, 92, 90, 90, 90, 88, 88, 88, 86, 86, 86, 84, 84, 84, 82, 82, 82, 80, 80, 80, 78, 78, 78, 76, 76, 76, 74, 74, 74, 72, 72, 72, 70, 70, 70, 68, 68, 68, 66, 66, 66, 64, 64, 64, 62, 62, 62, 60, 60, 60, 58, 58, 58, 56, 56, 56, 54, 54, 54, 52, 52, 52, 50, 50, 50, 48, 48, 48, 46, 46, 46, 44, 44, 44, 42, 42, 42, 40, 40, 40, 38, 38, 38, 36, 36, 36, 34, 34, 34, 32, 32, 32, 30, 30, 30, 28, 28, 28, 26, 26, 26, 24, 24, 24, 22, 22, 22, 20, 20, 20, 18, 18, 18, 16, 16, 16, 14, 14, 14, 12, 12, 12, 10, 10, 10, 8, 8, 8, 6, 6, 6, 4, 4, 4, 2, 2, 2, 0, 0, 0, 0, 0, 9, 2, 0, 16, 4, 0, 24, 6, 0, 31, 8, 0, 38, 10, 0, 45, 12, 0, 53, 14, 0, 60, 17, 0, 67, 19, 0, 74, 21, 0, 82, 23, 0, 89, 25, 0, 96, 27, 0, 103, 29, 0, 111, 31, 0, 118, 36, 0, 120, 41, 0, 121, 46, 0, 122, 51, 0, 123, 56, 0, 124, 61, 0, 125, 66, 0, 126, 71, 0, 127, 76, 1, 128, 81, 1, 129, 86, 1, 130, 91, 1, 131, 96, 1, 132, 101, 1, 133, 106, 1, 134, 111, 1, 135, 116, 1, 136, 121, 1, 136, 125, 2, 137, 130, 2, 137, 135, 3, 137, 139, 3, 138, 144, 3, 138, 149, 4, 138, 153, 4, 139, 158, 5, 139, 163, 5, 139, 167, 5, 140, 172, 6, 140, 177, 6, 140, 181, 7, 141, 186, 7, 141, 189, 10, 137, 191, 13, 132, 194, 16, 127, 196, 19, 121, 198, 22, 116, 200, 25, 111, 203, 28, 106, 205, 31, 101, 207, 34, 95, 209, 37, 90, 212, 40, 85, 214, 43, 80, 216, 46, 75, 218, 49, 69, 221, 52, 64, 223, 55, 59, 224, 57, 49, 225, 60, 47, 226, 64, 44, 227, 67, 42, 228, 71, 39, 229, 74, 37, 230, 78, 34, 231, 81, 32, 231, 85, 29, 232, 88, 27, 233, 92, 24, 234, 95, 22, 235, 99, 19, 236, 102, 17, 237, 106, 14, 238, 109, 12, 239, 112, 12, 240, 116, 12, 240, 119, 12, 241, 123, 12, 241, 127, 12, 242, 130, 12, 242, 134, 12, 243, 138, 12, 243, 141, 13, 244, 145, 13, 244, 149, 13, 245, 152, 13, 245, 156, 13, 246, 160, 13, 246, 163, 13, 247, 167, 13, 247, 171, 13, 248, 175, 14, 248, 178, 15, 249, 182, 16, 249, 185, 18, 250, 189, 19, 250, 192, 20, 251, 196, 21, 251, 199, 22, 252, 203, 23, 252, 206, 24, 253, 210, 25, 253, 213, 27, 254, 217, 28, 254, 220, 29, 255, 224, 30, 255, 227, 39, 255, 229, 53, 255, 231, 67, 255, 233, 81, 255, 234, 95, 255, 236, 109, 255, 238, 123, 255, 240, 137, 255, 242, 151, 255, 244, 165, 255, 246, 179, 255, 248, 193, 255, 249, 207, 255, 251, 221, 255, 253, 235, 255, 255, 24} };

const uint8_t colormap[
        256 * 3] = {1, 3, 74, 0, 3, 74, 0, 3, 75, 0, 3, 75, 0, 3, 76, 0, 3, 76, 0, 3, 77, 0, 3, 79,
                    0, 3, 82, 0, 5, 85, 0, 7, 88, 0, 10, 91, 0, 14, 94, 0, 19, 98, 0, 22, 100, 0,
                    25, 103, 0, 28, 106, 0, 32, 109, 0, 35, 112, 0, 38, 116, 0, 40, 119, 0, 42, 123,
                    0, 45, 128, 0, 49, 133, 0, 50, 134, 0, 51, 136, 0, 52, 137, 0, 53, 139, 0, 54,
                    142, 0, 55, 144, 0, 56, 145, 0, 58, 149, 0, 61, 154, 0, 63, 156, 0, 65, 159, 0,
                    66, 161, 0, 68, 164, 0, 69, 167, 0, 71, 170, 0, 73, 174, 0, 75, 179, 0, 76, 181,
                    0, 78, 184, 0, 79, 187, 0, 80, 188, 0, 81, 190, 0, 84, 194, 0, 87, 198, 0, 88,
                    200, 0, 90, 203, 0, 92, 205, 0, 94, 207, 0, 94, 208, 0, 95, 209, 0, 96, 210, 0,
                    97, 211, 0, 99, 214, 0, 102, 217, 0, 103, 218, 0, 104, 219, 0, 105, 220, 0, 107,
                    221, 0, 109, 223, 0, 111, 223, 0, 113, 223, 0, 115, 222, 0, 117, 221, 0, 118,
                    220, 1, 120, 219, 1, 122, 217, 2, 124, 216, 2, 126, 214, 3, 129, 212, 3, 131,
                    207, 4, 132, 205, 4, 133, 202, 4, 134, 197, 5, 136, 192, 6, 138, 185, 7, 141,
                    178, 8, 142, 172, 10, 144, 166, 10, 144, 162, 11, 145, 158, 12, 146, 153, 13,
                    147, 149, 15, 149, 140, 17, 151, 132, 22, 153, 120, 25, 154, 115, 28, 156, 109,
                    34, 158, 101, 40, 160, 94, 45, 162, 86, 51, 164, 79, 59, 167, 69, 67, 171, 60,
                    72, 173, 54, 78, 175, 48, 83, 177, 43, 89, 179, 39, 93, 181, 35, 98, 183, 31,
                    105, 185, 26, 109, 187, 23, 113, 188, 21, 118, 189, 19, 123, 191, 17, 128, 193,
                    14, 134, 195, 12, 138, 196, 10, 142, 197, 8, 146, 198, 6, 151, 200, 5, 155, 201,
                    4, 160, 203, 3, 164, 204, 2, 169, 205, 2, 173, 206, 1, 175, 207, 1, 178, 207, 1,
                    184, 208, 0, 190, 210, 0, 193, 211, 0, 196, 212, 0, 199, 212, 0, 202, 213, 1,
                    207, 214, 2, 212, 215, 3, 215, 214, 3, 218, 214, 3, 220, 213, 3, 222, 213, 4,
                    224, 212, 4, 225, 212, 5, 226, 212, 5, 229, 211, 5, 232, 211, 6, 232, 211, 6,
                    233, 211, 6, 234, 210, 6, 235, 210, 7, 236, 209, 7, 237, 208, 8, 239, 206, 8,
                    241, 204, 9, 242, 203, 9, 244, 202, 10, 244, 201, 10, 245, 200, 10, 245, 199,
                    11, 246, 198, 11, 247, 197, 12, 248, 194, 13, 249, 191, 14, 250, 189, 14, 251,
                    187, 15, 251, 185, 16, 252, 183, 17, 252, 178, 18, 253, 174, 19, 253, 171, 19,
                    254, 168, 20, 254, 165, 21, 254, 164, 21, 255, 163, 22, 255, 161, 22, 255, 159,
                    23, 255, 157, 23, 255, 155, 24, 255, 149, 25, 255, 143, 27, 255, 139, 28, 255,
                    135, 30, 255, 131, 31, 255, 127, 32, 255, 118, 34, 255, 110, 36, 255, 104, 37,
                    255, 101, 38, 255, 99, 39, 255, 93, 40, 255, 88, 42, 254, 82, 43, 254, 77, 45,
                    254, 69, 47, 254, 62, 49, 253, 57, 50, 253, 53, 52, 252, 49, 53, 252, 45, 55,
                    251, 39, 57, 251, 33, 59, 251, 32, 60, 251, 31, 60, 251, 30, 61, 251, 29, 61,
                    251, 28, 62, 250, 27, 63, 250, 27, 65, 249, 26, 66, 249, 26, 68, 248, 25, 70,
                    248, 24, 73, 247, 24, 75, 247, 25, 77, 247, 25, 79, 247, 26, 81, 247, 32, 83,
                    247, 35, 85, 247, 38, 86, 247, 42, 88, 247, 46, 90, 247, 50, 92, 248, 55, 94,
                    248, 59, 96, 248, 64, 98, 248, 72, 101, 249, 81, 104, 249, 87, 106, 250, 93,
                    108, 250, 95, 109, 250, 98, 110, 250, 100, 111, 251, 101, 112, 251, 102, 113,
                    251, 109, 117, 252, 116, 121, 252, 121, 123, 253, 126, 126, 253, 130, 128, 254,
                    135, 131, 254, 139, 133, 254, 144, 136, 254, 151, 140, 255, 158, 144, 255, 163,
                    146, 255, 168, 149, 255, 173, 152, 255, 176, 153, 255, 178, 155, 255, 184, 160,
                    255, 191, 165, 255, 195, 168, 255, 199, 172, 255, 203, 175, 255, 207, 179, 255,
                    211, 182, 255, 216, 185, 255, 218, 190, 255, 220, 196, 255, 222, 200, 255, 225,
                    202, 255, 227, 204, 255, 230, 206, 255, 233, 208};

uvc_device_handle_t *g_devh_IriUniverseTwo_ = NULL;
uvc_context_t *ctx_IriUniverseTwo_;
uvc_stream_ctrl_t ctrl_IriUniverseTwo_;
uvc_device_t *g_dev_IriUniverseTwo_ = NULL;
int g_isStreaming_IriUniverseTwo_ = 0;
uvc_stream_handle_t *g_streamHandle = 0;

jbyteArray gBuffer;

JavaVM *gJvm;
jmethodID g_method;
jobject g_jobject;
jobject g_buffer;
unsigned char *ptr;
pthread_mutex_t lock;


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_thermalapp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
int iter = 0;

void cb(uvc_frame_t *frame, void *pointer) {
    uvc_frame_t *bgr;
    uvc_error_t ret;
    /* We'll convert the image from YUV/JPEG to BGR, so allocate space */
//    bgr = uvc_allocate_frame(frame->width * frame->height * 3);
//    if (!bgr) {
//        LOGD("unable to allocate bgr frame!");
//        return;
//    }
//    /* Do the BGR conversion */
//    ret = uvc_any2bgr(frame, bgr);
//    if (ret) {
//        uvc_perror(ret, "uvc_any2bgr");
//        uvc_free_frame(bgr);
//        return;
//    }

//    LOGD("streaimng");
    JNIEnv *env;
    gJvm->AttachCurrentThread(&env, NULL);
    env->CallVoidMethod(g_jobject, g_method);
    gJvm->DetachCurrentThread();

    uint8_t *p;
    p = (uint8_t *) frame->data;
    MYLOGD("%d %d %d %d %d %d %d %d %d %d ", p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8],
           p[9]);
    MYLOGD("%d %d %d %d %d %d %d %d %d %d ", p[320], p[321], p[322], p[323], p[324], p[325], p[326],
           p[327], p[328], p[329]);
    MYLOGD("%d %d %d %d %d %d %d %d %d %d ", p[640], p[641], p[642], p[643], p[644], p[645], p[646],
           p[647], p[648], p[649]);
    const uint8_t *palette = colormap;
    MYLOGD("%d %d ", frame->width, frame->height);

    pthread_mutex_lock(&lock);
//    for (uint32_t i = 0; i < frame->height; i++)
//    {
////        uint8_t* rgba_line = &output.bits()[output.bytesPerLine() * i];
//        for (uint32_t j = 0; j < frame->width; j++)
//        {
//            // assume little-endian, and that we have already contrast extended into 8-bit
//            uint8_t val = ((uint8_t*)frame->data)[i * frame->width * 2 + j * 2];
//            const uint8_t *rgb = &palette[val * 3];
//
//            ptr[i * 160 + j * 4 + 0] = rgb[2];
//            ptr[i * 160 + j * 4 + 1] = rgb[1];
//            ptr[i * 160 + j * 4 + 2] = rgb[0];
//            ptr[i * 160 + j * 4 + 3] = 0xff;
//        }
//    }

    uint8_t max = 0;
    uint8_t min = 256;

    for (int i = 0; i < 160 * 120; i++) {
        uint8_t val = p[i * 2];
        if(val < min)
            min = val;
        if(val > max)
            max = val;
    }

    for (int i = 0; i < 160 * 120; i++) {
        uint8_t val = p[i * 2];
//        val = (uint8_t)(((float)(val - min) / (float)(max - min)) * 255.0f);
//        val = (uint8_t)(((float)(val - min) / (float)(max - min)) * 255.0f);

        const uint8_t *rgb = &palette[10 * 3];
        ptr[i * 4 + 0] = rgb[2];
        ptr[i * 4 + 1] = rgb[1];
        ptr[i * 4 + 2] = rgb[0];
        ptr[i * 4 + 3] = 0xff;
    }


    pthread_mutex_unlock(&lock);



//    switch (iter) {
//        case 0: {
//            for (int i = 0; i < 160 * 120; i++) {
//                ptr[i * 4] = 0xff;
//                ptr[i * 4 + 1] = 0;
//                ptr[i * 4 + 2] = 0;
//                ptr[i * 4 + 3] = 0xff;
//            }
//
//        }
//            break;
//        case 1: {
//            for (int i = 0; i < 160 * 120; i++) {
//                ptr[i * 4] = 0;
//                ptr[i * 4 + 1] = 0;
//                ptr[i * 4 + 2] = 0xff;
//                ptr[i * 4 + 3] = 0xff;
//            }
//        }
//            break;
//        case 2:
//        default: {
//            for (int i = 0; i < 160 * 120; i++) {
//                ptr[i * 4] = 0;
//                ptr[i * 4 + 1] = 0xff;
//                ptr[i * 4 + 2] = 0;
//                ptr[i * 4 + 3] = 0xff;
//            }
//        }
//            break;
//
//    }
//
//    iter++;
//    if (iter == 3)
//        iter = 0;

    /* Call a user function:
     *
     * my_type *my_obj = (*my_type) ptr;
     * my_user_function(ptr, bgr);
     * my_other_function(ptr, bgr->data, bgr->width, bgr->height);
     */
    /* Call a C++ method:
     *
     * my_type *my_obj = (*my_type) ptr;
     * my_obj->my_func(bgr);
     */
    /* Use opencv.highgui to display the image:
     *
     * cvImg = cvCreateImageHeader(
     *     cvSize(bgr->width, bgr->height),
     *     IPL_DEPTH_8U,
     *     3);
     *
     * cvSetData(cvImg, bgr->data, bgr->width * 3);
     *
     * cvNamedWindow("Test", CV_WINDOW_AUTOSIZE);
     * cvShowImage("Test", cvImg);
     * cvWaitKey(10);
     *
     * cvReleaseImageHeader(&cvImg);
     */
//    uvc_free_frame(bgr);
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_thermalapp_MainActivity_startCamera(JNIEnv *env, jobject thiz, jint vid, jint pid,
                                                     jint fd, jint bus_num, jint dev_num) {
    uvc_error_t res;

    /* Initialize a UVC service context. Libuvc will set up its own libusb
     * context. Replace NULL with a libusb_context pointer to run libuvc
     * from an existing libusb context. */
    res = uvc_init2(&ctx_IriUniverseTwo_, NULL, "/dev/bus/usb");

    if (res < 0) {
        uvc_perror(res, "uvc_init");
        return -1;
    }

    puts("UVC initialized");

    /* Locates the first attached UVC device, stores in dev */
    res = uvc_get_device_with_fd(ctx_IriUniverseTwo_, &g_dev_IriUniverseTwo_, vid, pid, NULL, fd,
                                 bus_num, dev_num);

    if (res < 0) {
        uvc_perror(res, "uvc_find_device"); /* no devices found */
        return -1;
    }
    puts("Device found");

    /// open

    if (g_dev_IriUniverseTwo_ == NULL) {
        LOGD("g_dev_IriUniverseTwo_ is NULL\n");

        return -1;
    }

    /* Try to open the device: requires exclusive access */
    res = uvc_open(g_dev_IriUniverseTwo_, &g_devh_IriUniverseTwo_);

    if (res < 0) {
        uvc_perror(res, "uvc_open"); /* unable to open device */
        return -1;
    }
    /* Print out a message containing all the information that libuvc
     * knows about the device */
    //uvc_print_diag(g_devh_IriUniverseTwo_, stderr);

    const uvc_format_desc_t *format_desc = uvc_get_format_descs(g_devh_IriUniverseTwo_);
    const uvc_frame_desc_t *frame_desc = format_desc->frame_descs;
    enum uvc_frame_format frame_format;
    int width = 160;
    int height = 120;
    int fps = 30;

    switch (format_desc->bDescriptorSubtype) {
        case UVC_VS_FORMAT_MJPEG:
            frame_format = UVC_COLOR_FORMAT_MJPEG;
            break;
        case UVC_VS_FORMAT_FRAME_BASED:
            frame_format = UVC_FRAME_FORMAT_H264;
            break;
        default:
            frame_format = UVC_FRAME_FORMAT_GRAY16;
            break;
    }

    if (frame_desc) {
        width = frame_desc->wWidth;
        height = frame_desc->wHeight;
        fps = 10000000 / frame_desc->dwDefaultFrameInterval;
    }

    LOGD("\nFirst format: (%4s) %dx%d %dfps\n", format_desc->fourccFormat, width, height, fps);

    /* Try to negotiate first stream profile */
    res = uvc_get_stream_ctrl_format_size(
            g_devh_IriUniverseTwo_, &ctrl_IriUniverseTwo_, /* result stored in ctrl */
            frame_format,
            width, height, fps /* width, height, fps */
    );

    /* Print out the result */
    //uvc_print_stream_ctrl(&ctrl_IriUniverseTwo_, stderr);

    if (res < 0) {
        uvc_perror(res, "get_mode"); /* device doesn't provide a matching stream */
        return -1;
    }

#if 1
    /* Start the video stream. The library will call user function cb:
         *   cb(frame, (void *) 12345)
         */
    res = uvc_start_streaming(g_devh_IriUniverseTwo_, &ctrl_IriUniverseTwo_, cb, (void *) 12345, 0);
    if (res != UVC_SUCCESS) {
        uvc_perror(res, "start_streaming"); /* unable to start stream */
        LOGD("%s: Error in uvc_stream_start : %d\n", __FUNCTION__, res);
        return -1;
    }

    g_isStreaming_IriUniverseTwo_ = 1;


    LOGD("%s: Start streaming...\n", __FUNCTION__);
#endif

    return 0;

    // TODO: implement startCamera()
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_thermalapp_MainActivity_stopCamera(JNIEnv *env, jobject thiz) {
    // close

    if (g_devh_IriUniverseTwo_ == NULL) {
        LOGD("g_devh_IriUniverseTwo_=NULL\n");
        return -1;
    }

    if (g_isStreaming_IriUniverseTwo_ == 0) {
        LOGD("Uvc not streaming, returning\n");
        return -1;
    }


    /* End the stream. Blocks until last callback is serviced */
    uvc_stop_streaming(g_devh_IriUniverseTwo_);

    g_isStreaming_IriUniverseTwo_ = 0;

    /* Release our handle on the device */
    uvc_close(g_devh_IriUniverseTwo_);

    g_devh_IriUniverseTwo_ = NULL;

    LOGD("Device closed\n");

    //de init

    /* Release the device descriptor */
    uvc_unref_device(g_dev_IriUniverseTwo_);
    LOGD("uvc_unref_device\n");

    /* Close the UVC context. This closes and cleans up any existing device handles,
     * and it closes the libusb context if one was not provided. */
    uvc_exit(ctx_IriUniverseTwo_);
    LOGD("UVC exited\n");

    return 0;
}


JNIEXPORT jint JNI_OnLoad(JavaVM *pVM, void *reserved) {
    gJvm = pVM;

    JNIEnv *env;
    gJvm->GetEnv((void **) &env, JNI_VERSION_1_6);

    jclass mainClass = env->FindClass("com/example/thermalapp/MainActivity");
    g_method = (env)->GetMethodID(mainClass, "callback", "()V");

    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_thermalapp_MainActivity_init(JNIEnv *env, jobject thiz, jbyteArray buffer) {
    g_jobject = env->NewGlobalRef(thiz);
    g_buffer = env->NewGlobalRef(buffer);
    ptr = new unsigned char[160 * 120 * 4];
    pthread_mutex_init(&lock, NULL);
//    env->SetByteArrayRegion (buffer, 0, 160*120*4, reinterpret_cast<jbyte*>(ptr));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_thermalapp_MainActivity_term(JNIEnv *env, jobject thiz) {
    env->DeleteGlobalRef(g_jobject);
    env->DeleteGlobalRef(g_buffer);
    delete[] ptr;
    pthread_mutex_destroy(&lock);
}
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_thermalapp_MainActivity_takeBuffer(JNIEnv *env, jobject thiz) {
    jbyteArray array = env->NewByteArray(160 * 120 * 4);
    pthread_mutex_lock(&lock);
    env->SetByteArrayRegion(array, 0, 160 * 120 * 4, reinterpret_cast<jbyte *>(ptr));
    pthread_mutex_unlock(&lock);
    return array;
}