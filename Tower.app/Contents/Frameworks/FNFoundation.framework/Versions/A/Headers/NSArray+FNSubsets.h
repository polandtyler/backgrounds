//
//  NSArray+FNSubsets.h
//  FNFoundation
//
//  Created by Alexander Rinass on 12.12.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray (FNSubsets)

/**
 1
 1,2
 1,3
 1,2,3
 1,3,2
 2
 2,1
 2,3
 2,1,3
 2,3,1
 3
 3,1
 3,2
 3,1,2
 3,2,1
 */
- (NSSet *)allPossibleUniqueSubsets;

@end
