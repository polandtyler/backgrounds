//
//  NSObject+FNPerformBlock.h
//  FNFoundation
//
//  Created by Alexander Rinass on 28/03/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSObject (FNPerformBlock)

- (void)performBlockOnMainThread:(void (^)(void))block afterDelay:(NSTimeInterval)delay;

@end
