//
//  Function.cpp
//  Function
//
//  Created by Leo on 2016/12/23.
//  Copyright © 2016年 air711. All rights reserved.
//





#include "Functions.h"

#define cvQueryHistValue_2D(hist,idx0,idx1)\
cvGetReal2D((hist)->bins,(idx0),(idx1))



using namespace std;
using namespace cv;


//转化灰度图
IplImage* Function::change(IplImage* image)
{
    IplImage * img = image;
    IplImage* img1 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);//创建目标图像
    cvCvtColor(img,img1,CV_BGR2GRAY);//cvCvtColor(src,des,CV_BGR2GRAY)
    IplImage* img2 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
    cvCvtColor(img1, img2, CV_GRAY2BGR);
    return img2;
}



//显示直方图
IplImage* Function::cvShowHist(IplImage* src)
{
    IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
    IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* planes[] = { h_plane, s_plane };
        
    /** H 分量划分为16个等级，S分量划分为8个等级 */
    int h_bins = 16, s_bins = 8;
    int hist_size[] = {h_bins, s_bins};
    
    /** H 分量的变化范围 */
    float h_ranges[] = { 0, 180 };
    
    /** S 分量的变化范围*/
    float s_ranges[] = { 0, 255 };
    float* ranges[] = { h_ranges, s_ranges };
    
    /** 输入图像转换到HSV颜色空间 */
    cvCvtColor( src, hsv, CV_BGR2HSV );
    cvSplit( hsv, h_plane, s_plane, v_plane, 0 );
    
    /** 创建直方图，二维, 每个维度上均分 */
    CvHistogram * hist = cvCreateHist( 2, hist_size, CV_HIST_ARRAY, ranges, 1 );
    /** 根据H,S两个平面数据统计直方图 */
    cvCalcHist( planes, hist, 0, 0 );
    
    /** 获取直方图统计的最大值，用于动态显示直方图 */
    float max_value;
    cvGetMinMaxHistValue( hist, 0, &max_value, 0, 0 );
    
    
    /** 设置直方图显示图像 */
    int height = 240;
    int width = (h_bins*s_bins*6);
    IplImage* hist_img = cvCreateImage( cvSize(width,height), 8, 3 );
    cvZero( hist_img );
    
    /** 用来进行HSV到RGB颜色转换的临时单位图像 */
    IplImage * hsv_color = cvCreateImage(cvSize(1,1),8,3);
    IplImage * rgb_color = cvCreateImage(cvSize(1,1),8,3);
    int bin_w = width / (h_bins * s_bins);
    for(int h = 0; h < h_bins; h++)
    {
        for(int s = 0; s < s_bins; s++)
        {
            int i = h*s_bins + s;
            /** 获得直方图中的统计次数，计算显示在图像中的高度 */
            float bin_val = cvQueryHistValue_2D( hist, h, s );
            int intensity = cvRound(bin_val*height/max_value);
            
            /** 获得当前直方图代表的颜色，转换成RGB用于绘制 */
            cvSet2D(hsv_color,0,0,cvScalar(h*180.f / h_bins,s*255.f/s_bins,255,0));
            cvCvtColor(hsv_color,rgb_color,CV_HSV2BGR);
            CvScalar color = cvGet2D(rgb_color,0,0);
            
            cvRectangle( hist_img, cvPoint(i*bin_w,height),
                        cvPoint((i+1)*bin_w,height - intensity),
                        color, -1, 8, 0 );
        }
    }
        
    
    return hist_img;
    
}

//直方图均衡化
IplImage* Function::EqualizeHistColorImage(IplImage *pImage)
{
    IplImage *pEquaImage = cvCreateImage(cvGetSize(pImage), pImage->depth, 3);
        
    // 原图像分成各通道后再均衡化,最后合并即彩色图像的直方图均衡化
    const int MAX_CHANNEL = 4;
    IplImage *pImageChannel[MAX_CHANNEL] = {NULL};
    
    int i;
    for (i = 0; i < pImage->nChannels; i++)
        pImageChannel[i] = cvCreateImage(cvGetSize(pImage), pImage->depth, 1);
    
    cvSplit(pImage, pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3]);
    
    for (i = 0; i < pImage->nChannels; i++)
        cvEqualizeHist(pImageChannel[i], pImageChannel[i]);
        
    cvMerge(pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3], pEquaImage);
    
    for (i = 0; i < pImage->nChannels; i++)
        cvReleaseImage(&pImageChannel[i]);
    
    return pEquaImage;
}
    
    
    
//添加噪声***************
    
//1.椒盐噪声
 Mat Function::PepperSaultNoise (Mat &Image) {
        
    Mat img = Image;
    for(int k=0; k<4000; k++)
    {
        int i = rand()%img.cols;
        int j = rand()%img.rows;
        
        if(img.channels() == 1)
        {
            img.at<uchar>(j,i) = 255;
        }
        else if(img.channels() == 3)
        {
            img.at<cv::Vec3b>(j,i)[0] = 255;
            img.at<cv::Vec3b>(j,i)[1] = 255;
            img.at<cv::Vec3b>(j,i)[2] = 255;
        }
    }
    
    for(int k=0; k<4000; k++)
    {
        int i = rand()%img.cols;
        int j = rand()%img.rows;
        
        if(img.channels() == 1)
        {
            img.at<uchar>(j,i) = 0;
        }
        else if(img.channels() == 3)
        {
            img.at<cv::Vec3b>(j,i)[0] = 0;
            img.at<cv::Vec3b>(j,i)[1] = 0;
            img.at<cv::Vec3b>(j,i)[2] = 0;
        }
    }
    
    
    return img;
}
    
    
//2.随机噪声

Mat Function::RandomNoise (Mat &Image) {
    
    Mat afterNoise = Image.clone();
    int n = rand() % 1000 + 2000;
    int a, b, c;
    int i, j;
    for (int k = 0; k < n - 1500; k++)
    {
        a = rand() % 30;
        b = rand() % 30;
        c = rand() % 30;
        i = rand() % afterNoise.cols;
        j = rand() % afterNoise.rows;
        if (afterNoise.channels() == 1)
            afterNoise.at<uchar>(j, i) = 255;
        else if (afterNoise.channels() == 3)
        {
            afterNoise.at<cv::Vec3b>(j, i)[0] = 255 - a;
            afterNoise.at<cv::Vec3b>(j, i)[1] = 255 - b;
            afterNoise.at<cv::Vec3b>(j, i)[2] = 255 - c;
        }
    }
    for (int k = 0; k < n; k++)
    {
        a = rand() % 30;
        b = rand() % 30;
        c = rand() % 30;
        i = rand() % afterNoise.cols;
        j = rand() % afterNoise.rows;
        if (afterNoise.channels() == 1)
            afterNoise.at<uchar>(j, i) = 0;
        else if (Image.channels() == 3)
        {
            afterNoise.at<cv::Vec3b>(j, i)[0] = a;
            afterNoise.at<cv::Vec3b>(j, i)[1] = b;
            afterNoise.at<cv::Vec3b>(j, i)[2] = c;
        }
    }
    return afterNoise;
}


//3.高斯噪声
double Function::generateGaussianNoise()
{
    static bool hasSpare = false;
    static double rand1, rand2;
    
    if(hasSpare)
    {
        hasSpare = false;
        return sqrt(rand1) * sin(rand2);
    }
    
    hasSpare = true;
    
    rand1 = rand() / ((double) RAND_MAX);
    if(rand1 < 1e-100) rand1 = 1e-100;
    rand1 = -2 * log(rand1);
    rand2 = (rand() / ((double) RAND_MAX)) * TWO_PI;
    
    return sqrt(rand1) * cos(rand2);
}
    
Mat Function::GaussianNoise(Mat& Image)
{
    // accept only char type matrices
    Mat Img = Image;
    CV_Assert(Img.depth() != sizeof(uchar));
    
    int channels = Img.channels();
    
    int nRows = Img.rows;
    int nCols = Img.cols * channels;
    
    if(Img.isContinuous()){
        nCols *= nRows;
        nRows = 1;
    }
    
    int i,j;
    uchar* p;
    for(i = 0; i < nRows; ++i){
        p = Img.ptr<uchar>(i);
        for(j = 0; j < nCols; ++j){
            double val = p[j] + generateGaussianNoise() * 128;
            if(val < 0)
                val = 0;
            if(val > 255)
                val = 255;
            
            p[j] = (uchar)val;
            
        }
    }
    
    return Img;
    
}


// Median blur
Mat Function::medianBlur(Mat &image)
{
    Mat afterBlur = image;
    Mat dst = image;
    cvSmooth(&image, &dst, CV_MEDIAN, 5, 5);
    
    return dst;
}

// Average value blur
Mat Function::averBlur(Mat &image)
{
    Mat afterBlur = image;
    Mat dst;
    cvSmooth(&image, &dst, CV_BLUR_NO_SCALE, 5, 5);
    
    return dst;
}

// Gaussian blur
Mat Function::gaussianBlur(Mat &image)
{
    Mat afterBlur = image;
    Mat *dst;
    cvSmooth(&afterBlur, dst, CV_GAUSSIAN, 5, 5);
    
    return *dst;
}



//超限邻域平均法滤波
IplImage* Function::OnBlurSmooth(IplImage* workImg)
{
    IplImage* in = cvCreateImage(cvGetSize(workImg), workImg->depth, workImg->nChannels);
    
    in = cvCloneImage(workImg);
    IplImage* out = cvCreateImage(cvGetSize(workImg),workImg->depth,workImg->nChannels);
    cvSmooth(in,out,CV_BLUR,3,3);  //  简单平均
    return out;
    
}
    
//超限中值滤波
IplImage* Function::OnMedianSmooth(IplImage* workImg)
{
    IplImage* in = workImg;
    IplImage* out = cvCreateImage(cvGetSize(in),
                                      IPL_DEPTH_8U,workImg->nChannels);
    cvSmooth(in,out,CV_MEDIAN,3,3);  //  中值滤波
    return out;
    
}
    
    
//高斯滤波器滤波
IplImage* Function::OnGaussSmooth(IplImage* workImg)
{
    IplImage* in  = workImg;
    IplImage* out = cvCreateImage(cvGetSize(in),IPL_DEPTH_8U,workImg->nChannels);//  建立辅助位图
    cvSmooth(in,out,CV_GAUSSIAN,3,3);  //  Gauss 平滑
    return out;
}

    
    
//边缘提取
//Roberts
IplImage* Function::Roberts(IplImage * image)
{
    int origin[4],target,i,j;
    double color_num = 256;
        
    IplImage * pTest = image;
        
    color_num = pow(2.0,(int)pTest->depth);
        
    IplImage * dst = cvCreateImage(cvGetSize(pTest), pTest->depth, 3);
    
        
    for (i = 0 ; i < 3*(pTest->width - 1); i++)
    {
        for (j = 0 ; j < pTest->height - 1; j++)
        {
            origin[0] = ((uchar*)(pTest->imageData + pTest->widthStep*j))[i];
            origin[1] = ((uchar*)(pTest->imageData + pTest->widthStep*(j+1)))[i+1];
            origin[2] = ((uchar*)(pTest->imageData + pTest->widthStep*j))[i+1];
            origin[3] = ((uchar*)(pTest->imageData + pTest->widthStep*(j+1)))[i];
            target = abs(origin[0] - origin[1]) + abs(origin[2] - origin[3]);
            if(target < 0)
                target = 0;
            if(target >= color_num)
                target = (int)color_num - 1;
            ((uchar*)(dst->imageData + dst->widthStep*j))[i] = target;
        }
    }
    for(i = 0;i < 3*(pTest->width - 1);i++)
        ((uchar*)(dst->imageData + dst->widthStep*(dst->height-1)))[i] = ((uchar*)(pTest->imageData + pTest->widthStep*(pTest->height-1)))[i];
    for(j = 0;j < pTest->height;j++)
        ((uchar*)(dst->imageData + dst->widthStep*j))[dst->width-1] = ((uchar*)(pTest->imageData + pTest->widthStep*j))[pTest->width-1];
        
    IplImage* d = dst;
        
    //cvReleaseImage(&pTest);
    //cvReleaseImage(&dst);
        
    return d;
}
    
//Sobel,Prewitt,Laplace
IplImage* Function::Sobel_Prewitt_Laplace(IplImage * image,int menu)
{
    int origin[9],target = 0,i,j;
    double color_num = 256;
    
    IplImage * pTest = image;
    
    color_num = pow(2.0,(int)pTest->depth);
    
    IplImage * dst = cvCreateImage(cvGetSize(pTest), pTest->depth, 3);
    
    for (i = 1 ; i < 3*(pTest->width - 1); i++)
    {
        for (j = 1 ; j < pTest->height - 1; j++)
        {
            origin[0] = ((uchar*)(pTest->imageData + pTest->widthStep*(j-1)))[i-1];
            origin[1] = ((uchar*)(pTest->imageData + pTest->widthStep*(j)))[i-1];
            origin[2] = ((uchar*)(pTest->imageData + pTest->widthStep*(j+1)))[i-1];
            origin[3] = ((uchar*)(pTest->imageData + pTest->widthStep*(j-1)))[i];
            origin[4] = ((uchar*)(pTest->imageData + pTest->widthStep*(j)))[i];
            origin[5] = ((uchar*)(pTest->imageData + pTest->widthStep*(j+1)))[i];
            origin[6] = ((uchar*)(pTest->imageData + pTest->widthStep*(j-1)))[i+1];
            origin[7] = ((uchar*)(pTest->imageData + pTest->widthStep*(j)))[i+1];
            origin[8] = ((uchar*)(pTest->imageData + pTest->widthStep*(j+1)))[i+1];
                
            switch(menu)
            {
                    //Sobel
                case 2:target = abs(origin[6] + 2*origin[7] + origin[8] - origin[0] - 2*origin[1] - origin[2]) \
                    + abs(origin[2] + 2*origin[5] + origin[8] - origin[0] - 2*origin[3] - origin[6]);break;
                    //Prewitt
                case 3:	target = abs(origin[6] + origin[7] + origin[8] - origin[0] - origin[1] - origin[2]) \
                    + abs(origin[2] + origin[5] + origin[8] - origin[0] - origin[3] - origin[6]);break;
                    //Lapalce
                case 4:	target = 5 * origin[4] - (origin[1] + origin[3] + origin[5] + origin[7]);
                    						//target = 9 * origin[4] - (origin[0] + origin[1] + origin[2] + origin[3] + origin[5] + origin[6] +origin[7] + origin[8]);
                    break;
                default:break;
            }
            if(target < 0)
                target = 0;
            if(target >= color_num)
                target = (int)color_num - 1;
            ((uchar*)(dst->imageData + dst->widthStep*j))[i] = target;
        }
    }
        
    for(i = 0;i < 3*(pTest->width - 1);i++)
    {
        ((uchar*)(dst->imageData + dst->widthStep*0))[i] = ((uchar*)(pTest->imageData + pTest->widthStep*0))[i];
        ((uchar*)(dst->imageData + dst->widthStep*(dst->height-1)))[i] = ((uchar*)(pTest->imageData + pTest->widthStep*(pTest->height-1)))[i];
    }
    for(j = 0;j < pTest->height;j++)
    {
        ((uchar*)(dst->imageData + dst->widthStep*j))[0] = ((uchar*)(pTest->imageData + pTest->widthStep*j))[0];
        ((uchar*)(dst->imageData + dst->widthStep*j))[dst->width-1] = ((uchar*)(pTest->imageData + pTest->widthStep*j))[pTest->width-1];
    }
        
        
    //cvReleaseImage(&pTest);
    
    return dst;
}
    
    
    
    
    
//Hough圆形检测
IplImage* Function::Hough(IplImage *image)
{
        
    IplImage * img = image;
    IplImage* src = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);//创建目标图像
    cvCvtColor(img,src,CV_BGR2GRAY);
    
    cvSmooth(src, src, CV_GAUSSIAN, 5, 5);      //降噪,不然误检测太高
    IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, 3);
    cvCvtColor(src, dst, CV_GRAY2BGR);
    
    
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* results = cvHoughCircles(
                                    //cvHoughCircles函数需要估计每一个像素梯度的方向,
                                    //因此会在内部自动调用cvSobel,而二值边缘图像的处理是比较难的
                                    src,
                                    storage,
                                    CV_HOUGH_GRADIENT,
                                    1,  //累加器图像的分辨率
                                    10,
                                    100,
                                    30,
                                    1,30);  //改变着两个参数检测不同大小的圆
        
    for( int i = 0; i < results->total; i++ )
    {
        float* p = ( float* )cvGetSeqElem( results, i );
        //霍夫圆变换
        CvPoint pt = cvPoint( cvRound( p[0] ), cvRound( p[1] ) );
        cvCircle(
                    img,
                    pt,  //确定圆心
                    cvRound( p[2] ),  //确定半径
                    CV_RGB( 255, 0, 0 )
                    );  //画圆函数
    }
        
        
    //cvReleaseMemStorage(&storage);
    //cvReleaseImage(&src);
    
    return img;
        
}
    
    
    
//最大类间方差法
Mat Function::afterOTSU1(Mat &image)
{
    Mat gray;
    cvtColor(image, gray, CV_BGR2GRAY);
    Mat result;
    Mat out1 = image.clone(), out2 = image.clone();
    threshold(gray, result, 0, 255, CV_THRESH_OTSU);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if (result.at<uchar>(i, j) == 255)
            {
                out1.at<Vec3b>(i, j)[0] = 255;
                out1.at<Vec3b>(i, j)[1] = 255;
                out1.at<Vec3b>(i, j)[2] = 255;
            }
            else
            {
                out2.at<Vec3b>(i, j)[0] = 255;
                out2.at<Vec3b>(i, j)[1] = 255;
                out2.at<Vec3b>(i, j)[2] = 255;
            }
        }
    }
    //imshow("Binary Image", result);
    //imshow("Segmentation Class 1", out1);
    //imshow("Segmentation Class 2", out2);
    return out1;
}

Mat Function::afterOTSU2(Mat &image)
{
    Mat gray;
    cvtColor(image, gray, CV_BGR2GRAY);
    Mat result;
    Mat out1 = image.clone(), out2 = image.clone();
    threshold(gray, result, 0, 255, CV_THRESH_OTSU);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if (result.at<uchar>(i, j) == 255)
            {
                out1.at<Vec3b>(i, j)[0] = 255;
                out1.at<Vec3b>(i, j)[1] = 255;
                out1.at<Vec3b>(i, j)[2] = 255;
            }
            else
            {
                out2.at<Vec3b>(i, j)[0] = 255;
                out2.at<Vec3b>(i, j)[1] = 255;
                out2.at<Vec3b>(i, j)[2] = 255;
            }
        }
    }
    //imshow("Binary Image", result);
    //imshow("Segmentation Class 1", out1);
    //imshow("Segmentation Class 2", out2);
    return out2;
}
    
    
    
    
//HCM
Scalar colorTab[] =
{
    Scalar(0, 0, 255),
    Scalar(0, 255, 0),
    Scalar(255, 100, 100),
    Scalar(255, 0, 255),
    Scalar(0, 255, 255),
    Scalar(255, 0, 0),
    Scalar(255, 255, 0),
    Scalar(255, 0, 100),
    Scalar(100, 100, 100),
    Scalar(50, 125, 125)
};


Mat Function::clusterColorImageByKmeans(Mat image, Mat labels, int clusterCounts)
{
    assert(image.channels() != 1);
        
    int rows = image.rows;
    int cols = image.cols;
    int channels = image.channels();
        
        
    Mat clusteredMat(rows, cols, CV_8UC3);
    clusteredMat.setTo(Scalar::all(0));
        
    Mat pixels(rows*cols, 1, CV_32FC3);
    pixels.setTo(Scalar::all(0));
        
    for (int i = 0; i < rows; ++i)
    {
        const uchar *idata = image.ptr<uchar>(i);
        float *pdata = pixels.ptr<float>(0);
            
        for (int j = 0; j < cols*channels; ++j)
        {
            pdata[i*cols*channels + j] = saturate_cast<float>(idata[j]);
        }
    }
        
    kmeans(pixels, clusterCounts, labels, TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 0), 5, KMEANS_PP_CENTERS);
        
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols*channels; j += channels)
        {
            circle(clusteredMat, Point(j / channels, i), 1, colorTab[labels.at<int>(i*cols + (j / channels))]);
        }
    }
        
    return clusteredMat;
}

Mat Function::HCM(Mat &image, int i)
{
    Mat testImage = image.clone();
    
    Mat label;
    
    Mat colorResults = clusterColorImageByKmeans(testImage, label, i);

    return colorResults;
}
    
    
    
//开
IplImage* Function::open(IplImage* Image)
{
    // Load an image
    IplImage * src = Image;
    
   // IplImage * temp = cvCreateImage(cvGetSize(src), 8,3);
    //IplImage * img=cvCreateImage(cvGetSize(src), 8, 3);
    //cvCopy(src,temp);
    //cvCopy(src, img);
    IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    IplImage* temp;
    //开运算
    cvMorphologyEx(
                    src,
                    dst,
                    temp,
                    NULL, //default 3*3
                    CV_MOP_OPEN,
                    1);
    //cvReleaseImage(&src);
    //cvReleaseImage(&temp);
    return dst;
        
}
    
    
//闭
IplImage* Function::close(IplImage* Image)
{
    // Load an image
    IplImage * src = Image;
    
    IplImage * temp = cvCreateImage(cvGetSize(src), 8,3);
    IplImage * img=cvCreateImage(cvGetSize(src), 8, 3);
    cvCopy(src,temp);
    cvCopy(src, img);
    //开运算
    cvMorphologyEx(
                    src,
                    img,
                    temp,
                    NULL, //default 3*3
                    CV_MOP_CLOSE,
                    1);
    
    //cvReleaseImage(&src);
    //cvReleaseImage(&temp);
    return img;
        
}
    
    
    
//膨胀
Mat Function::Dilation(Mat Image, int dilation_elem ,int dilation_size)
{
    Mat src, dilation_dst;
    src = Image;
    int dilation_type;
    if ( dilation_elem == 0 )
    {
        dilation_type = MORPH_RECT;
    }
    else if ( dilation_elem == 1)
    {
        dilation_type = MORPH_CROSS;
    }
    else if ( dilation_elem == 2 )
    {
        dilation_type = MORPH_ELLIPSE;
    }
    
    Mat element = getStructuringElement( dilation_type,
                                        Size( 2*dilation_size + 1, 2*dilation_size + 1 ),
                                        Point( dilation_size,  dilation_size));
        
    // apply the dilation operation
    dilate( src, dilation_dst, element );
    
    return dilation_dst;
}
    
    
//腐蚀
Mat Function::Erosion(  Mat Image, int erosion_elem ,int erosion_size )
{
    Mat src, erosion_dst;
    src = Image;
    int erosion_type;
    if ( erosion_elem == 0 )
    {
        erosion_type = MORPH_RECT;
    }
    else if ( erosion_elem == 1 )
    {
        erosion_type = MORPH_CROSS;
    }
    else if ( erosion_elem == 2 )
    {
        erosion_type = MORPH_ELLIPSE;
    }
    
    Mat  element = getStructuringElement( erosion_type,
                                            Size( 2*erosion_size + 1 , 2*erosion_size + 1 ),
                                            Point( erosion_size, erosion_size ));
    erode ( src, erosion_dst, element );
        
    return erosion_dst;
}


//毛玻璃
Mat Function::Glass(Mat& Image)
{
    Mat src = Image;
    int width=src.cols;
    int heigh=src.rows;
    RNG rng;
    Mat img(src.size(),CV_8UC3);
    for (int y=1; y<heigh-1; y++)
    {
        uchar* P0  = src.ptr<uchar>(y);
        uchar* P1  = img.ptr<uchar>(y);
        for (int x=1; x<width-1; x++)
        {
            int tmp=rng.uniform(0,9);
            P1[3*x]=src.at<uchar>(y-1+tmp/3,3*(x-1+tmp%3));
            P1[3*x+1]=src.at<uchar>(y-1+tmp/3,3*(x-1+tmp%3)+1);
            P1[3*x+2]=src.at<uchar>(y-1+tmp/3,3*(x-1+tmp%3)+2);
        }
        
    }
    return img;
}

//浮雕
Mat Function::Relief(Mat& Image)
{
    Mat src = Image;
    Mat img0(src.size(),CV_8UC3);
    Mat img1(src.size(),CV_8UC3);
    for (int y=1; y<src.rows-1; y++)
    {
        uchar *p0 = src.ptr<uchar>(y);
        uchar *p1 = src.ptr<uchar>(y+1);
        
        uchar *q0 = img0.ptr<uchar>(y);
        uchar *q1 = img1.ptr<uchar>(y);
        for (int x=1; x<src.cols-1; x++)
        {
            for (int i=0; i<3; i++)
            {
                int tmp0 = p1[3*(x+1)+i]-p0[3*(x-1)+i]+128;//浮雕
                if (tmp0<0)
                    q0[3*x+i]=0;
                else if(tmp0>255)
                    q0[3*x+i]=255;
                else
                    q0[3*x+i]=tmp0;
                
                int tmp1 = p0[3*(x-1)+i]-p1[3*(x+1)+i]+128;//雕刻
                if (tmp1<0)
                    q1[3*x+i]=0;
                else if(tmp1>255)
                    q1[3*x+i]=255;
                else
                    q1[3*x+i]=tmp1;
            }
        }
    }
    return img0;
}


//雕刻
Mat Function::Grave(Mat& Image)
{
    Mat src = Image;
    Mat img0(src.size(),CV_8UC3);
    Mat img1(src.size(),CV_8UC3);
    for (int y=1; y<src.rows-1; y++)
    {
        uchar *p0 = src.ptr<uchar>(y);
        uchar *p1 = src.ptr<uchar>(y+1);
        
        uchar *q0 = img0.ptr<uchar>(y);
        uchar *q1 = img1.ptr<uchar>(y);
        for (int x=1; x<src.cols-1; x++)
        {
            for (int i=0; i<3; i++)
            {
                int tmp0 = p1[3*(x+1)+i]-p0[3*(x-1)+i]+128;//浮雕
                if (tmp0<0)
                    q0[3*x+i]=0;
                else if(tmp0>255)
                    q0[3*x+i]=255;
                else
                    q0[3*x+i]=tmp0;
                
                int tmp1 = p0[3*(x-1)+i]-p1[3*(x+1)+i]+128;//雕刻
                if (tmp1<0)
                    q1[3*x+i]=0;
                else if(tmp1>255)
                    q1[3*x+i]=255;
                else
                    q1[3*x+i]=tmp1;
            }
        }
    }
    return img1;
}


//素描
Mat Function::Skech(Mat& Image)
{
    Mat src = Image;
    int width=src.cols;
    int heigh=src.rows;
    Mat gray0,gray1;
    //去色
    cvtColor(src,gray0,CV_BGR2GRAY);
    //反色
    addWeighted(gray0,-1,NULL,0,255,gray1);
    //高斯模糊,高斯核的Size与最后的效果有关
    GaussianBlur(gray1,gray1,Size(11,11),0);
    
    //融合：颜色减淡
    Mat img(gray1.size(),CV_8UC1);
    for (int y=0; y<heigh; y++)
    {
        
        uchar* P0  = gray0.ptr<uchar>(y);
        uchar* P1  = gray1.ptr<uchar>(y);
        uchar* P  = img.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            int tmp0=P0[x];
            int tmp1=P1[x];
            P[x] =(uchar) min((tmp0+(tmp0*tmp1)/(256-tmp1)),255);
        }
        
    }
    return img;
}


//怀旧
Mat Function::Nostalgia(Mat& Image)
{
    Mat src = Image;
    int width=src.cols;
    int heigh=src.rows;
    RNG rng;
    Mat img(src.size(),CV_8UC3);
    for (int y=0; y<heigh; y++)
    {
        uchar* P0  = src.ptr<uchar>(y);
        uchar* P1  = img.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            float B=P0[3*x];
            float G=P0[3*x+1];
            float R=P0[3*x+2];
            float newB=0.272*R+0.534*G+0.131*B;
            float newG=0.349*R+0.686*G+0.168*B;
            float newR=0.393*R+0.769*G+0.189*B;
            if(newB<0)newB=0;
            if(newB>255)newB=255;
            if(newG<0)newG=0;
            if(newG>255)newG=255;
            if(newR<0)newR=0;
            if(newR>255)newR=255;
            P1[3*x] = (uchar)newB;
            P1[3*x+1] = (uchar)newG;
            P1[3*x+2] = (uchar)newR;
        }
        
    }
    return img;
}

//横向模糊
Mat Function::Wind(Mat& Image)
{
    Mat src = Image;
    int num = 20;
    int num1 = 20;
    Mat src1u[3];
    split(src,src1u);
    
    int width=src.cols;
    int heigh=src.rows;
    Mat img;
    src.copyTo(img);
    
    Point center(width/2,heigh/2);
    
    RNG rng;
    
    for (int y=0; y<heigh; y++)
    {
        
        uchar *imgP  = img.ptr<uchar>(y);
        
        //      for (int x=0; x<width; x++)
        {
            
            for (int i=0;i<num;i++)      //  num：风线密度
            {
                int newX=rng.uniform(i*width/num,(i+1)*width/num);
                int newY = y;
                
                if(newX<0)newX=0;
                if(newX>width-1)newX=width-1;
                
                uchar tmp0 = src1u[0].at<uchar>(newY,newX);
                uchar tmp1 = src1u[1].at<uchar>(newY,newX);
                uchar tmp2 = src1u[2].at<uchar>(newY,newX);
                
                for (int j=0; j<num1; j++)   //num1：风线长度
                {
                    int tmpX=newX-j;//减：风向左；加：风向右
                    
                    if(tmpX<0)tmpX=0;
                    if(tmpX>width-1)tmpX=width-1;
                    
                    imgP[tmpX*3]=tmp0;
                    imgP[tmpX*3+1]=tmp1;
                    imgP[tmpX*3+2]=tmp2;
                }  
            }  
            
        }  
        
    }
    return img;
}

