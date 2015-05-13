//
//  FNGitBlob.h
//  FNGit
//
//  Created by Alexander Rinass on 14.01.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitObject.h"

@class FNGitRepository;
@interface FNGitBlob : FNGitObject
@property (nonatomic, readonly) NSString *blobHash;
@property (nonatomic, readonly) NSString *revision;
@property (nonatomic, readonly) NSString *filePath;
@property (nonatomic, readonly) NSData *contents;
@property (nonatomic, readonly) NSUInteger size;	

#pragma mark - Loading a Blob From a Repository

/**
 Returns the blob for the given object hash or `nil` on error.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
+ (id)blobForHash:(NSString *)blobHash repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/**
 Returns the blob for the given revision and path or `nil` on error.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
+ (id)blobForRevision:(NSString *)revision filePath:(NSString *)filePath repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/**
 Creates and returns the blob with the current contents at the given file path or `nil` on error.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
+ (id)blobForCurrentFileAtPath:(NSString *)filePath repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)blobWithRepository:(FNGitRepository *)repository filePath:(NSString *)filePath contents:(NSData *)contents;
+ (id)blobWithRepository:(FNGitRepository *)repository blobHash:(NSString *)blobHash contents:(NSData *)contents;
+ (id)blobWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePath:(NSString *)filePath contents:(NSData *)contents;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository blobHash:(NSString *)blobHash revision:(NSString *)revision filePath:(NSString *)filePath contents:(NSData *)contents;

#pragma mark - Comparing to Another Blob

- (BOOL)isEqualToBlob:(FNGitBlob *)object;

@end
