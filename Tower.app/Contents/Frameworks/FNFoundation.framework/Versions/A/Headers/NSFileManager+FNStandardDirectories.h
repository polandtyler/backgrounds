//
//  NSFileManager+FNStandardDirectories.h
//  FNFoundation
//
//  Created by Alexander Rinass on 30/06/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSFileManager (FNStandardDirectories)

- (NSURL *)applicationSupportDirectory;
- (NSURL *)cachesDirectory;

@end
