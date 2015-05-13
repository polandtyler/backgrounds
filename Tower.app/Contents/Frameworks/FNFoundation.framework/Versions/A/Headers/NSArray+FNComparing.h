//
//  NSArray+FNComparing.h
//  FNFoundation
//
//  Created by Alexander Rinass on 28.05.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray (FNComparing)

/** @name Comparing Object Indexes */

/**
 Compares the order of objects with another array.
 
 Use this method if you have the two arrays that may contain the _same_ 
 (`isEqual:`) objects and you want to know which objects have been removed, 
 inserted or moved around. 
 
 Perfect for table view animations after changes in the data source.
 */
- (void)compareIndexesOfObjectsWithIndexesOfObjectsInArray:(NSArray *)otherArray result:(void (^)(NSIndexSet *removedIndexes, NSIndexSet *insertedIndexes, NSArray *movedIndexes))resultBlock;

- (void)compareIndexesOfObjectsWithIndexesOfObjectsInArray:(NSArray *)otherArray usingComparator:(NSComparator)comparator result:(void (^)(NSIndexSet *removedIndexes, NSIndexSet *insertedIndexes, NSArray *movedIndexes))resultBlock;

@end
