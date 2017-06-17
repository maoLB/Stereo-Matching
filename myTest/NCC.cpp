/*************************************************************************
    > File Name: NNC.cpp
    > Author: ll.pan
    > Mail: ll.pan931204@gmail.com 
    > Created Time: 2017年06月17日 星期六 14时57分02秒
 ************************************************************************/

#include<iostream>   
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <cmath>   
using namespace std;  
using namespace cv;

int main(int argc,char** argv){  
    /*Half of the window size for the census transform*/  
    int hWin = 11;  
    int compareLength = (2*hWin+1)*(2*hWin+1);  

    cout<<"hWin: "<<hWin<<";  "<<"compare length:  "<<compareLength<<endl;    
    cout<<"NCC test"<<endl;  

    Mat leftImage = imread(argv[1],0);                             
    Mat rightImage = imread(argv[2],0);  

    int imageWidth = leftImage.cols;  
    int imageHeight =leftImage.rows;  

    Mat NCCImage;
    NCCImage.create(leftImage.rows,leftImage.cols,leftImage.type());  
    Mat MatchLevelImage;
    MatchLevelImage.create(leftImage.rows,leftImage.cols,leftImage.type());  

    int minDBounds = 0;  
    int maxDBounds = 31;  

    imwrite("Left.jpg",leftImage);  
    imwrite("Right.jpg",rightImage); 
    
//    imshow("Left",leftImage);  
//    imshow("Right",rightImage);  

    /*Census Transform */  
    int i,j ,m,n,k;  
    unsigned char centerPixel = 0;   
    unsigned char neighborPixel = 0;  
    int bitCount = 0;  
    unsigned int bigger = 0;  

    unsigned int sum =0;  
    unsigned int leftSquareSum = 0;  
    unsigned int rightSquareSum = 0;   

    double *matchLevel = new double[maxDBounds - minDBounds  + 1];  
    double tempMax = 0;  
    int tempIndex = 0;  

    unsigned char* dst;  
    unsigned char* leftSrc  = NULL;  
    unsigned char* rightSrc = NULL;  

    unsigned char leftPixel = 0;  
    unsigned char rightPixel =0;  
    unsigned char subPixel = 0;  
    unsigned char meanLeftPixel  = 0;  
    unsigned char meanRightPixel = 0;  


    for(i = 0 ; i < leftImage.cols;i++){  
      for(j = 0; j< leftImage.cols;j++){
	  /*均值计算 */  
	  for (k = minDBounds;k <= maxDBounds;k++)
	  {
	    sum = 0;
	    leftSquareSum  = 0;
	    rightSquareSum = 0;
	    for (m = i-hWin; m <= i + hWin;m++)
	    {
		for (n = j - hWin; n <= j + hWin;n++)
		{
		  if (m < 0 || m >= imageHeight || n <0 || n >= imageWidth ) 
		  {
		    leftPixel = 0;
		  }else {
		    leftSrc = (unsigned char*)leftImage.data + m*leftImage.cols + n + k;
		    leftPixel = *leftSrc;  
		  }
		  if (m < 0 || m >= imageHeight || n + k <0 || n +k >= imageWidth)
		  {
		    rightPixel = 0;
		  }else
		  {
		    rightSrc = (unsigned char*)rightImage.data + m*rightImage.cols + n;
		    rightPixel = *rightSrc;
		  }
		  sum +=  leftPixel*rightPixel;
		  leftSquareSum  += leftPixel*leftPixel;
		  rightSquareSum += rightPixel*rightPixel;
		}
	    }
	    matchLevel[k] = (double)sum/(sqrt(double(leftSquareSum))*sqrt((double)rightSquareSum));
	  }
	  tempMax = 0;
	  tempIndex = 0;
	  for ( m = 1;m < maxDBounds - minDBounds + 1;m++)  
	  {
	    if (matchLevel[m] > matchLevel[tempIndex])  
	    {
		tempMax = matchLevel[m];  
            tempIndex = m;
	    }
	  }
	  dst = (unsigned char *)NCCImage.data + i*NCCImage.cols + j;  
        *dst = tempIndex*8;
//	  dst = (unsigned char *)MatchLevelImage.data + i*MatchLevelImage.cols + j;
//	  *dst = (unsigned char)(tempMax*255);  
	}
    }

    cout<<endl<<"Over"<<endl;  
   // waitKey(0);
   imwrite("depth.jpg",NCCImage);  
   // imwrite("MatchLevelImage.jpg",MatchLevelImage); 
    return 0;  
} 
