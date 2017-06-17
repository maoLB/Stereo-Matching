/*************************************************************************
    > File Name: DP.cpp
    > Author: ll.pan
    > Mail: ll.pan931204@gmail.com 
    > Created Time: 2017?06?17? ??? 12?31?00?
 ************************************************************************/

#include <cstdio>   
#include <cstring>   
#include <iostream>   
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>   

using namespace std; 
using namespace cv;
const int Width =  1024;  
const int Height = 1024;  
int Ddynamic[Width][Width];  

int main(int argc,char** argv)  
{    
    /*Half of the window size for the census transform*/  
    int hWin = 11;  
    int compareLength = (2*hWin+1)*(2*hWin+1);  

    cout<<"hWin: "<<hWin<<";  "<<"compare length:  "<<compareLength<<endl;    
    cout<<"belief propagation test"<<endl;  

    Mat leftImage = imread(argv[1],0);  
    Mat rightImage = imread(argv[2],0);

    int imageWidth = leftImage.cols;  
    int imageHeight =leftImage.rows;  

    Mat DPImage;
    DPImage.create(leftImage.rows,leftImage.cols,leftImage.type());  
    Mat MatchLevelImage;
    MatchLevelImage.create(leftImage.rows,leftImage.cols,leftImage.type());  

    unsigned char * pPixel = NULL;  
    unsigned char  pixel;  
    for (int i = 0; i< imageHeight;i++)  
    {  
        for (int j =0; j < imageWidth;j++ )  
        {  
            pPixel = (unsigned char *)DPImage.data + i*DPImage.cols + j;  
            *pPixel = 0;  
        }  
    }  

    int minDBounds = 0;  
    int maxDBounds = 31;  

    imshow("Left",leftImage);  
    imshow("Right",rightImage);  

    int minD = 0;  
    int maxD = 31;  
    //????????????????????????????   
    int max12Diff = 10;  

    for (int i = 0;i < imageWidth;i++)  
    {  
        Ddynamic[0][i] = 0;  
        Ddynamic[i][0] = 0;  
    }  

    unsigned char * pLeftPixel  = NULL;  
    unsigned char * pRightPixel = NULL;  
    unsigned char leftPixel = 0;  
    unsigned char rightPixel =0;  
    int m,n,l;  

    for (int i = 0 ; i < imageHeight;i++)  
    {  
        for (int j = 0; j<imageWidth;j++)  
        {  
            for (int k = j + minD; k <= j + maxD;k++)  
            {  
                if (k <0 || k >= imageWidth)  
                {
                   Ddynamic[j + 1][k + 1] = 0;
                }else {  
                    pLeftPixel = (unsigned char*)leftImage.data + i*leftImage.cols + k;  
                    pRightPixel= (unsigned char*)rightImage.data+i*rightImage.cols + j;  
                    leftPixel  = *pLeftPixel;  
                    rightPixel = *pRightPixel;  

                    if (abs(leftPixel - rightPixel) <= max12Diff)  
                    {  
                        Ddynamic[j + 1][k + 1] = Ddynamic[j][k] +1;   
                    }else if (Ddynamic[j][k+1] > Ddynamic[j+1][k])  
                    {  
                        Ddynamic[j + 1][k + 1] = Ddynamic[j][k+1];  
                    }else{  
                        Ddynamic[j+1][k+1] = Ddynamic[j+1][k];  
                    }  
                }  
            }  
        }  
        // Reverse search to find the best path
         m = imageWidth;  
         n = imageWidth;  
         l = Ddynamic[imageWidth][imageWidth];  
        while( l>0 )  
        {  
            if (Ddynamic[m][n] == Ddynamic[m-1][n])    
                m--;  
            else if (Ddynamic[m][n] == Ddynamic[m][n-1])    
                n--;  
            else  
            {   
                //s[--l]=a[i-1];   
                pPixel = (unsigned char *)DPImage.data + i*DPImage.cols + m;  
                *pPixel = (n-m)*8;  
                l--;  
                m--;   
                n--;  
            }  
        }  
}
    imwrite("depth.jpg",DPImage);  
   // waitKey(0);  
    return 0;  
} 

