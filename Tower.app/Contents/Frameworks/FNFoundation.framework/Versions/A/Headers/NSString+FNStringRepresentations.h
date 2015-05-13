//
//  NSString+FNStringRepresentations.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 09.03.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

NSString * FNStringFromBOOL(BOOL value);

@interface NSString (FNStringRepresentations)

+ (NSString *)stringForBoolean:(BOOL)boolValue;
+ (NSString *)stringForInteger:(NSInteger)integerValue;
+ (NSString *)stringForUnsignedInteger:(NSUInteger)unsignedIntegerValue;
+ (NSString *)stringForDouble:(double)doubleValue;
+ (NSString *)stringForFloat:(float)floatValue;

@end
