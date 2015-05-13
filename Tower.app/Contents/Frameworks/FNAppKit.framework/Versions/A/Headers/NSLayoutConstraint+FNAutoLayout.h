//
//  NSLayoutConstraint+FNAutoLayout.h
//  FNAppKit
//
//  Created by Alexander Rinass on 23/09/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSLayoutConstraint (FNAutoLayout)

+ (NSArray *)autoresizeConstraintsForView:(NSView *)view;
+ (NSArray *)autoresizeXConstraintsForView:(NSView *)view;
+ (NSArray *)autoresizeYConstraintsForView:(NSView *)view;
+ (NSLayoutConstraint *)centerXConstraintForView:(NSView *)view inView:(NSView *)otherView;
+ (NSLayoutConstraint *)centerYConstraintForView:(NSView *)view inView:(NSView *)otherView;
+ (NSLayoutConstraint *)baselineConstraintForView:(NSView *)view otherView:(NSView *)otherView;

@end
