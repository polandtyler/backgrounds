//
//  NSFileManager+FNAuthorizedFileOperations.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 22.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSFileManager (FNAuthorizedFileOperations)

- (BOOL)authorizedMovePath:(NSString *)source toPath:(NSString *)destination;
- (BOOL)authorizedCopyPath:(NSString *)source toPath:(NSString *)destination;
- (BOOL)authorizedMakeDirectory:(NSString *)path;

@end
