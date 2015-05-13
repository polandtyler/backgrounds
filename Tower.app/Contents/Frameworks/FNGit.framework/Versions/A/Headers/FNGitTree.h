//
//  FNGitTree.h
//  FNGit
//
//  Created by Alexander Rinass on 14.01.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitObject.h"
#import "FNGitTreeIsh.h"

@class FNGitTreeEntry;
@interface FNGitTree : FNGitObject <FNGitTreeIsh>
@property (nonatomic, readonly) NSString *treeHash;
@property (nonatomic, readonly) NSString *shortTreeHash;
@property (nonatomic, readonly) NSString *revision;
@property (nonatomic, readonly) NSString *filePath;
@property (nonatomic, readonly) NSArray *entries;

#pragma mark - Retrieving Tree Entries For a Repository

/**
 Convenience method for the same method in `FNGitTreeEntry`.
 */
+ (NSArray *)allTreeEntriesForTreeHash:(NSString *)treeHash repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/**
 Convenience method for the same method in `FNGitTreeEntry`.
 */
+ (NSArray *)allTreeEntriesForRevision:(NSString *)revision filePath:(NSString *)filePath repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (NSArray *)allTreeEntriesForRevision:(NSString *)revision filePath:(NSString *)filePath repository:(FNGitRepository *)repository options:(FNGitTreeOptions)options error:(NSError * __autoreleasing *)error;

/**
 Convenience method for the same method in `FNGitTreeEntry`.
 */
+ (FNGitTreeEntry *)treeEntryForRevision:(NSString *)revision filePath:(NSString *)filePath repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Retrieving a Tree For a Repository

/**
 Returns the root tree for the given revision in the given repository or nil on error.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
+ (id)rootTreeForRevision:(NSString *)revision repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/**
 Retrieves the tree for the given revision and filePath in the given repository or nil on error.
 
 If the file path argument does not point to a directory, an error will be returned.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
+ (id)treeForRevision:(NSString *)revision filePath:(NSString *)filePath repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/**
 Retrieves the tree for the given tree hash in the given repository or nil on error.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
+ (id)treeForTreeHash:(NSString *)treeHash repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)treeWithRepository:(FNGitRepository *)repository treeHash:(NSString *)treeHash entries:(NSArray *)treeEntries;
+ (id)treeWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePath:(NSString *)filePath entries:(NSArray *)treeEntries;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository treeHash:(NSString *)treeHash revision:(NSString *)revision filePath:(NSString *)filePath entries:(NSArray *)treeEntries;

@end
