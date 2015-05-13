//
//  NSOperationQueue+FNPerformBlock.h
//  FNFoundation
//
//  Created by Alexander Rinass on 08.07.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSOperationQueue (FNPerformBlock)

- (void)performBlock:(void (^)())block;
- (void)performBlockAndWait:(void (^)())block;

@end
