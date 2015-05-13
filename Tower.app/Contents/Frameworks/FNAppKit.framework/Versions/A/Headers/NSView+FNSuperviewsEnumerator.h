//
//  NSView+FNSuperviewsEnumerator.h
//  FNAppKit
//
//  Created by Alexander Rinass on 22/10/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSView (FNSuperviewsEnumerator)

- (void)enumerateSuperviewsUsingBlock:(void (^)(NSView *superview, BOOL *stop))block;

@end
