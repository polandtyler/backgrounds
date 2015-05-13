//
//  NSMenuItem+FNFactories.h
//  FNAppKit
//
//  Created by Alexander Rinass on 09.08.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSMenuItem (FNFactories)

+ (instancetype)itemWithTitle:(NSString *)title action:(SEL)action;

+ (instancetype)itemWithURL:(NSURL *)url;
+ (instancetype)itemWithApplication:(NSString *)application;

@end
