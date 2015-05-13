//
//  FNGitChangeset.h
//  FNGit
//
//  Created by Alexander Rinass on 05.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitDiffSettings.h"

@class FNGitRepository;
@class FNGitDiff;
@class FNGitChangesetEntry;
@interface FNGitChangeset : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSArray *entries;
@property (nonatomic, readonly) NSUInteger totalFilesChanged;
@property (nonatomic, readonly) NSUInteger totalLinesChanged;
@property (nonatomic, readonly) NSUInteger totalLinesAdded;
@property (nonatomic, readonly) NSUInteger totalLinesDeleted;

/** @name Getting Changesets */

/**
 Retrieves a changeset by comparing the given revision with its direct
 ancestor(s).
 */
+ (id)changesetByComparingRevisionWithAncestorForRevision:(NSString *)revision filePaths:(NSArray *)filePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Retrieves a changeset by comparing two distinct revisions.
 */
+ (id)changesetByComparingRevisions:(NSArray *)revisions forFilePaths:(NSArray *)filePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Retrieves a changeset by comparing the working tree with the index.
 */
+ (id)changesetByComparingWorkingTreeWithIndexWithForFilePaths:(NSArray *)filePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Retrieves a changeset by comparing the working tree with a given revision.
 */

+ (id)changesetByComparingWorkingTreeWithRevision:(NSString *)revision forFilePaths:(NSArray *)filePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Retrieves a changeset by comparing the index with the base revision
 */
+ (id)changesetByComparingIndexWithBaseForFilePaths:(NSArray *)filePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Retrieves a changeset by comparing the index with a given revision.
 */
+ (id)changesetByComparingIndexWithRevision:(NSString *)revision forFilePaths:(NSArray *)filePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/** @name Getting Changeset Entries */

- (FNGitChangesetEntry *)entryForFilePath:(NSString *)filePath;

/** @name Getting Diffs for Changeset Entries */

- (NSArray *)allDiffs:(NSError * __autoreleasing *)error;
- (FNGitDiff *)diffForEntryWithFilePath:(NSString *)filePath error:(NSError * __autoreleasing *)error;

@end
