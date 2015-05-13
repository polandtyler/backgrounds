//
//  NSString+FNStringEncoding.h
//  FNFoundation
//
//  Created by Alexander Rinass on 03.12.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNStringEncoding)

+ (NSStringEncoding)stringEncodingFromIANACharSetName:(NSString *)charSetName;

@end
