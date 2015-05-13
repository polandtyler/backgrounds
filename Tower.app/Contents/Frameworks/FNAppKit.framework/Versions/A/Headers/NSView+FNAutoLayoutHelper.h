//
//  NSView+FNAutoLayoutHelper.h
//  FNAppKit
//
//  Created by Florian Buerger on 2/19/13.
//  Copyright (c) 2013 Florian Buerger. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSView (FNAutoLayoutHelper)

- (NSArray *)autoresizeConstraints;

/** @name SplitView pre 10.8 */
/** @brief  Find first min/max width/height constraints
            in subtree to constrain splitview resizing
            min methods return fittingSize.width/height
            max methods return first 
            constraint.width/height <= X or -1 if no
            constraint can be found in the subtree.
 */

- (CGFloat)fn_minWidth;
- (CGFloat)fn_maxWidth;

- (CGFloat)fn_minHeight;
- (CGFloat)fn_maxHeight;

/**
 Add H:|[view]| constraints to the receiver.
 */
- (void)addHorizontalConstraintsToFillWithView:(NSView *)view;
- (void)addHorizontalConstraintsToFillWithView:(NSView *)view options:(NSLayoutFormatOptions)options metrics:(NSDictionary *)metrics;
/**
 Add V:|[view]| constraints to the receiver.
 */
- (void)addVerticalConstraintsToFillWithView:(NSView *)view;
- (void)addVerticalConstraintsToFillWithView:(NSView *)view options:(NSLayoutFormatOptions)options metrics:(NSDictionary *)metrics;

- (NSArray *)constraintsAffectingView:(NSView *)affectedView;
- (NSArray *)constraintsAffectingView:(NSView *)affectedView attribute:(NSLayoutAttribute)attribute;

/**
 Adds a view as subview to the receiver with the given constraints.
 
 This will also check the `translatesAutoresizingMaskIntoConstraints` property
 of the view and sets it to `NO` if necessary as autoresizing masks do not work
 well with Auto Layout.
 
 Use this method for adding subviews when using Auto Layout.
 */

- (void)addSubviewWithAutoresizeConstraints:(NSView *)view;
- (void)addSubviewWithAutoresizeConstraints:(NSView *)view positioned:(NSWindowOrderingMode)place relativeTo:(NSView *)otherView;

- (void)addSubview:(NSView *)view withConstraints:(NSArray *)constraints;
- (void)addSubview:(NSView *)view positioned:(NSWindowOrderingMode)place relativeTo:(NSView *)otherView withConstraints:(NSArray *)constraints;

- (void)setSubviews:(NSArray *)views withConstraints:(NSArray *)constraints;

@end
