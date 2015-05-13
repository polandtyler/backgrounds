//
//  NSApplication+FNCommonDirectories.h
//  Tower
//
//  Created by Alexander Rinass on 27.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSApplication (FNCommonDirectories)

+ (NSURL *)applicationDirectory;
+ (NSURL *)applicationSupportDirectory;
+ (NSURL *)cachesDirectory;
+ (NSURL *)applicationLogsDirectory;
+ (NSURL *)localApplicationSupportDirectory;

@end
