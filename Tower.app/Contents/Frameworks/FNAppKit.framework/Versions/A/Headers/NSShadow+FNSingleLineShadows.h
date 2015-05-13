//
//  NSShadow+FNSingleLineShadows.h
//  FNAppKit
//
//  Created by Florian Bürger on 8/1/12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

// Cheers, Matt Gallagher - http://cocoawithlove.com/2011/01/advanced-drawing-using-appkit.html

#import <AppKit/AppKit.h>

@interface NSShadow (FNSingleLineShadows)

+ (NSShadow *)shadowWithOffset:(NSSize)offset blurRadius:(CGFloat)radius color:(NSColor *)shadowColor;
+ (void)setShadowWithOffset:(NSSize)offset blurRadius:(CGFloat)radius color:(NSColor *)shadowColor;
+ (void)clearShadow;

@end
