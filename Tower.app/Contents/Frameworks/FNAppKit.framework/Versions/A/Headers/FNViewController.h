//
//  FNViewController.h
//  FNAppKit
//
//  Created by Florian Bürger on 14/08/2012.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class FNNavigationViewController;
@class FNNavigationItem;
@interface FNViewController : NSViewController

/** @name Creating FNViewController Objects */

/**
 Returns the default nib name for this view controller.
 
 The default implementation returns the class name of the view controller. 
 Subclasses can override this method to provide another nib name.
 
 The default nib name will be used in the `init` method to pair a view 
 controller with a nib file by passing it to `initWithNibName:bundle:`.
 
 If the view controller does not use a nib file, override this method and return
 `nil`.
 */
+ (NSString *)defaultNibName;

/**
 Creates a view controller object by calling init, which will pair the view
 controller with its default nib file (see `defaultNibName`).
 */
+ (id)controller;

/** @name Initialization */

/**
 Common initializer that is called regardless of wether the view controller
 was loaded from a nib file or created programmatically.
 
 Use this method to initialize instance variables. If you want to perform
 additional initialization on views, use `viewDidLoad`.
 */
- (void)commonInit;

/** @name Managing the View */

/**
 Called after the controller’s view is loaded into memory.
 
 This method is called after the view controller has loaded its view hierarchy
 into memory. This method is called regardless of whether the view hierarchy 
 was loaded from a nib file or created programmatically in the loadView method.
 
 You usually override this method to perform additional initialization on views 
 that were loaded from nib files. 
 
 Use this method over `awakeFromNib` as `awakeFromNib` can be called multiple
 times for view controllers that manage table or outline views.
 */
- (void)viewDidLoad;

/** @name Responding to View Events */

/**
 Notifies the view controller that its view is about to be added to a view 
 hierarchy and will be displayed in a window.
 */
- (void)viewWillAppear;

/**
 Notifies the view controller that its view was added to a view hierarchy and
 belongs to a window.
 */
- (void)viewDidAppear;

/**
 Notifies the view controller that its view is about to be removed from a view 
 hierarchy.
 */
- (void)viewWillDisappear;

/**
 Notifies the view controller that its view was removed from a view hierarchy.
 */
- (void)viewDidDisappear;

/** @name Managing Controller State */

/**
 
 */
@property (nonatomic) BOOL needsUpdate;

- (void)update;
- (void)updateIfNeeded;

/** @name Getting Other Related View Controllers */

/**
 The parent view controller of the recipient.
 
 If the recipient is a child of a container view controller, this property holds
 the view controller it is contained in. If the recipient has no parent, the
 value in this property is `nil`.
 */
@property (nonatomic, weak, readonly) FNViewController *parentViewController;

/**
 The nearest ancestor in the view controller hierarchy that is a navigation 
 view controller.
 */
@property (nonatomic, readonly) FNNavigationViewController *navigationViewController;

/** @name Configuring a Navigation Interface */

/**
 The navigation item used to represent the view controller in a parent’s
 navigation bar.

 This is a unique instance of UINavigationItem created to represent the view
 controller when it is pushed onto a navigation controller.

 The first time the property is accessed, the FNNavigationItem object is
 created. Therefore, you shouldn’t access this property if you are not using a
 navigation controller to display the view controller. To ensure the navigation
 item is configured, you can either override this property and add code to
 create the bar button items when first accessed or create the items in your
 view controller’s initialization code.
 */
@property (nonatomic, readonly) FNNavigationItem *navigationItem;

/** @name Managing Child View Controllers */

/**
 An array of the view controllers that are the children of the receiver in the 
 view controller hierarchy.
 */
@property (nonatomic, readonly) NSArray *childViewControllers;

/**
 Adds the given view controller as a child.
 */
- (void)addChildViewController:(FNViewController *)childViewController;

/**
 Removes the given child view controller.
 */
- (void)removeChildViewController:(FNViewController *)childViewController;

/**
 Removes the receiver from its parent in the view controller hierarchy.
 */
- (void)removeFromParentViewController;

@end
