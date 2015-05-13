//
//  NSEvent+FNKeyEquivalents.h
//  FNAppKit
//
//  Created by Alexander Rinass on 25/04/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>

static unsigned short const FNEventKeyCodeSpaceKey = kVK_Space;
static unsigned short const FNEventKeyCodeBackspaceKey =  kVK_Delete;
static unsigned short const FNEventKeyCodeEnterKey = kVK_ANSI_KeypadEnter;
static unsigned short const FNEventKeyCodeReturnKey =  kVK_Return;

@interface NSEvent (FNKeyEquivalents)

+ (BOOL)isAlternateKeyDown;
+ (BOOL)isCommandKeyDown;
+ (BOOL)isControlKeyDown;
+ (BOOL)isShiftKeyDown;
- (BOOL)isAlternateKeyDown;
- (BOOL)isCommandKeyDown;
- (BOOL)isControlKeyDown;
- (BOOL)isShiftKeyDown;

- (BOOL)isKeyCodeDown:(unsigned short)keyCode withModifierMask:(NSUInteger)modifierMask;
- (BOOL)isKeyEquivalentDown:(NSString *)keyEquivalent withModifierMask:(NSUInteger)modifierMask;

@end
