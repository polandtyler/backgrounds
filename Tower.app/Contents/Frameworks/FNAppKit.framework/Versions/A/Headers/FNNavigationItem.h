//
//  FNNavigationBarInfo.h
//  FNAppKit
//
//  Created by Alexander Rinass on 10.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol FNNavigationItemDelegate;
@interface FNNavigationItem : NSObject
@property (nonatomic, weak) id<FNNavigationItemDelegate> delegate;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *prompt;
@property (nonatomic) NSImage *image;

/** @name Creating Navigation Items */

- (id)initWithTitle:(NSString *)title;

/** @name Customizing Views */

/**
 An array of views that will be placed at the left side of the navigation bar.
 
 If the items are identical to the ones of the previous navigation item, no
 replacement will happen.
 */
@property (nonatomic, copy) NSArray *leftBarItems;

/**
 A Boolean value indicating whether the left items are displayed in addition
 to the current left items.
 */
@property (nonatomic) BOOL leftItemsSupplementCurrentItems;

/**
 An array of views that will be placed at the right side of the navigation bar.
 
 If the items are identical to the ones of the previous navigation item, no
 replacement will happen.
 */
@property (nonatomic, copy) NSArray *rightBarItems;

/**
 A Boolean value indicating whether the right items are displayed in addition
 to the current right items.
 */
@property (nonatomic) BOOL rightItemsSupplementCurrentItems;

/**
 Updates the left bar items.
 */
- (void)setLeftBarItems:(NSArray *)leftBarItems animated:(BOOL)animated;

/**
 Updates the right bar items.
 */
- (void)setRightBarItems:(NSArray *)rightBarItems animated:(BOOL)animated;

@end
