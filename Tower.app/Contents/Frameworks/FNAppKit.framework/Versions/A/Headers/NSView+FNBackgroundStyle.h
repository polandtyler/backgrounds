//
//  NSView+FNBackgroundStyle.h
//  FNAppKit
//
//  Created by Alexander Rinass on 22/10/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSView (FNBackgroundStyle)

- (NSBackgroundStyle)effectiveBackgroundStyle;
- (void)updateBackgroundStyleForSubtreeIfNeeded;

@end
