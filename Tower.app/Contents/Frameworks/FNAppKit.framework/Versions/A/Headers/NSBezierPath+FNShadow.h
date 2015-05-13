//
//  NSBezierPath+FNShadow.h
//  FNAppKit
//
//  Created by Alexander Rinass on 21.03.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSBezierPath (FNShadow)

- (void)fillPathWithInnerShadow:(NSShadow *)shadow;

@end
