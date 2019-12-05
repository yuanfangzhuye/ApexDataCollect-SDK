//
//  APEXDataCollectSDK.h
//  DataCollector
//
//  Created by yulin chi on 2018/10/17.
//  Copyright © 2018 yulin chi. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PEXBaseModel;

//事件追踪类型
typedef NS_ENUM(NSUInteger, ApexAnalyticEventType) {
    ApexAnalyticEventType_None = 0, /* 不追踪任何事件 */
    ApexAnalyticEventType_AppLaunch = 1 << 0, /* 追踪app启动事件 */
    ApexAnalyticEventType_Click = 1 << 1, /* 追踪点击事件 */
    ApexAnalyticEventType_ViewController = 1 << 2, /* 追踪浏览事件 */
    ApexAnalyticEventType_ViewExposureRate = 1 << 3 /* 追踪列表曝光事件 */
};

//事件入队发送方式
typedef NS_ENUM(NSUInteger, ApexMessageSendPriority) {
    ApexMessageSendPriority_Height = 0,/* 立即发送 */
    ApexMessageSendPriority_Normal, /* 入队等待发送 */
    ApexMessageSendPriority_Low, /*  下次app开启时发送 */
};

//事件类型
typedef NS_ENUM(NSUInteger, ApexTrackType) {
    ApexTrackType_Custom = 0, /* 自定义事件即代码埋点事件 */
    ApexTrackType_Cold = 1 << 0, /* 冷启动事件 */
    ApexTrackType_Click = 1 << 1, /* 点击事件 */
    ApexTrackType_ViewPage = 1 << 2, /* 页面浏览事件 */
    ApexTrackType_List = 6, /* 列表页面曝光率事件 */
    ApexTrackType_ElemPv = 5, /* 控件元素的曝光率 */
    ApexTrackType_AppUsageTime = 7
};

//地理信息语言设置
typedef NS_ENUM(NSUInteger, ApexLocationDataLanguage) {
    ApexLocationDataLanguage_System = 0,/* 无设置 */
    ApexLocationDataLanguage_Hans, /* 简体中文 */
    ApexLocationDataLanguage_Hant, /* 繁体中文 */
    ApexLocationDataLanguage_EN, /* 英文 */
    ApexLocationDataLanguage_Jap /* 日语 */
};

typedef NS_ENUM(NSInteger, ApexLocalization) {
    ApexLocalization_ByCLLocation, //通过core location获取地理位置
};

//SDK线上/开发环境设置
typedef NS_ENUM(NSUInteger, APEXDataCollectSDKWorkModel) {
    APEXDataCollectSDKWorkModel_Product, //线上环境
    APEXDataCollectSDKWorkModel_Developing //圈选环境
};

static NSString* const PexlocalConfigFileName = @"ApexDataCollectConfigFile";
static NSString* const PexInnerPidLocalKey = @"PexInnerPidName";

@interface APEXDataCollectSDK : NSObject
+ (instancetype)shareCollector;

@property (nonatomic, assign) ApexLocationDataLanguage currentLanguage; /**< 定位信息返回语言 */
@property (nonatomic, copy, readonly) NSString *serverUrl; /* 服务端url */
@property (nonatomic, copy,readonly) NSString *trackingID; /**< MD5(serverUrl) */
@property (nonatomic, copy, readonly) NSString *UUID; /**< 自动生成 存储在keychain中 */
@property (nonatomic, copy, readonly) NSString *apiKey; /**< api key */
@property (nonatomic, copy) NSString *UID; /**< 用户id */
@property (nonatomic, copy) NSString *localConfigVersion; /**< 当前本地的配置文件版本 */
@property (nonatomic, assign, readonly) NSTimeInterval uploadInterval; /**< 设置上报轮询的时间间隔(最小值: 60s) 小于60 默认60s*/
@property (nonatomic, assign, readonly) NSInteger uploadQueneTrigerCount; /**< 上报队列count的上报触发值(最小值: 50) */
@property (nonatomic, assign, readonly) APEXDataCollectSDKWorkModel currentMode; /**< SDK当前的工作模式 默认线上模式 */
@property (nonatomic, assign, readonly) BOOL shoudReport; /**< 是否上报数据 */
@property (nonatomic, assign, readonly) BOOL isPrepared; /**< 是否初始化完成 */
@property (nonatomic, assign, readonly) BOOL debug; /**< 是否debug模式 */
@property (nonatomic, strong, readonly) NSMutableDictionary *cachedInfo; /**< 缓存的设备信息 */
@property (nonatomic, assign, readonly) BOOL strictlyUploadInfomationOfCellsAndItems; /**< 是否仍然上传未配置过的cell以及items(false:上传, true:不上传) */
@property (nonatomic, assign, readonly) BOOL automaticallyCleanUp; /**<  是否删除超出给定的时间段的数据 */
@property (nonatomic, copy, readonly) NSString *appLanguage; /**<  */
@property (nonatomic, assign, readonly) NSTimeInterval CleanUpPeriod;

@property (nonatomic, copy, readonly) NSString *visitId; /**< 会话id 无则不填*/
@property (nonatomic, copy, readonly) NSString *innerPid; /**< innerpid 无则不填*/

@property (nonatomic, copy, readonly) NSString *configUrl; /**< 配置文件下载url */
@property (nonatomic, copy, readonly) NSString *VisualizationDomain; /**< 可视化sdk接口域名 */

/**
 可视化跳转回调中调用,通知SDK进行验证与开启可视化功能
 */
+ (void)openUrl:(NSURL*)url;


/**
 初始化方法(必要)

 @param serverUrl 上报服务端的域名
 @param uuid uuid
 */
- (void)startCollectorWithServersUrl:(NSString *)serverUrl uuid:(NSString*)uuid;


/**
 设置下载配置文件的url
 */
- (void)setDownloadConfigServerUrl:(NSString *)configUrl DEPRECATED_MSG_ATTRIBUTE("please use setVisualizationSDKServerDomain: ");


/**
 设置可视化sdk的域名,域名后不跟\(必要)
 */
- (void)setVisualizationSDKServerDomain:(NSString *)VisualizationDomain;

#pragma mark - config
/**
 设置追踪事件类型

 @param eventType 事件类型 追踪多个事件可用 | 操作
 */
- (void)configAutoTrackEventType:(ApexAnalyticEventType)eventType;

/**
 设置sdk当前的模式 (必要)
 */
- (void)configSDKMode:(APEXDataCollectSDKWorkModel)mode DEPRECATED_MSG_ATTRIBUTE("please use setDebug: to Control SDK mode");


- (void)setDebug:(BOOL)debug;

/**
 设置SDK是否上报事件数据, 默认为 true 上报事件
 */
- (void)configShouldReport:(bool)shoudReport;

/**
 此事件类型是否被追踪
 */
- (BOOL)isEventTypeTracked:(ApexAnalyticEventType)eventType;

/**
 登入with用户id
 */
- (void)signInWithUID:(NSString*)UID;


/**
 登出时调用
 */
- (void)signOut;

/**
 设置定位信息国际化
 */
- (void)configAppLocationLanguage:(ApexLocationDataLanguage)currentLanguage;


/**
 控制地理位置获取方式,不调用则不获取地理位置
 */
- (void)configLocalizationMethod:(ApexLocalization)localizationMethod;

/**
 设置上报轮询的时间间隔 default:60s
 */
- (void)configUploadTrigerTimeInterval:(NSTimeInterval)interval;


/**
 设置上报队列的上报触发值,达到值时立刻上报 default:100
 */
- (void)configUploadTrigerQueneMaxCount:(NSInteger)count;


/**
 是否仍然上传开发人员未配置过trackDataId的cell以及items(true:不上传, false:上传) 默认为true
 */
- (void)configStrictlyUploadInfomationOfCellsAndItems:(BOOL)shouldStrict;


/**
 是否删除超出给定的时间段的数据
 🌰: period定为一个月,当有数据在一个月之后都还没有上报成功的话,就删除掉此数据
 @param shouldClean 是否开启此功能 默认: 开启
 @param period 数据保留的时间段 单位:秒 默认:7天
 */
- (void)configAutomaticalyCleanUp:(BOOL)shouldClean period:(NSTimeInterval)period;

#pragma mark - track
/**
 代码埋点接口

 @param label 可选 如: 预留
 @param value 可选 如: {商品详情数据}
 */
- (void)trackWithMode:(ApexMessageSendPriority)mode label:(NSString*)label value:(NSDictionary*)value;


/**
 追踪此事件 SDK外部不应该使用此api
 */
- (void)track:(PEXBaseModel*)model TrackType:(ApexTrackType)type;


/**
 强制显示悬浮按钮, 仅供测试使用. sdk已自动管理悬浮按钮的i显示
 */
- (void)forceToShowFuncBtn;

/*********************************Spring Config Exclusive********************************************/
/**
 设置对话id(s4)
 */
- (void)configVisitId:(NSString*)visitId;

/**
 告诉sdk app的语言
 */
- (void)configAppLanguage:(NSString*)appLanguage;

/**
配置 InnerPid 以及其有效期
 */
- (void)configInnerPid:(NSString*)innerpid withPeriodSeconds:(NSTimeInterval)seconds;


/**
 验证本地innerpid是否有效
 */
- (void)verifyLocalInnerPid;

@end

