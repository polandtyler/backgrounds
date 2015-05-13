//
//  NSColor+FNCGColorSupport.h
//  FNAppKit
//
//  Created by Florian Bürger on 27/08/2012.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSColor (FNCGColorSupport)

- (CGColorRef)fn_CGColor;
+ (NSColor *)fn_colorWithCGColor:(CGColorRef)CGColor;

@end
