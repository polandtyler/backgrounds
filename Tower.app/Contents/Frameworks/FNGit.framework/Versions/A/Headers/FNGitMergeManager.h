//
//  FNGitMergeManager.h
//  FNGit
//
//  Created by Alexander Rinass on 03.09.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitMergeOptions.h"
#import "FNGitRebaseOptions.h"
#import "FNGitCherryPickOptions.h"
#import "FNGitRevertOptions.h"

typedef NS_ENUM(NSUInteger, FNGitMergeMode) {
    FNGitMergeModeNone,
    FNGitMergeModeMerge,
    FNGitMergeModeMergeSquash,
    FNGitMergeModeRebase,
    FNGitMergeModeCherryPick,
    FNGitMergeModeRevert
};

@class FNGitRepository;
@interface FNGitMergeManager : NSObject
@property (nonatomic, readonly) FNGitRepository *repository;

/** @name Creating Merge Manager Objects */

+ (id)mergeManagerWithRepository:(FNGitRepository *)repository;
- (id)initWithRepository:(FNGitRepository *)repository;

/** @name Querying the Merge Status */

- (BOOL)isMerging;
- (FNGitMergeMode)currentMergeMode;
- (NSTimeInterval)mergeTimestamp;

/**
 The original revision on which the merge was started.
 */
- (NSString *)originalRevision;

/**
 The revision that is merged onto the original revision.
 
 For merges, this is the revision that the original HEAD branch was merged with.

 For rebases, this is the revision the original HEAD branch should be rebased
 onto.
 */
- (NSString *)mergedRevision;

/** @name Getting the Merge Commit Message */

- (NSString *)mergeCommitMessage;

/** @name Querying the Merge Sequencer */

/**
 For cherry-pick and revert operaions, this will always return 0 as it is 
 currently not supported.
 */
- (NSUInteger)nextSequenceStep;

/**
 For cherry-pick and revert operaions, this will return the number of revisions
 left to process.
 */
- (NSUInteger)lastSequenceStep;

- (NSString *)nextSequenceRevision;
- (NSString *)lastSequenceRevision;

/** @name Merging Revisions */

- (BOOL)mergeWithRevision:(NSString *)revision options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;
- (BOOL)abortMerge:(NSError * __autoreleasing *)error;

/** @name Rebasing Revisions */

- (BOOL)rebaseWithRevision:(NSString *)revision options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;
- (BOOL)continueRebase:(NSError * __autoreleasing *)error;
- (BOOL)skipRebase:(NSError * __autoreleasing *)error;
- (BOOL)abortRebase:(NSError * __autoreleasing *)error;

/** @name Cherry-Picking Revisions */

- (BOOL)cherryPickRevisions:(NSArray *)revisions options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;
- (BOOL)continueCherryPick:(NSError * __autoreleasing *)error;
- (BOOL)abortCherryPick:(NSError * __autoreleasing *)error;
- (BOOL)quitCherryPick:(NSError * __autoreleasing *)error;

/** @name Reverting Revisions */

- (BOOL)revertRevisions:(NSArray *)revisions options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;
- (BOOL)continueRevert:(NSError * __autoreleasing *)error;
- (BOOL)abortRevert:(NSError * __autoreleasing *)error;
- (BOOL)quitRevert:(NSError * __autoreleasing *)error;

/** @name Resolving File Merge Conflicts */

- (BOOL)canResolveUnmergedFileByAdding:(NSString *)unmergedFilePath;
- (BOOL)resolveUnmergedFileByAdding:(NSString *)unmergedFilePath error:(NSError * __autoreleasing *)error;
- (BOOL)resolveUnmergedFilesByAdding:(NSArray *)unmergedFilePaths error:(NSError * __autoreleasing *)error;

- (BOOL)canResolveUnmergedFileByRemoving:(NSString *)unmergedFilePath;
- (BOOL)resolveUnmergedFileByRemoving:(NSString *)unmergedFilePath error:(NSError * __autoreleasing *)error;
- (BOOL)resolveUnmergedFilesByRemoving:(NSArray *)unmergedFilePaths error:(NSError * __autoreleasing *)error;

- (BOOL)canRestoreAncestorVersionForUnmergedFile:(NSString *)unmergedFilePath;
- (BOOL)restoreAncestorVersionForUnmergedFile:(NSString *)unmergedFilePath error:(NSError * __autoreleasing *)error;
- (BOOL)restoreAncestorVersionForUnmergedFiles:(NSArray *)unmergedFilePaths error:(NSError * __autoreleasing *)error;

- (BOOL)canRestoreOurVersionForUnmergedFile:(NSString *)unmergedFilePath;
- (BOOL)restoreOurVersionForUnmergedFile:(NSString *)unmergedFilePath error:(NSError * __autoreleasing *)error;
- (BOOL)restoreOurVersionForUnmergedFiles:(NSArray *)unmergedFilePaths error:(NSError * __autoreleasing *)error;

- (BOOL)canRestoreTheirVersionForUnmergedFile:(NSString *)unmergedFilePath;
- (BOOL)restoreTheirVersionForUnmergedFile:(NSString *)unmergedFilePath error:(NSError * __autoreleasing *)error;
- (BOOL)restoreTheirVersionForUnmergedFiles:(NSArray *)unmergedFilePaths error:(NSError * __autoreleasing *)error;

- (BOOL)restoreUnmergedVersionForFile:(NSString *)unmergedFilePath error:(NSError * __autoreleasing *)error;
- (BOOL)restoreUnmergedVersionForFiles:(NSArray *)unmergedFilePaths error:(NSError * __autoreleasing *)error;
- (BOOL)restoreUnmergedVersionForFiles:(NSArray *)unmergedFilePaths inDirectory:(NSString *)directoryPath error:(NSError * __autoreleasing *)error;

@end
