//
//  NSNumber+FNRandomNumber.h
//  FNFoundation
//
//  Created by Alexander Rinass on 23/06/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSNumber (FNRandomNumber)

+ (instancetype)randomNumber;
+ (instancetype)randomNumberWithLimit:(NSUInteger)limit;

@end
