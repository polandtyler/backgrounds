//
//  NSView+FNSubviews.h
//  Tower
//
//  Created by Tobias Günther on 15.04.11.
//  Copyright 2011 n/a. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSView (FNSubviews)

/** @name Managing Subviews */ 

/**
 Convenient method for `[[self subviews] firstObject]`
 @return The first `NSView` or nil
 */
- (NSView *)firstSubview;

/**
 Removes all subviews from the receiver via -makeObjectsPerformSelection:
 */
- (void)removeAllSubviews;

@end
