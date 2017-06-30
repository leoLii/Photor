

import Foundation
import UIKit
//继承自UIImagePickerController，遵守代理
class ImagePickerViewController: UIImagePickerController,UIImagePickerControllerDelegate,UINavigationControllerDelegate {
    override func viewDidLoad() {
        super.viewDidLoad()
        // photoLibrary 相册(默认的)
        // camera 相机
        // SavedPhotosAlbum已保存的相片
        sourceType = UIImagePickerControllerSourceType.photoLibrary//相机（只能在真机上使用）
        
        //        self.view.addSubview(redView)
        //        delegate = self
        //        redView.backgroundColor = UIColor.redColor()
    }
}
