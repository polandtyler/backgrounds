//
//  NSTableView+FNSortedColumn.h
//  FNAppKit
//
//  Created by Alexander Rinass on 10.04.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSTableView (FNSortedColumn)

- (BOOL)isSortedColumn:(NSInteger)column ascending:(BOOL *)ascending;
- (NSInteger)sortedColumn;
- (NSTableColumn *)sortedTableColumn;

@end
