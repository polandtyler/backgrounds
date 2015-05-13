//
//  NSButton+FNBorderlessButton.h
//  FNAppKit
//
//  Created by Florian Bürger on 8/10/12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSButton (FNBorderlessButton)

+ (id)borderlessButtonWithImage:(NSImage *)image;
+ (id)borderlessButtonWithImage:(NSImage *)image target:(id)target action:(SEL)action;

@end
