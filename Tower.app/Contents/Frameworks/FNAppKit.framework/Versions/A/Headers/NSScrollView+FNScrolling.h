//
//  NSScrollView+FNScrolling.h
//  FNAppKit
//
//  Created by Alexander Rinass on 23.09.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSScrollView (FNScrolling)

- (BOOL)isScrollingHorizontally;
- (BOOL)isScrollingVertically;

@end
