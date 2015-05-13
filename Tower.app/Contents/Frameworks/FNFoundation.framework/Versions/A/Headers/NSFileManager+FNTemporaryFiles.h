//
//  NSFileManager+FNTemporaryFiles.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSFileManager (FNTemporaryFiles)

#pragma mark - Creating Temporary Directories

/* @name Creating Temporary Directories */

/**
 Creates a unique directory URL in the NSTemporaryDirectory space but does not create
 the directory.
 
 @return A unique directory URL that is not created yet. 
 */
- (NSURL *)temporaryDirectoryURL;

/**
 Creates a unique directory path in the NSTemporaryDirectory space but does not create
 the directory.
 
 @return A unique directory path that is not created yet.
 */
- (NSString *)temporaryDirectoryPath;

/**
 Creates a unique directory in the NSTemporaryDirectory space.
 
 @return The URL to the temporary directory.
 */
- (NSURL *)createTemporaryDirectory:(NSError * __autoreleasing *)error;

#pragma mark - Creating Temporary Files

/* @name Creating Temporary Files */

/**
 Creates a unique file URL in the NSTemporaryDirectory space but does not create
 the file.
 
 @return A unique file URL that is not created yet.
 */
- (NSURL *)temporaryFileURL;

/**
 Creates a unique file URL with the given extension in the NSTemporaryDirectory space but does 
 not create the file.
 
 @return A unique file URL that is not created yet.
 */
- (NSURL *)temporaryFileURLWithExtension:(NSString *)fileExtension;

/**
 Creates a unique file path in the NSTemporaryDirectory space but does not create
 the file.
 
 @return A unique file path that is not created yet.
 */
- (NSString *)temporaryFilePath;

/**
 Creates a unique file path with the given extension in the NSTemporaryDirectory space but does
 not create the file.
 
 @return A unique file path that is not created yet.
 */
- (NSString *)temporaryFilePathWithExtension:(NSString *)fileExtension;

/**
 Creates a unique file path in the NSTemporaryDirectory space.
 
 @return The URL to the temporary file.
 */
- (NSURL *)createTemporaryFileWithContents:(NSData *)data error:(NSError * __autoreleasing *)error;

/**
 Creates a unique file with the given extension in the NSTemporaryDirectory space.
 
 @return The URL to the temporary file.
 */
- (NSURL *)createTemporaryFileWithExtension:(NSString *)fileExtension contents:(NSData *)data error:(NSError * __autoreleasing *)error;

@end
