//
//  PEXLogger.h
//  ChinapexAnalytics
//
//  Created by Cedric Wu on 2017/7/18.
//  Copyright © 2017年 Cedric Wu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ApexDataCollectUtil_iOS/ApexDataCollectUtil_iOS.h>

@interface PEXLogger : NSObject
+ (instancetype)sharedInstance;

- (void)setLogLevel:(LoggerLevel)aLevel;

- (void)error:(id)log;
- (void)info:(id)log;
- (void)debug:(id)log;
- (void)Verbose:(id)log;

@end
