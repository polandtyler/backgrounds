//
//  NSOutlineView+FNRowItemConverter.h
//  FNAppKit
//
//  Created by Alexander Rinass on 16.04.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSOutlineView (FNRowItemConverter)

/** @name Converting Between Items and Rows */

- (NSArray *)itemsAtRowIndexes:(NSIndexSet *)rows;
- (NSIndexSet *)rowIndexesForItems:(NSArray *)items;

@end
