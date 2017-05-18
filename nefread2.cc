#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(void)
{
  FILE *fp;
  //char *fname = "/home/aws/Downloads/Aerial.bmp";
  Mat nef(4924, 7424, CV_16SC1);
  
  unsigned char * buf = nef.data;// new unsigned char[14848*4924];
  int  i, size;
  long lSize;

  fp = fopen("DSC_5670.NEF", "rb" );
  if( fp == NULL ){
    printf("ファイルが開けません¥n");
    return -1;
  }
  fseek(fp,0,SEEK_END);
  lSize = ftell(fp);
  rewind(fp);
  
  fseek(fp,lSize-(14848*4924),SEEK_SET);
  size = fread( buf, sizeof( unsigned char ), 14848*4924, fp );

  for(int a=0;a<size;a=a+2){
    unsigned char tmp;
    tmp = buf[a+1];
    buf[a+1] = buf[a];
    buf[a] = tmp;
  }

  Mat nef8, nef8small;
  nef.convertTo(nef8, CV_8UC1, 0.0390625);
  cvtColor(nef8,nef8,CV_BayerRG2BGR);
  //resize(nef8, nef8small, Size(640, 450));
  resize(nef8, nef8small, Size(), 0.1, 0.1);
  namedWindow("nef8");
  imshow("nef8", nef8small);
  cvWaitKey(0);
  fclose( fp );
  return 0;
}
