//
//  NSOperationQueue+FNFoundation.h
//  FNFoundation
//
//  Created by Alexander Rinass on 27.03.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSOperationQueue (FNFoundation)

+ (id)serialQueue;
+ (id)queueWithMaxConcurrentOperationCount:(NSUInteger)maxConcurrentOperationCount;

@end
