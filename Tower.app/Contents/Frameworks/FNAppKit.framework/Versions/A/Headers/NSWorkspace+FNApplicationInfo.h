//
//  NSWorkspace+FNApplicationName.h
//  FNAppKit
//
//  Created by Alexander Rinass on 17/06/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSWorkspace (FNApplicationName)

- (NSString *)applicationVersionForApplicationWithBundleIdentifier:(NSString *)bundleIdentifier;
- (NSString *)applicationNameForApplicationWithBundleIdentifier:(NSString *)bundleIdentifier;

@end
