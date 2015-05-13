//
//  FNNetworkReachabilityObserving.h
//  FNFoundation
//
//  Created by Alexander Rinass on 19/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol FNNetworkReachabilityObserving <NSObject>
@optional

- (void)networkReachabilityDidChange:(NSNotification *)notification;

@end
