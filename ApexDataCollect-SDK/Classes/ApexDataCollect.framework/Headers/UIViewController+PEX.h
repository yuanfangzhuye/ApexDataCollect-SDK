//
//  UIViewController+PEX.h
//  ChinapexAnalytics
//
//  Created by Cedric Wu on 2017/7/19.
//  Copyright © 2017年 Cedric Wu. All rights reserved.
//

#import <UIKit/UIKit.h>
@class PEXViewPageModel;

@interface UIViewController (PEX)
@property (nonatomic, strong, readonly) PEXViewPageModel *pvModel; /**< vc 属性 */
@property (nonatomic, strong) NSMutableDictionary *pvs; /**< 控件pv的集合 */
@property (nonatomic, strong) UIView *showingView; /**< 单VC管理多页面时,设置当前正在显示的页面,设置后生成的事件将会更详细的划分到每个页面 */
@property (nonatomic, assign) BOOL didAppear; /**< 是否已经显示在屏幕上 */
@end
