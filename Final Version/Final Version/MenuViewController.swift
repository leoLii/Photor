//
//  MenuViewController.swift
//  Final Version
//
//  Created by Leo on 2016/12/26.
//  Copyright © 2016年 air711. All rights reserved.
//

import Foundation
import UIKit



class MenuViewController: UIViewController, UIImagePickerControllerDelegate,
UINavigationControllerDelegate{
    
   
    var dilation_Time:Int = 0
    var dilation_Elem:Int = 0
    var dilation_Size:Int = 0
    
    var erosion_Time:Int = 0
    var erosion_Elem:Int = 0
    var erosion_Size:Int = 0
    
    var OTSU_Time: Int = 0
    
    @IBOutlet weak var OTSU:UISegmentedControl!
    
    @IBOutlet weak var dElem:UISegmentedControl!
    @IBOutlet weak var dSize:UISlider!
    
    @IBOutlet weak var eElem:UISegmentedControl!
    @IBOutlet weak var eSize:UISlider!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        OTSU.isHidden = true
        
        
        dElem.isHidden = true
        dSize.isHidden = true
        
        eElem.isHidden = true
        eSize.isHidden = true
        
        // Do any additional setup after loading the view.
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    //灰度化
    @IBAction func change(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result:UIImage! = oc.change(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    //均衡化
    @IBAction func EqualizeHistColorImage(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result:UIImage! = oc.equalizeHistColorImage(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }

    
    //椒盐噪声
    @IBAction func PepperSaultNoise(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result:UIImage! = oc.pepperSaultNoise(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    
    //随机噪声
    @IBAction func RandomNoise(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result:UIImage! = oc.randomNoise(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    
    //高斯噪声
    @IBAction func GaussianNoise(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result:UIImage! = oc.gaussianNoise(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    
    //平均滤波
    @IBAction func OnBlurSmooth(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result:UIImage! = oc.onBlurSmooth(Input)
        let result2:UIImage! = oc.onGaussSmooth(result)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result2)
    }
    
    
    //高斯滤波
    @IBAction func OnGaussSmooth(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result:UIImage! = oc.onGaussSmooth(Input)
        let result2:UIImage! = oc.onGaussSmooth(result)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result2)
    }
    
    
    //中值滤波
    @IBAction func OnMedianSmooth(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result:UIImage! = oc.onMedianSmooth(Input)
        let result2:UIImage! = oc.onGaussSmooth(result)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result2)
    }
    
    
    @IBAction func OTSU(_ sender: AnyObject) {
        self.OTSU_Time = self.OTSU_Time + 1
        if((self.OTSU_Time % 2) == 0)
        {
            OTSU.isHidden = true
        }else {
            OTSU.isHidden = false
            let Input: UIImage! = PrimImage
            let oc = OC()
            let result:UIImage! = oc.afterOTSU1(Input)
            NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
        }
            
        if(self.OTSU_Time == 10) {
            self.OTSU_Time = 0
        }
    }
    
    
    
    
    @IBAction func OTSU1(_ sender: UISegmentedControl) {
        let Input: UIImage! = PrimImage
        let oc = OC()
        let result1:UIImage! = oc.afterOTSU1(Input)
        let result2:UIImage! = oc.afterOTSU2(Input)
        if(sender.selectedSegmentIndex == 0) {
            NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result1)
        } else {
            NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result2)
        }
    }
    
    
    
    //Roberts
    @IBAction func Roberts(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let presult:UIImage! = oc.change(Input)
        let result:UIImage! = oc.roberts(presult)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    
    //Sobel
    @IBAction func Sobel(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let presult:UIImage! = oc.change(Input)
        let result:UIImage! = oc.sobel_Prewitt_Laplace(presult, menu: 2)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    
    //Prewitt
    @IBAction func Prewitt(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let presult:UIImage! = oc.change(Input)
        let result:UIImage! = oc.sobel_Prewitt_Laplace(presult, menu: 3)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    
    //Laplacian
    @IBAction func Laplacian(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let presult:UIImage! = oc.change(Input)
        let result:UIImage! = oc.sobel_Prewitt_Laplace(presult, menu: 3)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    
    //差分
    @IBAction func A(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let presult:UIImage! = oc.change(Input)
        let result:UIImage! = oc.sobel_Prewitt_Laplace(presult, menu: 2)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    
    //开
    @IBAction func open(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result1:UIImage! = oc.erosion(Input, erosion_elem: 0, erosion_size: 3)
        let result2:UIImage! = oc.dilation(result1, dilation_elem: 0, dilation_size: 3)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result2)
    }
    
    
    //闭
    @IBAction func close(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result1:UIImage! = oc.dilation(Input, dilation_elem: 0, dilation_size: 3)
        let result2:UIImage! = oc.erosion(result1, erosion_elem: 0, erosion_size: 3)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result2)
    }
    
    
    //膨胀
    @IBAction func Dilation(_ sender: AnyObject) {
        
        self.dilation_Time = self.dilation_Time + 1
        if((self.dilation_Time % 2) == 0)
        {
            dElem.isHidden = true
            dSize.isHidden = true
        }else {
            dElem.isHidden = false
            dSize.isHidden = false
        }
        
        if(self.dilation_Time == 10) {
            self.dilation_Time = 0;
        }

        
    }
    
    @IBAction func delemSection (_ sender: UISegmentedControl) {
        let Input: UIImage! = curImage
        let oc = OC()
        dilation_Size = 0
        dSize.value = 0
        if (sender.selectedSegmentIndex == 0) {
        dilation_Elem = 0
        let result:UIImage! = oc.dilation(Input, dilation_elem: Int32(dilation_Elem), dilation_size: Int32(dilation_Size))
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
        } else if (sender.selectedSegmentIndex == 1){
            dilation_Elem = 1
            let result:UIImage! = oc.dilation(Input, dilation_elem: Int32(dilation_Elem), dilation_size: Int32(dilation_Size))
            NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
        }else if (sender.selectedSegmentIndex == 2){
            dilation_Elem = 2
            let result:UIImage! = oc.dilation(Input, dilation_elem: Int32(dilation_Elem), dilation_size: Int32(dilation_Size))
            NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
        }
    }
    
    @IBAction func dsizeSection (_ sender: UISlider) {
        let Input: UIImage! = PrimImage
        let oc = OC()
        dilation_Size = Int(sender.value)
        let result:UIImage! = oc.dilation(Input, dilation_elem: Int32(dilation_Elem), dilation_size: Int32(dilation_Size))
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    
    //腐蚀
    @IBAction func Erosion(_ sender: AnyObject) {
        self.erosion_Time = self.erosion_Time + 1
        if((self.erosion_Time % 2) == 0)
        {
            eElem.isHidden = true
            eSize.isHidden = true
        }else {
            eElem.isHidden = false
            eSize.isHidden = false
        }
        
        if(self.erosion_Time == 10) {
            self.erosion_Time = 0;
        }
        
        
    }
    
    @IBAction func eelemSection (_ sender: UISegmentedControl) {
        let Input: UIImage! = curImage
        let oc = OC()
        erosion_Size = 0
        eSize.value = 0
        if (sender.selectedSegmentIndex == 0) {
            erosion_Elem = 0
            let result:UIImage! = oc.erosion(Input, erosion_elem: Int32(erosion_Elem), erosion_size: Int32(erosion_Size))
            NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
        } else if (sender.selectedSegmentIndex == 1){
            erosion_Elem = 1
            let result:UIImage! = oc.erosion(Input, erosion_elem: Int32(erosion_Elem), erosion_size: Int32(erosion_Size))
            NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
        }else if (sender.selectedSegmentIndex == 2){
            erosion_Elem = 2
            let result:UIImage! = oc.erosion(Input, erosion_elem: Int32(erosion_Elem), erosion_size: Int32(erosion_Size))
            NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
        }
    }
    
    @IBAction func esizeSection (_ sender: UISlider) {
        let Input: UIImage! = PrimImage
        let oc = OC()
        erosion_Size = Int(sender.value)
        let result:UIImage! = oc.erosion(Input, erosion_elem: Int32(erosion_Elem), erosion_size: Int32(erosion_Size))
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    //HCM
    @IBAction func HCM(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result:UIImage! = oc.hcm(Input , colors: 5)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    
    //Hough
    @IBAction func Hough(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let presult: UIImage! = oc.hough(Input)
        let result:UIImage! = oc.hough(presult)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    //毛玻璃
    @IBAction func Glass(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        let result:UIImage! = oc.glass(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    //浮雕
    @IBAction func Relief(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        
        let result:UIImage! = oc.relief(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    //雕刻
    @IBAction func Grave(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        
        let result:UIImage! = oc.grave(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    //怀旧
    @IBAction func Nostalgia(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        
        let result:UIImage! = oc.notalgia(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    //素描
    @IBAction func Skech(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
       
        let result:UIImage! = oc.skech(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }
    
    //横向模糊
    @IBAction func Wind(_ sender: AnyObject) {
        let Input: UIImage! = curImage
        let oc = OC()
        
        let result:UIImage! = oc.wind(Input)
        NotificationCenter.default.post(name: Notification.Name(rawValue: "name"), object: result)
    }

    
    /*
     // MARK: - Navigation
     
     // In a storyboard-based application, you will often want to do a little preparation before navigation
     override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
     // Get the new view controller using segue.destinationViewController.
     // Pass the selected object to the new view controller.
     }
     */
    
}
