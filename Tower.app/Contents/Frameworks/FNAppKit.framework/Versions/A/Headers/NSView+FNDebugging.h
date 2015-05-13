//
//  NSView+FNDebugging.h
//  FNAppKit
//
//  Created by Alexander Rinass on 21.03.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSView (FNDebugging)

/** @name Debugging */

// Thanks to the OmniGroup for inspiration
- (void)fn_logConstraints;
- (void)fn_logViewHierarchy;

@end
