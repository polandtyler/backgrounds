//
//  NSView+FNActive.h
//  FNAppKit
//
//  Created by Alexander Rinass on 04/02/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSView (FNActive)
@property (atomic, readonly, getter=isActive) BOOL active;
@end
