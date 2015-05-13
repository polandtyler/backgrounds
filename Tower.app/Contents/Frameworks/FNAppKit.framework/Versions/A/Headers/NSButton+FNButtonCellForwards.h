//
//  NSButton+FNButtonCellForwards.h
//  FNAppKit
//
//  Created by Alexander Rinass on 11/13/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSButton (FNButtonCellForwards)
@property (readonly, getter = isHighlighted) BOOL highlighted;
@property NSColor *backgroundColor;
@property NSInteger showsStateBy;
@property NSInteger highlightsBy;
@property NSControlSize controlSize;
@end
