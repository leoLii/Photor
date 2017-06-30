//
//  Bridge.m
//  Final Version
//
//  Created by Leo on 2016/12/26.
//  Copyright © 2016年 air711. All rights reserved.
//


#import "Bridge.h"
#import "Functions.h"
#import "Transfer.h"

@implementation OC

//灰度化
-(UIImage* )change:(UIImage* )image
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::change(Img);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}


//显示直方图*IplImage
-(UIImage* )cvShowHist:(UIImage* )image
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::cvShowHist(Img);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}



//直方图均衡化*IplImage
-(UIImage* )EqualizeHistColorImage:(UIImage* )image
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::EqualizeHistColorImage(Img);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}


//添加噪声***************

//1.椒盐噪声*Mat
-(UIImage* )PepperSaultNoise:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::PepperSaultNoise(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
}



//2.随机噪声
-(UIImage* )RandomNoise:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::RandomNoise(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
}



//3.高斯噪声*Mat
-(UIImage* )GaussianNoise:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::GaussianNoise(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
}



//超限邻域平均法滤波*IplImage
-(UIImage* )OnBlurSmooth:(UIImage* )image
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::OnBlurSmooth(Img);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}


//超限中值滤波*IplImage
-(UIImage* )OnMedianSmooth:(UIImage* )image
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::OnMedianSmooth(Img);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}


//高斯滤波器滤波*IplImage
-(UIImage* )OnGaussSmooth:(UIImage* )image
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::OnGaussSmooth(Img);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}



//边缘提取
//Roberts*IplImage
-(UIImage* )Roberts:(UIImage* )image
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::Roberts(Img);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}


//Sobel,Prewitt,Laplace*IplImage
-(UIImage* )Sobel_Prewitt_Laplace:(UIImage* )image Menu:(int) menu
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::Sobel_Prewitt_Laplace(Img, menu);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}


//Hough圆形检测*IplImage
-(UIImage* )Hough:(UIImage* )image
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::Hough(Img);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}



//最大类间方差法*Mat
-(UIImage* ) afterOTSU1:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::afterOTSU1(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;

}


-(UIImage* ) afterOTSU2:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::afterOTSU2(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
}


//HCM*Mat
-(UIImage* ) HCM:(UIImage* )image Colors:(int)colors
{
    Mat Img = [image CVMat3];
    Mat result = Function::HCM(Img, colors);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
}

//开*IplImage
-(UIImage* ) open:(UIImage* )image
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::open(Img);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}


//闭*IplImage
-(UIImage* ) close:(UIImage* )image
{
    IplImage* Img = [image CreateIplImageFromUIImage:image];
    IplImage* result = Function::close(Img);
    UIImage* r = [image UIImageFromIplImage:result];
    return r;
}


//膨胀*Mat
-(UIImage* ) Dilation:(UIImage* )image Dilation_elem:(int)dilation_elem Dilation_size:(int)dilation_size
{
    Mat Img = [image CVMat3];
    Mat result = Function::Dilation(Img, dilation_elem, dilation_size);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
}


//腐蚀*Mat
-(UIImage* ) Erosion:(UIImage* )image Erosion_elem:(int)erosion_elem  Erosion_size:(int)erosion_size
{
    Mat Img = [image CVMat3];
    Mat result = Function::Erosion(Img, erosion_elem, erosion_size);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
}

//毛玻璃
-(UIImage* ) Glass:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::Glass(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
    
}

//浮雕
-(UIImage* ) Relief:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::Relief(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
    
}

//雕刻
-(UIImage* ) Grave:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::Grave(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
    
}

//怀旧
-(UIImage* ) Notalgia:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::Nostalgia(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
    
}

//素描
-(UIImage* ) Skech:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::Skech(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
    
}

//横向模糊
-(UIImage* ) Wind:(UIImage* )image
{
    Mat Img = [image CVMat3];
    Mat result = Function::Wind(Img);
    UIImage* r = [UIImage imageWithCVMat:result];
    return r;
    
}
@end
