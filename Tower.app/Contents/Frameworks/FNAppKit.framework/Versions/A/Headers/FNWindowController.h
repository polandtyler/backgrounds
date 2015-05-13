//
//  FNWindowController.h
//  FNAppKit
//
//  Created by Alexander Rinass on 20.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface FNWindowController : NSWindowController
@property (nonatomic, readonly, getter = isRunningModal) BOOL runningModal;
@property (nonatomic, readonly) NSModalSession modalSession;
@property (nonatomic, readonly) NSInteger modalSessionStatus;

/** @name Creating FNWindowController Objects */

/**
 Returns the default nib name for this window controller.

 The default implementation returns the class name of the window controller.
 Subclasses can override this method to provide another nib name.

 The default nib name will be used in the `init` method to pair a window
 controller with a nib file by passing it to `initWithWindowNibName:owner:`.

 If the window controller does not use a nib file, override this method and return
 `nil`.
 */
+ (NSString *)defaultNibName;

/**
 Creates a window controller object by calling init, which will pair the window
 controller with its default nib file (see `defaultNibName`).
 */
+ (id)controller;

/** @name Initialization */

/**
 Common initializer that is called regardless of wether the window controller
 was loaded from a nib file or created programmatically.

 Use this method to initialize instance variables. If you want to perform
 additional initialization on views, use `windowDidLoad`.
 */
- (void)commonInit;

/** @name Running the Dialogue as Sheet */

- (void)beginSheetModalForWindow:(NSWindow *)targetWindow completion:(void (^)(NSWindow *sheet, NSInteger returnCode, void *context))completion;
- (void)beginSheetModalForWindow:(NSWindow *)targetWindow contextInfo:(void *)contextInfo completion:(void (^)(NSWindow *sheet, NSInteger returnCode, void *contextInfo))completion;

/** @name Running the Dialogue as Modal Window */

- (NSInteger)runModal;
- (void)stopModalWithCode:(NSInteger)returnCode;

@end
