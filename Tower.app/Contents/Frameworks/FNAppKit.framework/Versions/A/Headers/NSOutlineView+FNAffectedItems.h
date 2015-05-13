//
//  NSOutlineView+FNAffectedItems.h
//  FNAppKit
//
//  Created by Alexander Rinass on 26.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSOutlineView (FNAffectedItems)

/**
 Returns the affected items for the current selection and clicked row.
 */
- (NSArray *)affectedItemsForClickedRow;

@end
