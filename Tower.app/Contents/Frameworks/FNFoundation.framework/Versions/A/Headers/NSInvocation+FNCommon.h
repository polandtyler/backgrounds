//
//  NSInvocation+FNCommon.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSInvocation (FNCommon)

+ (id)invocationWithTarget:(id)target selector:(SEL)selector;
+ (id)invocationWithTarget:(id)target selector:(SEL)selector argument:(id)argument;
+ (id)invocationWithTarget:(id)target selector:(SEL)selector arguments:(NSArray *)arguments;

@end
