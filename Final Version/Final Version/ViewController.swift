//
//  ViewController.swift
//  Final Version
//
//  Created by Leo on 2016/12/26.
//  Copyright © 2016年 air711. All rights reserved.
//

import UIKit
import Foundation



var preImage:UIImage!
var curImage:UIImage!
var PrimImage:UIImage!



// 首先在头部加入当前Controller需要遵从的代理
class ViewController: UIViewController,
    UIImagePickerControllerDelegate,
UINavigationControllerDelegate{
    
    
    // 主页导航控制器
    var mainNavigationController:UINavigationController!
    
    // 主页面控制器
    var mainViewController:MainViewController!
    
    // 菜单页控制器
    var menuViewController:MenuViewController?
    
    // 菜单页当前状态
    var currentState = MenuState.collapsed {
        didSet {
            //菜单展开的时候，给主页面边缘添加阴影
            let shouldShowShadow = currentState != .collapsed
            showShadowForMainViewController(shouldShowShadow)
        }
    }
    
    // 菜单打开后主页在屏幕右侧露出部分的宽度
    let menuViewExpandedOffset: CGFloat = 225
    
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        //初始化主视图
        mainNavigationController = UIStoryboard(name: "Main", bundle: nil)
            .instantiateViewController(withIdentifier: "mainNavigaiton")
            as! UINavigationController
        view.addSubview(mainNavigationController.view)
        
        //指定Navigation Bar左侧按钮的事件
        mainViewController = mainNavigationController.viewControllers.first
            as! MainViewController
        mainViewController.navigationItem.leftBarButtonItem?.action = #selector(ViewController.showMenu)
        
        //添加拖动手势
        let panGestureRecognizer = UIPanGestureRecognizer(target: self,
                                                          action: #selector(ViewController.handlePanGesture(_:)))
        mainNavigationController.view.addGestureRecognizer(panGestureRecognizer)
        
        //单击收起菜单手势
        let tapGestureRecognizer = UITapGestureRecognizer(target: self,
                                                          action: #selector(ViewController.handlePanGesture as (ViewController) -> () -> ()))
        mainNavigationController.view.addGestureRecognizer(tapGestureRecognizer)
    }
    
    
    
    func showMenu() {
        //如果菜单是展开的则会收起，否则就展开
        if currentState == .expanded {
            animateMainView(false)
        }else {
            addMenuViewController()
            animateMainView(true)
        }
    }
    
    //拖动手势响应
    func handlePanGesture(_ recognizer: UIPanGestureRecognizer) {
        
        switch(recognizer.state) {
        // 刚刚开始滑动
        case .began:
            // 判断拖动方向
            let dragFromLeftToRight = (recognizer.velocity(in: view).x > 0)
            // 如果刚刚开始滑动的时候还处于主页面，从左向右滑动加入侧面菜单
            if (currentState == .collapsed && dragFromLeftToRight) {
                currentState = .expanding
                addMenuViewController()
            }
            
        // 如果是正在滑动，则偏移主视图的坐标实现跟随手指位置移动
        case .changed:
            let positionX = recognizer.view!.frame.origin.x +
                recognizer.translation(in: view).x
            //页面滑到最左侧的话就不许要继续往左移动
            recognizer.view!.frame.origin.x = positionX < 0 ? 0 : positionX
            recognizer.setTranslation(CGPoint.zero, in: view)
            
        // 如果滑动结束
        case .ended:
            //根据页面滑动是否过半，判断后面是自动展开还是收缩
            let hasMovedhanHalfway = recognizer.view!.center.x > view.bounds.size.width
            animateMainView(hasMovedhanHalfway)
        default:
            break
        }
    }
    
    //单击手势响应
    func handlePanGesture() {
        //如果菜单是展开的点击主页部分则会收起
        if currentState == .expanded {
            animateMainView(false)
        }
    }
    
    // 添加菜单页
    func addMenuViewController() {
        if (menuViewController == nil) {
            menuViewController = UIStoryboard(name: "Main", bundle: nil)
                .instantiateViewController(withIdentifier: "menuView") as? MenuViewController
            
            // 插入当前视图并置顶
            view.insertSubview(menuViewController!.view, at: 0)
            
            // 建立父子关系
            addChildViewController(menuViewController!)
            menuViewController!.didMove(toParentViewController: self)
        }
    }
    
    //主页自动展开、收起动画
    func animateMainView(_ shouldExpand: Bool) {
        // 如果是用来展开
        if (shouldExpand) {
            // 更新当前状态
            currentState = .expanded
            // 动画
            animateMainViewXPosition(mainNavigationController.view.frame.width -
                menuViewExpandedOffset)
        }
            // 如果是用于隐藏
        else {
            // 动画
            animateMainViewXPosition(0) { finished in
                // 动画结束之后s更新状态
                self.currentState = .collapsed
                // 移除左侧视图
                self.menuViewController?.view.removeFromSuperview()
                // 释放内存
                self.menuViewController = nil;
            }
        }
    }
    
    //主页移动动画（在x轴移动）
    func animateMainViewXPosition(_ targetPosition: CGFloat,
                                  completion: ((Bool) -> Void)! = nil) {
        //usingSpringWithDamping：1.0表示没有弹簧震动动画
        UIView.animate(withDuration: 0.5, delay: 0, usingSpringWithDamping: 1.0,
                       initialSpringVelocity: 0, options: UIViewAnimationOptions(), animations: {
                        self.mainNavigationController.view.frame.origin.x = targetPosition
        }, completion: completion)
    }
    
    //给主页面边缘添加、取消阴影
    func showShadowForMainViewController(_ shouldShowShadow: Bool) {
        if (shouldShowShadow) {
            mainNavigationController.view.layer.shadowOpacity = 0.8
        } else {
            mainNavigationController.view.layer.shadowOpacity = 0.0
        }
    }
    
    // 菜单状态枚举
    enum MenuState {
        case collapsed  // 未显示(收起)
        case expanding   // 展开中
        case expanded   // 展开
    }
    
    
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

}

