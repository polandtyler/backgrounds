//
//  NSMenu+FNAppKit.h
//  FNAppKit
//
//  Created by Florian Bürger on 21/08/2012.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSMenu (FNAppKit)

//
//  Convenience methods to quickly add NSMenuItems to the menu
//
- (NSMenuItem *)addItemWithTitle:(NSString *)title action:(SEL)action; // target = nil
- (NSMenuItem *)addItemWithTitle:(NSString *)title action:(SEL)action target:(id)target; // representedObject = nil
- (NSMenuItem *)addItemWithTitle:(NSString *)title action:(SEL)action target:(id)target representedObject:(id)object;

- (void)addItems:(NSArray *)items;

//
//  Set the target for all menu items.
//  Can walk all submenus as well and set the target.
//
- (void)setTarget:(id)target recursiveForSubmenus:(BOOL)recursive;

@end
