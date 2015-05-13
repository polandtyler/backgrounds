//
//  NSApplication+FNMainBundleInfo.h
//  FNAppKit
//
//  Created by Alexander Rinass on 21.03.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSApplication (FNMainBundleInfo)

+ (NSString *)productName;
+ (NSString *)productIdentifier;
+ (NSString *)productVersion;
+ (NSString *)productShortVersionString;
+ (NSString *)productFullVersionString;

@end
