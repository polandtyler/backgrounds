//
//  FNNetworkReachabilityDelegate.h
//  FNFoundation
//
//  Created by Alexander Rinass on 19/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNNetworkReachability;
@protocol FNNetworkReachabilityDelegate <NSObject>
@optional

- (void)networkReachabilityDidChange:(FNNetworkReachability *)networkReachability;

@end
