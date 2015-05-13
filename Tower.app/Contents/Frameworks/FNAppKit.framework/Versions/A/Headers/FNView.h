//
//  FNView.h
//  FNAppKit
//
//  Created by Florian Bürger on 08/10/2012.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class FNViewController;
@interface FNView : NSView

/** @name Initialization */

- (void)commonInit;

/** @name Supporting Tags */

- (void)setTag:(NSInteger)tag;

/** @name Integrating View Controllers Into the Responder Chain */

/**
 If this is your view controllers's view, connect this outlet in nib files with
 the view controller or set this property programmatically to integrate the view
 controller into the responder chain.

 The view controller will also receive view events from this view, such as
 `viewWillAppear`, `viewDidAppear`, `viewWillDisappear` and `viewDidDisappear`.
 */
@property (nonatomic, weak) IBOutlet FNViewController *viewController;

@end
