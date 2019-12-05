//
//  UICollectionViewCell+PEX.h
//  AFJSONRPCClient-iOS10.0
//
//  Created by yulin chi on 2018/11/16.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UICollectionViewCell (PEX)
@property (nonatomic, strong) NSIndexPath *pex_indexPath;
@property (nonatomic, copy) NSString *trackDataId; /**< 点击cell时将会携带上传的数据 */
@end

NS_ASSUME_NONNULL_END
