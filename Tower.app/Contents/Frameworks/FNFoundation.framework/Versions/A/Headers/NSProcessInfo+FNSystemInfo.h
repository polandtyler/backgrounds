//
//  NSProcessInfo+FNSystemInfo.h
//  FNFoundation
//
//  Created by Alexander Rinass on 09/04/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSProcessInfo (FNSystemInfo)

+ (NSString *)operatingSystemVersionString;
- (NSString *)operatingSystemVersionStringValue;

@end
