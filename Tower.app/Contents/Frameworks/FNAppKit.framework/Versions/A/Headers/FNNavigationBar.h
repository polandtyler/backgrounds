//
//  FNNavigationBar.h
//  FNAppKit
//
//  Created by Alexander Rinass on 09.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import "FNView.h"
#import "FNViewAppearance.h"
#import "FNNavigationBarDelegate.h"

extern NSString *const FNNavigationBarDidChangeAppearanceNotification;

@class FNNavigationItem;
@class FNNavigationBarAppearance;
@interface FNNavigationBar : NSView <FNViewAppearance>
@property (nonatomic, weak) id<FNNavigationBarDelegate> delegate;
@property (nonatomic, readonly) NSArray *items;
@property (nonatomic, readonly) FNNavigationItem *topItem;
@property (nonatomic) NSImage *backgroundImage;
@property (nonatomic) NSGradient *backgroundGradient;
@property (nonatomic) NSShadow *bottomShadow;
@property (nonatomic) CGFloat bottomShadowHeight;
@property (nonatomic) CGFloat barHeight;
@property (nonatomic) NSColor *topBorderColor;
@property (nonatomic) NSColor *bottomBorderColor;
@property (nonatomic) BOOL displayTopBorder;
@property (nonatomic) BOOL displayBottomBorder;

/** @name Pushing and Popping Items */

- (void)pushNavigationItem:(FNNavigationItem *)item animated:(BOOL)animated;
- (FNNavigationItem *)popNavigationItemAnimated:(BOOL)animated;
- (void)setItems:(NSArray *)items animated:(BOOL)animated;

/** @name Enabling and Disabling Navigation Bar Items */

/**
 This will trigger update methods for all visible items of the navigation bar
 that conform to the `FNValidatedNavigationBarItem` protocol.
 
 Note that this method needs to be called manually as there is no general way
 of determining when navigation bar items need to be updated in an application.
 */
- (void)update;

/** @name Reloading the properties in appearance */
- (void)reloadAppearanceProperties;

@end
