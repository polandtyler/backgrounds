//
//  NSColor+FNHexString.h
//  FNAppKit
//
//  Created by Alexander Rinass on 08.07.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSColor (FNHexString)

+ (NSColor *)colorWithHexString:(NSString *)hexString alpha:(CGFloat)alphaValue;

- (NSString *)hexString;

@end
