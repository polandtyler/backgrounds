//
//  FNGitWorkingTreeManager.h
//  FNGit
//
//  Created by Alexander Rinass on 12.09.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>
#import "FNGitResetCommand.h"
#import "FNGitWorkingTreeEntry.h"

typedef NS_OPTIONS(NSUInteger, FNGitMoveOptions) {
    FNGitMoveDefault = 0,
    FNGitMoveForce = 1UL << 0
};

typedef NS_OPTIONS(NSUInteger, FNGitAddOptions) {
    FNGitAddDefault = 0,
    FNGitAddForce = 1UL << 0
};

typedef NS_OPTIONS(NSUInteger, FNGitCommitOptions) {
    FNGitCommitDefault = 0,
    FNGitCommitAmend = 1UL << 0,
    FNGitCommitSignOff = 1UL << 1
};

@class FNGitRepository;
@class FNGitWorkingTreeEntry;
@interface FNGitWorkingTreeManager : NSObject
@property (nonatomic, readonly) FNGitRepository *repository;

#pragma mark - Factory Methods

+ (id)workingTreeManagerWithRepository:(FNGitRepository *)repository;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository;

#pragma mark - Checking out Revisions

- (BOOL)checkoutRevision:(NSString *)revision error:(NSError * __autoreleasing *)error;

#pragma mark - Resetting the Working Tree

/**
 Resets the working tree (or specific files in it) to the given revision with the given reset mode.
 */
- (BOOL)resetToRevision:(NSString *)revision withMode:(FNGitResetMode)mode filePaths:(NSArray *)filePaths error:(NSError * __autoreleasing *)error;

#pragma mark - Managing File Changes

- (BOOL)stageFiles:(NSArray *)filePaths error:(NSError * __autoreleasing *)error;
- (BOOL)stageFiles:(NSArray *)filePaths options:(FNGitAddOptions)mask error:(NSError * __autoreleasing *)error;
- (BOOL)stageAllFiles:(NSError * __autoreleasing *)error;


- (BOOL)unstageFiles:(NSArray *)filePaths error:(NSError * __autoreleasing *)error;
- (BOOL)unstageAllFiles:(NSError * __autoreleasing *)error;

- (BOOL)removeFiles:(NSArray *)filePaths error:(NSError * __autoreleasing *)error;

- (BOOL)moveFileAtPath:(NSString *)sourceFilePath toPath:(NSString *)destinationFilePath options:(FNGitMoveOptions)mask error:(NSError * __autoreleasing *)error;

- (BOOL)untrackFiles:(NSArray *)filePaths error:(NSError * __autoreleasing *)error;

- (BOOL)revertFiles:(NSArray *)filePaths error:(NSError * __autoreleasing *)error;
- (BOOL)revertFiles:(NSArray *)filePaths toRevision:(NSString *)revision error:(NSError * __autoreleasing *)error;

#pragma mark - Managing Index Flags

- (BOOL)setAssumeUnchangedFlagForFilePaths:(NSArray *)filePaths
                                 error:(NSError * __autoreleasing *)error;

- (BOOL)unsetAssumeUnchangedFlagForFilePaths:(NSArray *)filePaths
                                   error:(NSError * __autoreleasing *)error;

#pragma mark - Committing Changes

/**
 Commits all staged changes.
 
 This method will ensure that the commit is created in UTF-8 encoding regardless of the config 
 setting `i18n.commitencoding`.
 */
- (BOOL)commitWithMessage:(NSString *)message options:(FNGitCommitOptions)mask error:(NSError * __autoreleasing *)error;

#pragma mark - Applying Patches

/**
 Applies the given diff patch to the working tree by default.
 
 You can pass in options to apply the patch to the index and/or apply it in
 reverse which enables you to stage/unstage/discard chunks.
 
 - Stage patch options: `FNGitApplyOptionCached`
 - Unstage patch options: `FNGitApplyOptionCached`, `FNGitApplyOptionReverse`
 - Discard unstaged patch options: `FNGitApplyOptionReverse`
 
 Discarding a staged patch is not supported.
 
 Passing the `FNGitApplyOptionUnidiffZero` option is required if you do single-line staging.
 
 Returns `NO` if the patch could not be applied. If an `error` reference
 was passed it will contain the error.
 */
- (BOOL)applyPatch:(NSData *)patch options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

- (BOOL)applyPatchFromFileAtURL:(NSURL *)fileURL options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

@end
