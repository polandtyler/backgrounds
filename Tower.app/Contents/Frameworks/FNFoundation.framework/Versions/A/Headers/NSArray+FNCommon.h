//
//  NSArray+FNCommon.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray (FNCommon)

#
#pragma mark - Array Class Methods

+ (NSArray *)splitArray:(NSArray *)targetArray componentsPerSegment:(NSUInteger)componentsCount;

#pragma mark - Querying an Array

- (BOOL)isEmpty;
- (id)firstObject;

#pragma mark - Deriving New Arrays

- (NSArray *)arrayByRemovingObjectsFromArray:(NSArray *)otherArray;
- (NSArray *)arrayByRemovingObjectsInRange:(NSRange)range;

@end
