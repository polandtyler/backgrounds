//
//  NSMutableArray+FNMoving.h
//  FNFoundation
//
//  Created by Alexander Rinass on 10/03/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSMutableArray (FNMoving)

- (void)moveObjectAtIndex:(NSUInteger)fromIndex toIndex:(NSUInteger)toIndex;

@end
