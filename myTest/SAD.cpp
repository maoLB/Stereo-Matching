/*************************************************************************
    > File Name: SAD.cpp
    > Author: ll.pan
    > Mail: ll.pan931204@gmail.com 
    > Created Time: 2017年06月16日 星期五 15时39分16秒
    > Sum of Absolute difference (SAD)
 ************************************************************************/

#include<iostream>   
#include<opencv2/core/core.hpp>   
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
int main(int argc,char** argv)
{  
    if(argc!=3)
	cout<<"Please input:SAD leftImage rightImage"<<endl;
    /*Half of the window size for the census transform*/  
    int hWin = 11;  
    int compareLength = (2*hWin+1)*(2*hWin+1);  

    cout<<"hWin: "<<hWin<<";  "<<"compare length:  "<<compareLength<<endl;    

    Mat leftImage = imread(argv[1]);  
    Mat rightImage = imread(argv[2]);  

    int imageWidth = leftImage.cols;  
    int imageHeight =leftImage.rows;  
    cout<<"imageWidth(cols):"<<imageWidth<<";  "<<"imageHeight(rows):"<<imageHeight<<endl; 

    Mat SADImage,MatchLevelImage;
    SADImage.create(leftImage.rows,leftImage.cols,leftImage.type()); 
    MatchLevelImage.create(leftImage.rows,leftImage.cols,leftImage.type());  

    int minDBounds = 0;  
    int maxDBounds = 31;  

    /*Census Transform */  
    int i,j ,m,n,k;  
    
    int sum = 0;  
    unsigned int *matchLevel = new unsigned int[maxDBounds - minDBounds  + 1];  
    int tempMin = 0;  
    int tempIndex = 0;  

    unsigned char* dst;  
    unsigned char* leftSrc  = NULL;  
    unsigned char* rightSrc = NULL;  

    unsigned char leftPixel = 0;  
    unsigned char rightPixel =0;  
    unsigned char subPixel = 0;  


    for(i = 0 ; i < leftImage.rows;i++){
	for(j = 0; j< leftImage.cols;j++){
	  // k is the disparity layer
	  for (k = minDBounds;k <= maxDBounds;k++)
	  {
	    sum = 0;
	    for (m = i-hWin; m <= i + hWin;m++)
	    { 
		// keep the surrounding pixel located in the image;
		for (n = j - hWin; n <= j + hWin;n++)
		{
		  if (m < 0 || m >= imageHeight || n <0 || n >= imageWidth )
		  {
		    subPixel  = 0;  
		  }
		  else if (n + k >= imageWidth)
		  {
		    subPixel = 0;
		  }
		  else
		  {
	    
		    //unsigned char* row_lptr = leftImage.ptr<unsigned char> (m);
		    //unsigned char* row_rptr = rightImage.ptr<unsigned char> (m);
		    //leftSrc = &row_lptr[n+k];
		   // rightSrc = &row_rptr[n];
		     leftSrc = (unsigned char*)leftImage.data + m*imageWidth + n + k;
		     rightSrc = (unsigned char*)rightImage.data + m*imageWidth + n;
		    leftPixel = *leftSrc;
		    rightPixel = *rightSrc;
		    subPixel =abs(rightPixel -leftPixel);
		  }
		  sum += subPixel;
		}
	    }
	    matchLevel[k] = sum;
	  }

	  tempMin = 0;
	  tempIndex = 0;
	  for ( m = 1;m < (maxDBounds - minDBounds + 1);m++)  
	  {
	    if (matchLevel[m] < matchLevel[tempIndex])
            {
                tempMin = matchLevel[m];
                tempIndex = m;
            }
	  }
	  
/*	  unsigned char* row_ptr1 = SADImage.ptr<unsigned char>(i);
	  unsigned char* data_ptr1 =&row_ptr1[j];
	  *data_ptr1 = tempIndex*8;
	  
	  unsigned char* row_ptr2 = MatchLevelImage.ptr<unsigned char>(i);
	  unsigned char* data_ptr2 =&row_ptr2[j];
	  *data_ptr2 = tempMin;	  
*/	  
	  dst = (unsigned char *)SADImage.ptr<unsigned char>(i) + j;  

	  *dst = tempIndex*8;  
	  dst = (unsigned char *)MatchLevelImage.ptr<unsigned char>(i) + j;
	  *dst = tempMin;

	}
	//waitKey(0);   
    }


    imwrite("Census.jpg",SADImage);  
    imwrite("MatchLevel.jpg",MatchLevelImage);  

    //waitKey(100);
    //destroyAllWindows();  
    //leftImage.release();  
    //rightImage.release();   
    return 0;  
}  

