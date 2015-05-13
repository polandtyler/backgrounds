//
//  FNVersionStringComparator.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 24.05.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNVersionStringComparator : NSObject

+ (NSComparisonResult)compareVersion:(NSString *)version toVersion:(NSString *)otherVersion;

@end
