//
//  NSSegmentedControl+NSSegmentedCellForwards.h
//  FNAppKit
//
//  Created by Alexander Rinass on 30/10/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSSegmentedControl (NSSegmentedCellForwards)

- (NSString *)toolTipForSegment:(NSInteger)segment;
- (void)setToolTip:(NSString *)toolTip forSegment:(NSInteger)segment;

@end
