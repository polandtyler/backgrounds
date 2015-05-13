//
//  NSTableView+FNAffectedRows.h
//  FNAppKit
//
//  Created by Alexander Rinass on 26.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSTableView (FNAffectedRows)

/**
 Returns the affected rows for the current selection and clicked row.

 If the user performs an action on a row that is not part of the current
 selection, the action will be performed only on this row, e.g. in Finder.

 Otherwise, all selected rows will be returned.
 */
- (NSIndexSet *)affectedRowIndexesForClickedRow;

@end
