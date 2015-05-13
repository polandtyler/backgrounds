//
//  FNNavigationViewControllerDelegate.h
//  FNAppKit
//
//  Created by Alexander Rinass on 10.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNViewController;
@class FNNavigationViewController;
@protocol FNNavigationViewControllerDelegate <NSObject>
@optional

/**
 Sent to the receiver just before the navigation controller displays a view controller’s view and navigation item properties.
 */
- (void)navigationViewController:(FNNavigationViewController *)navigationViewController willShowViewController:(FNViewController *)viewController animated:(BOOL)animated;

/**
 Sent to the receiver just after the navigation controller displays a view controller’s view and navigation item properties.
 */
- (void)navigationViewController:(FNNavigationViewController *)navigationViewController didShowViewController:(FNViewController *)viewController animated:(BOOL)animated;


- (void)navigationViewControllerDidUpdateNavigationItems:(FNNavigationViewController *)navigationViewController;

@end
