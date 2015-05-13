//
//  NSWorkspace+FNLaunchServices.h
//  FNAppKit
//
//  Created by Alexander Rinass on 17/06/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSWorkspace (FNLaunchServices)

/** @name Querying Applications for URL Schemes */

- (NSArray *)allApplicationsForURLScheme:(NSString *)urlScheme;

/** @name Managing Default Application for URL Schemes */

- (NSString *)defaultApplicationForURLScheme:(NSString *)urlScheme;
- (BOOL)setDefaultApplication:(NSString *)bundleIdentifier forURLScheme:(NSString *)urlScheme;
- (BOOL)isApplication:(NSString *)bundleIdentifier defaultHandlerForURLScheme:(NSString *)urlScheme;

@end
