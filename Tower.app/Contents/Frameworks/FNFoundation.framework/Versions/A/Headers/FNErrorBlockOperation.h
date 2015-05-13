//
//  FNErrorBlockOperation.h
//  FNFoundation
//
//  Created by Alexander Rinass on 27.03.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNErrorBlockOperation : NSOperation
@property (readonly) NSError *error;
@property (copy, readonly) NSError* (^block)();
@property (copy) void (^completionHandler)(NSError *error);

/** @name Creating Error Block Operations */

+ (instancetype)errorBlockOperationWithBlock:(NSError* (^)())block;
- (id)initWithBlock:(NSError* (^)())block;

@end
