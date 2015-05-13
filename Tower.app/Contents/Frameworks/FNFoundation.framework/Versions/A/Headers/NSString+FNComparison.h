//
//  NSString+FNComparison.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNComparison)

/**
 Wether or not two Unicode strings are identical.
 
 The default `isEqualToString:` method may not properly compare unicode strings
 in some cases.
 */
- (BOOL)isEqualToUnicodeString:(NSString *)anotherString;

@end
