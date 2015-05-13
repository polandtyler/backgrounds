//
//  FNMasterDetailViewController.h
//  FNAppKit
//
//  Created by Alexander Rinass on 06.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

/**
 The `FNMasterDetailViewController` is a view controller, that helps with 
 master-detail views. It simply manages a `NSSplitView` that has two views.
 
 The master view is the left view and usually contains some sort of list.
 The detail view is the rigt view and shows the detailed content of the selected
 item on behalf of the master view.
 
 How master and detail view communicate with each other is not part of this 
 view controller. It merely helps with setting master and detail view 
 controllers and their respective views. 
 */

#import "FNViewController.h"

@interface FNMasterDetailViewController : FNViewController
@property (nonatomic, readonly) NSSplitView *splitView;

/** @name Managing Master and Detail View Controllers */

/**
 Returns the current master view controller.
 
 @return The current master view controller
 */
- (NSViewController *)masterViewController;

/**
 Sets the master view controller and places its view into the master view 
 (left).
 
 If the master view controller did not change, this method will do nothing.
 The existing master view controller and its view will be properly removed.
 
 Passing `nil` for masterViewController will insert an empty `NSView`.
 
 @param masterViewController The new master view controller
 */
- (void)setMasterViewController:(NSViewController *)masterViewController;

/**
 Returns the current detail view controller.
 
 @return The current detail view controller
 */
- (NSViewController *)detailViewController;

/**
 Sets the detail view controller and places its view into the detail view
 (right).
 
 If the detail view controller did not change, this method will do nothing.
 The existing detail view controller and its view will be properly removed.
 
 Passing `nil` for detailViewController will insert an empty `NSView`.
 
 @param detailViewController The new detail view controller
 */
- (void)setDetailViewController:(NSViewController *)detailViewController;

@end
