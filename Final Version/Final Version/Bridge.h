//
//  Bridge.h
//  Final Version
//
//  Created by Leo on 2016/12/26.
//  Copyright © 2016年 air711. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface OC : NSObject


//灰度化
-(UIImage* )change:(UIImage* )image;

//显示直方图*IplImage
-(UIImage* )cvShowHist:(UIImage* )image;



//直方图均衡化*IplImage
-(UIImage* )EqualizeHistColorImage:(UIImage* )image;


//添加噪声***************

//1.椒盐噪声*Mat
-(UIImage* )PepperSaultNoise:(UIImage* )image;



//2.随机噪声

-(UIImage* )RandomNoise:(UIImage* )image;


//3.高斯噪声*Mat

-(UIImage* )GaussianNoise:(UIImage* )image;



//超限邻域平均法滤波*IplImage
-(UIImage* )OnBlurSmooth:(UIImage* )image;


//超限中值滤波*IplImage
-(UIImage* )OnMedianSmooth:(UIImage* )image;


//高斯滤波器滤波*IplImage
-(UIImage* )OnGaussSmooth:(UIImage* )image;



//边缘提取
//Roberts*IplImage
-(UIImage* )Roberts:(UIImage* )image;


//Sobel,Prewitt,Laplace*IplImage
-(UIImage* )Sobel_Prewitt_Laplace:(UIImage* )image Menu:(int) menu;


//Hough圆形检测*IplImage
-(UIImage* )Hough:(UIImage* )image;



//最大类间方差法*Mat
-(UIImage* ) afterOTSU1:(UIImage* )image;


-(UIImage* ) afterOTSU2:(UIImage* )image;



//HCM*Mat
-(UIImage* ) HCM:(UIImage* )image Colors:(int)colors;

//开*IplImage
-(UIImage* ) open:(UIImage* )image;


//闭*IplImage
-(UIImage* ) close:(UIImage* )image;


//膨胀*Mat
-(UIImage* ) Dilation:(UIImage* )image Dilation_elem:(int)dilation_elem Dilation_size:(int)dilation_size;


//腐蚀*Mat
-(UIImage* ) Erosion:(UIImage* )image Erosion_elem:(int)erosion_elem  Erosion_size:(int)erosion_size;

//毛玻璃*Mat
-(UIImage* ) Glass:(UIImage* )image;

//浮雕*Mat
-(UIImage* ) Relief:(UIImage* )image;

//雕刻*Mat
-(UIImage* ) Grave:(UIImage* )image;

//怀旧*Mat
-(UIImage* ) Notalgia:(UIImage* )image;

//横向模糊*Mat
-(UIImage* ) Wind:(UIImage* )image;

//素描*Mat
-(UIImage* ) Skech:(UIImage* )image;

@end
