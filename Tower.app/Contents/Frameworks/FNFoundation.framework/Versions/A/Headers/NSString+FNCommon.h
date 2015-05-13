//
//  NSString+FNCommon.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 23.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNCommon)

- (BOOL)isEmpty;
- (BOOL)isNotEmpty __attribute__((deprecated));

@end
