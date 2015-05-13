//
//  FNNetworkReachability.h
//  FNFoundation
//
//  Created by Alexander Rinass on 15/07/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import "FNNetworkReachabilityDelegate.h"

typedef void (^FNNetworkReachabilityNotificationBlock)(NSString *host, BOOL reachable);

extern NSString *const FNNetworkReachabilityDidChangeNotification;

@interface FNNetworkReachability : NSObject
@property (nonatomic, weak) id<FNNetworkReachabilityDelegate> delegate;
@property (nonatomic, readonly) NSString *host;
@property (nonatomic, readonly, getter=isMonitoring) BOOL monitoring;
@property (nonatomic, readonly, getter=isReachable) BOOL reachable;
@property (atomic, copy) FNNetworkReachabilityNotificationBlock notificationBlock;

+ (instancetype)sharedNetworkReachability;

+ (BOOL)isHostAvailable:(NSString *)hostname;
+ (void)checkNetworkReachabilityForHost:(NSString *)hostname completionHandler:(FNNetworkReachabilityNotificationBlock)completionHandler;

+ (instancetype)networkReachabilityWithHostName:(NSString *)hostname;
+ (instancetype)networkReachabilityWithIP4AddressString:(NSString *)internetAddress;
+ (instancetype)networkReachabilityForInternetConnection;

- (instancetype)initWithNetworkReachability:(SCNetworkReachabilityRef)reachability;

- (void)startMonitoringNetworkReachability;
- (void)stopMonitoringNetworkReachability;

- (void)checkNetworkReachabilityForHost:(NSString *)hostname completionHandler:(FNNetworkReachabilityNotificationBlock)completionHandler;

@end
