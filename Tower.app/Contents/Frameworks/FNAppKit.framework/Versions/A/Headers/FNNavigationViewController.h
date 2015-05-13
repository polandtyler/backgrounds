//
//  FNNavigationViewController.h
//  FNAppKit
//
//  Created by Alexander Rinass on 09.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import "FNViewController.h"
#import "FNNavigationViewControllerDelegate.h"
#import "FNNavigationBarDelegate.h"

extern NSString *const FNNavigationViewControllerDidPushViewControllerNotification;
extern NSString *const FNNavigationViewControllerDidPopViewControllerNotification;

typedef NS_ENUM(NSInteger, FNNavigationTransitionStyle) {
    FNNavigationTransitionStyleSlide,
    FNNavigationTransitionStyleStack,
    FNNavigationTransitionStyleDefault = FNNavigationTransitionStyleSlide
};

@class FNNavigationBar;
@interface FNNavigationViewController : FNViewController <FNNavigationBarDelegate>

/** @name Creating Navigation Controllers */

- (id)initWithRootViewController:(FNViewController *)rootViewController;

/** @name Accessing Items on the Navigation Stack */

- (NSArray *)viewControllers;
- (void)setViewControllers:(NSArray *)viewControllers animated:(BOOL)animated;

@property (nonatomic, readonly) FNViewController *rootViewController;
@property (nonatomic, readonly) FNViewController *topViewController;

/** @name Pushing and Popping Stack Items */

- (void)pushViewController:(FNViewController *)viewController animated:(BOOL)animated;
- (void)popViewControllerAnimated:(BOOL)animated;
- (void)popToRootViewControllerAnimated:(BOOL)animated;
- (void)popToViewController:(FNViewController *)viewController animated:(BOOL)animated;

/** @name Configuring Navigation Bars */

@property (nonatomic, readonly) FNNavigationBar *navigationBar;

/** @name Accessing the Delegate */

@property (nonatomic, weak) id<FNNavigationViewControllerDelegate> delegate;

@property (nonatomic) FNNavigationTransitionStyle transitionStyle;
@property (nonatomic) BOOL navigationBarHidden;

- (void)updateNavigationItems;

@end
