//
//  MainViewController.swift
//  Final Version
//
//  Created by Leo on 2016/12/26.
//  Copyright © 2016年 air711. All rights reserved.
//

import Foundation
import UIKit

class MainViewController: UIViewController,UIImagePickerControllerDelegate,
UINavigationControllerDelegate {
    
    
    
   
    
    var times:Int! = 0
    
    @IBOutlet weak var Hist: UIImageView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        Hist.isHidden = true
        //imagePicked.image = curImage
        NotificationCenter.default.addObserver(self, selector: #selector(MainViewController.reload(_:)), name: NSNotification.Name(rawValue: "name"), object: nil)
        // Do any additional setup after loading the view.
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    
    
    func reload(_ notifaction: Notification) {
        preImage = imagePicked.image
        imagePicked.image = notifaction.object as! UIImage?
        curImage = imagePicked.image
        //self.bNameTextField.text = notifaction.object as? String
        //NotificationCenter.default.removeObserver(self)
        
    }
   
    
    // 这个对象是用来在屏幕上显示
    @IBOutlet weak var imagePicked: UIImageView!
    
    // 这个Action方法对应着屏幕上的按钮，该按钮点击后会调用图库
    @IBAction func add(_ sender: UIBarButtonItem) {
        // 判断数据源是否合法，这里的.photoLibrary省略了其类名，Swift会自动推导
        if UIImagePickerController.isSourceTypeAvailable(.photoLibrary){
            let imagePicker = UIImagePickerController()
            imagePicker.delegate = self
            imagePicker.sourceType = .photoLibrary
            imagePicker.allowsEditing = true
            // 这一句，开始调用图库
            self.present(imagePicker,animated: true)
        }
    }
    // 实现代理的方法
    // 注意，这里和swift3.0之前的版本实现方法都不太一样，这是唯一的写法，网上流传的其他方法都是过时的
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any]) {
        if let image = info[UIImagePickerControllerOriginalImage] as? UIImage{
            // 将图片显示给UIImageView
            preImage = imagePicked.image
            imagePicked.image = image
            curImage = image
            PrimImage = image
        }else{
            print("pick image wrong")
        }
        // 收回图库选择界面
        self.dismiss(animated: true, completion: nil)
    }
    /*
     // MARK: - Navigation
     
     // In a storyboard-based application, you will often want to do a little preparation before navigation
     override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
     // Get the new view controller using segue.destinationViewController.
     // Pass the selected object to the new view controller.
     }
     */
    
    @IBAction func back(_ sender: UIBarButtonItem) {
        // 判断数据源是否合法，这里的.photoLibrary省略了其类名，Swift会自动推导
      if ((imagePicked.image) != nil)
      {
        imagePicked.image = preImage
        curImage = preImage
      }else{
        print("No image!")
      }

    }
    
    
    @IBAction func Prim(_ sender: AnyObject) {
        preImage = imagePicked.image
        imagePicked.image = PrimImage
        curImage = imagePicked.image
    }

    
    //显示直方图
    @IBAction func Hist(_ sender: AnyObject) {
        self.times = self.times + 1
        if((self.times % 2) == 0)
        {
            Hist.isHidden = true
        }else {
            let oc = OC()
            Hist.image = oc.cvShowHist(imagePicked.image)
            Hist.isHidden = false
        }
        
        if(self.times == 10) {
            self.times = 0;
        }
    }
    
    
}
