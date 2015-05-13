//
//  NSFileManager+FNFoundation.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 23.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSFileManager (FNFoundation)

#pragma mark - Validating File Paths

- (BOOL)isEmptyDirectoryAtPath:(NSString *)aDirectoryPath error:(NSError **)error;

#pragma mark - Working with Volumes

- (NSString *)volumePathForFileAtPath:(NSString *)aFilePath;

@end
