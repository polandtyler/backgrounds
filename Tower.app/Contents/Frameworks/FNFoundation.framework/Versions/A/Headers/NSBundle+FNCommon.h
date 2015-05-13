//
//  NSBundle+FNCommon.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 23.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSBundle (FNCommon)

- (NSString *)bundleName;
- (NSString *)bundleVersion;
- (NSString *)bundleShortVersion;

@end
