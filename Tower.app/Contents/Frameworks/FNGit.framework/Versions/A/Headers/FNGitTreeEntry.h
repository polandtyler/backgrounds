//
//  FNGitTreeEntry.h
//  FNGit
//
//  Created by Alexander Rinass on 20.05.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitFileEntry.h"

@class FNGitRepository;
@class FNGitTree;
@class FNGitBlob;
@interface FNGitTreeEntry : FNGitFileEntry
@property (nonatomic, readonly) FNGitObjectType objectType;
@property (nonatomic, readonly) NSUInteger fileSize;
@property (nonatomic, readonly) BOOL isTreeObject;
@property (nonatomic, readonly) BOOL isBlobObject;
@property (nonatomic, readonly) BOOL isCommitObject; // for submodules

#pragma mark - Retrieving Tree Entries

/**
 Returns all tree entries for the given revision and file path.
 
 Note that all tree entries will contain the full file path, e.g. if you pass `HEAD` as revision
 and `src/git` as file path, a file entry `defines.h` will contain the full path `src/git/defines.h`.
 
 If the file path argument does not point to a directory, an error will be returned.
 
 If any error occurs, `nil` will be returned and the passed error reference will contain detailed
 information about the error. 
 */
+ (NSArray *)allTreeEntriesForRevision:(NSString *)revision filePath:(NSString *)filePath repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (NSArray *)allTreeEntriesForRevision:(NSString *)revision filePath:(NSString *)filePath repository:(FNGitRepository *)repository options:(FNGitTreeOptions)options error:(NSError * __autoreleasing *)error;

/**
 Returns all tree entries for the given revision and file path.
 
 Note that all tree entries for the tree will contain only the file name and not the full path! 
 This is because a tree object does not know anything about parent trees and thus does not know it
 parent path (nor do the entries).
 
 If any error occurs, `nil` will be returned and the passed error reference will contain detailed
 information about the error. 
 */
+ (NSArray *)allTreeEntriesForTreeHash:(NSString *)treeHash repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/**
 Returns a single tree entry for the given revision and file path.
 
 If any error occurs, `nil` will be returned and the passed error reference will contain detailed
 information about the error. 
 */
+ (FNGitTreeEntry *)treeEntryForRevision:(NSString *)revision filePath:(NSString *)filePath repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)treeEntryWithRepository:(FNGitRepository *)repository
					 filePath:(NSString *)filePath
				   objectType:(FNGitObjectType)objectType
				   objectHash:(NSString *)objectHash
					 fileMode:(FNGitFileMode)fileMode
					 fileSize:(NSUInteger)fileSizeInBytes;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository
				filePath:(NSString *)filePath
			  objectType:(FNGitObjectType)objectType
			  objectHash:(NSString *)objectHash
				fileMode:(FNGitFileMode)fileMode
				fileSize:(NSUInteger)fileSizeInBytes;

#pragma mark - Retrieving the Git Object of the Entry

/**
 Returns the associated Git tree object for this file entry.
 
 If the entry is not a tree object, nil will be returned with error set to `nil`.
 
 If any other error occurs, `nil` will be returned and the passed error reference will contain detailed
 information about the error. 
 */
- (FNGitTree *)treeObject:(NSError * __autoreleasing *)error;

/**
 Returns the associated Git blob object for this file entry.
 
 If the entry is not a blob object, nil will be returned with error set to `nil`.
 
 If any other error occurs, `nil` will be returned and the passed error reference will contain detailed
 information about the error. 
 */
- (FNGitBlob *)blobObject:(NSError * __autoreleasing *)error;

#pragma mark - Comparing to Another Tree Entry

- (BOOL)isEqualToTreeEntry:(FNGitTreeEntry *)object;

@end
