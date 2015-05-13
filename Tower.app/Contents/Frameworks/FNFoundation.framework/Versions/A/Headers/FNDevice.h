//
//  FNDevice.h
//  Tower
//
//  Created by Alexander Rinass on 24.08.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNDevice : NSObject

#pragma mark - Factory Methods

+ (id)currentDevice __deprecated;

#pragma mark - Querying the System Version

- (NSString *)systemVersion __deprecated;
- (NSInteger)majorSystemVersion __deprecated;
- (NSInteger)minorSystemVersion __deprecated;
- (BOOL)isSystemVersion10_5 __deprecated;
- (BOOL)isSystemVersion10_6 __deprecated;
- (BOOL)isSystemVersion10_7 __deprecated;

@end
