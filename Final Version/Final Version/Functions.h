//
//  Functions.hpp
//  Function
//
//  Created by Leo on 2016/12/23.
//  Copyright © 2016年 air711. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp



#define TWO_PI 6.2831853071795864769252866

#define cvQueryHistValue_2D(hist,idx0,idx1)\
cvGetReal2D((hist)->bins,(idx0),(idx1))


using namespace std;
using namespace cv;

class Function
{
public:
    
    //灰度化
    static IplImage* change(IplImage* image);
    
    //将Mat转换成IplImage
    static IplImage* TransferM2I(Mat Img);
    
    
    //显示直方图
    static IplImage* cvShowHist(IplImage* src);
  
    
    
    //直方图均衡化
    static IplImage* EqualizeHistColorImage(IplImage *pImage);
    
    
    //添加噪声***************
    
    //1.椒盐噪声
    static Mat PepperSaultNoise (Mat &Image);
    
    
    
    //2.随机噪声
    
    static Mat RandomNoise (Mat &Image);
    
    //3.高斯噪声
    static double generateGaussianNoise();
    
    
    static Mat GaussianNoise(Mat& Image);

    
    // Median blur
    static Mat medianBlur(Mat &image);
    
    // Average value blur
    static Mat averBlur(Mat &image);
    
    // Gaussian blur
    static Mat gaussianBlur(Mat &image);
    
    
    
    
    //超限邻域平均法滤波
    static IplImage* OnBlurSmooth(IplImage* workImg);
    
    
    //超限中值滤波
    static IplImage* OnMedianSmooth(IplImage* workImg);
    
    
    //高斯滤波器滤波
    static IplImage* OnGaussSmooth(IplImage* workImg);
    
    
    
    //边缘提取
    //Roberts
    static IplImage* Roberts(IplImage * image);

    
    //Sobel,Prewitt,Laplace
    static IplImage* Sobel_Prewitt_Laplace(IplImage * image,int menu);

    
    //Hough圆形检测
    static IplImage* Hough(IplImage *image);
    
    
    
    //最大类间方差法
    static Mat afterOTSU1(Mat &image);

    
    static Mat afterOTSU2(Mat &image);

    
    //HCM
    static Mat clusterColorImageByKmeans(Mat image, Mat labels, int clusterCounts);
    
    static Mat HCM(Mat &image, int i);
    
    //开
    static IplImage* open(IplImage* Image);
    
    
    //闭
    static IplImage* close(IplImage* Image);
    
    
    //膨胀
    static Mat Dilation( Mat image, int dilation_elem ,int dilation_size );
    
    
    //腐蚀
    static Mat Erosion( Mat Image,  int erosion_elem ,int erosion_size);
   
    //毛玻璃
    static Mat Glass(Mat& Image);
    
    //浮雕
    static Mat Relief(Mat& Image);
    
    //雕刻
    static Mat Grave(Mat& Image);
    
    //素描
    static Mat Skech(Mat& Image);
    
    //怀旧
    static Mat Nostalgia(Mat& Image);
    
    //横向模糊
    static Mat Wind(Mat& Image);
    
};





#endif /* Functions_hpp */
