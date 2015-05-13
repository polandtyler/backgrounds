//
//  NSBezierPath+FNQuartzPath.h
//  FNAppKit
//
//  Created by Florian Bürger on 8/2/12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSBezierPath (FNQuartzPath)

- (CGPathRef)quartzPath;

@end
