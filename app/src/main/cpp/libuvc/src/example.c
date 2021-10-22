#include <stdio.h>
#include <unistd.h>
#include "libuvc/libuvc.h"
#include <unistd.h>
#include <pthread.h>
#include "opencv/cv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;


extern "C" {

void cb_IriUniverseTwo(uvc_frame_t *srcFrame, void *ptr) 
{
  unsigned char *ptrSrc;
  unsigned char *ptrDst;

  uvc_frame_t *dstFrame;
  uvc_error_t ret;
  unsigned long i, ii;

  enum uvc_frame_format *frame_format = (enum uvc_frame_format *)ptr;
  /* FILE *fp;
   * static int jpeg_count = 0;
   * static const char *H264_FILE = "iOSDevLog.h264";
   * static const char *MJPEG_FILE = ".jpeg";
   * char filename[16]; */

  /* We'll convert the image from YUV to MONO raw, so allocate space */
  dstFrame = uvc_allocate_frame(srcFrame->width * srcFrame->height);
  if (!dstFrame) {
    printf("unable to allocate dstFrame!\n");
    return;
  }

  printf("callback! frame_format = %d, width = %d, height = %d, length = %lu, ptr = %d\n",
    srcFrame->frame_format, srcFrame->width, srcFrame->height, srcFrame->data_bytes, (int) ptr);
   
  ptrDst = (unsigned char*)dstFrame->data;
  ptrSrc = (unsigned char*)srcFrame->data;

  for( i=0, ii=0; i<(srcFrame->width)*(srcFrame->height); i+=2, ii++)
  {
	*(ptrDst+ii) = *(ptrSrc+i);
  }

  Mat dispimg(dstFrame->height, dstFrame->width , CV_8UC1, dstFrame->data);

  imshow("Universe Video", dispimg);
  waitKey(1);

  uvc_free_frame(dstFrame);
}

extern int IriUniverseTwo_UvcInitDevice();
extern int IriUniverseTwo_UvcOpenDevice();
extern int IriUniverseTwo_UvcCloseDeivce();
extern int IriUniverseTwo_UvcInitDevice();
extern int IriUniverseTwo_UvcDeinitDevice();

extern int IriUniverseTwo_UvcReadByte(int regAddr, int *regDat);
extern int IriUniverseTwo_UvcWriteByte(int regAddr, int regDat);
extern int IriUniverseTwo_UvcBlinkLED();
extern int IriUniverseTwo_UvcGreenLED();
extern int IriUniverseTwo_UvcTurnOffLED();

}

//this function is called by capture funtion of uvc

pthread_t mThread;


static void* streamThreadProc(void* lpParam)
{
  
    
    while(1)
    {

	printf("Camera thread run\n");

	usleep(1000000);

    }	

    pthread_exit(0);

    

    return 0;
} // End of __EZFaceCamera_ThreadWinProc



int main(int argc, char **argv) 
{
  int regDat;
  pthread_attr_t attr;

 
  //Make a thread to test camera stream
  //pthread_attr_init(&attr);
  //pthread_create(&mThread, &attr, &streamThreadProc, 0);
  
  IriUniverseTwo_UvcInitDevice();

  IriUniverseTwo_UvcOpenDevice();   //open device and start stream


  //while(1)
  {

	  sleep(1);
	  printf("blink led\n");
	  IriUniverseTwo_UvcBlinkLED();

	  sleep(5);
	  printf("off led\n");
	  IriUniverseTwo_UvcTurnOffLED();

	  sleep(1);  
	  printf("green led\n");
	  IriUniverseTwo_UvcGreenLED();

	  sleep(2);
	  printf("off led\n");
	  IriUniverseTwo_UvcTurnOffLED();

	  sleep(2);
	  printf("read xu\n");
	  IriUniverseTwo_UvcReadByte(0x00, &regDat);
	  printf("blink led\n");   
	  sleep(1);
	  printf("write xu\n");
	  IriUniverseTwo_UvcWriteByte(0x00, 0xAA);
  } 


  IriUniverseTwo_UvcCloseDeivce();   //stop stream and close device


  pthread_attr_destroy(&attr);

  IriUniverseTwo_UvcDeinitDevice(); 
}


