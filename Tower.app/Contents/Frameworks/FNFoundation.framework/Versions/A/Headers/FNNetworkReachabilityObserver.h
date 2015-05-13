//
//  FNNetworkReachabilityObserver.h
//  FNFoundation
//
//  Created by Alexander Rinass on 19/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNNetworkReachabilityObserving.h"

@class FNNetworkReachability;
@interface FNNetworkReachabilityObserver : NSObject
@property (nonatomic, weak, readonly) FNNetworkReachability *networkReachability;
@property (nonatomic, weak) id<FNNetworkReachabilityObserving> delegate;

/** @name Creating Objects */

- (id)initWithNetworkReachability:(FNNetworkReachability *)networkReachability delegate:(id<FNNetworkReachabilityObserving>)delegate;

/** @name Starting and Stopping NetworkReachability Observation */

- (void)startObserving;
- (void)stopObserving;

@end
