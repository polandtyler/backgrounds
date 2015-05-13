//
//  NSData+FNSeparator.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (FNSeparator)

- (NSArray *)componentsSeparatedByChar:(char)separator;
- (NSArray *)componentsSeparatedByNULByte;

@end
