//
//  NSString+FNVersionStringComparator.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 24.05.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNVersionStringComparator)

- (NSComparisonResult)compareToOtherVersionString:(NSString *)otherVersionString;

- (BOOL)isGreaterThanOtherVersionString:(NSString *)otherVersionString;
- (BOOL)isGreaterThanOrEqualToOtherVersionString:(NSString *)otherVersionString;
- (BOOL)isLessThanOtherVersionString:(NSString *)otherVersionString;
- (BOOL)isLessThanOrEqualToOtherVersionString:(NSString *)otherVersionString;

@end
