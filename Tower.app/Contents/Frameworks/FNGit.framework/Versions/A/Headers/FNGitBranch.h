//
//  FNGitBranch.h
//  FNGit
//
//  Created by Alexander Rinass on 06.12.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitRef.h"

@class FNGitRepository;
@class FNGitCommit;
@class FNGitRemote;
@interface FNGitBranch : NSObject <FNGitRef>
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) FNGitRef *ref;
@property (nonatomic, readonly) NSString *fullRefName;
@property (nonatomic, readonly) NSString *refName;
@property (nonatomic, readonly) NSString *commitHash;
@property (nonatomic, readonly) FNGitCommit *commit;
@property (nonatomic, readonly) NSUInteger commitsAhead;
@property (nonatomic, readonly) NSUInteger commitsBehind;
@property (nonatomic, readonly) NSString *trackedRemoteName;
@property (nonatomic, readonly) NSArray *trackedRefNames;
@property (nonatomic, readonly) BOOL isTracking;
@property (nonatomic, readonly) BOOL usesRebaseForMerge;
@property (nonatomic, readonly) NSArray *mergeOptions;
@property (nonatomic, readonly) BOOL isHead;
@property (nonatomic, readonly) BOOL isDetachedHead;
@property (nonatomic, readonly) BOOL isOrphaned;
@property (nonatomic, readonly) NSString *trackedSVNRemoteName;
@property (nonatomic, readonly) NSString *trackedSVNRefName;
@property (nonatomic, readonly) BOOL isTrackingSVNBranch;

#pragma mark - Validating Branch Names

+ (BOOL)isValidBranchName:(NSString *)branchName;

#pragma mark - Identifying Orphaned Branches

/**
 Wether or not the current HEAD ref is an orphaned branch.
 
 This method is faster than retrieving the HEAD branch and calling `isOrphaned`.
 */
+ (BOOL)isInitialCommitOnHeadBranchForRepository:(FNGitRepository *)repository;

#pragma mark - Retrieving Branches From a Repository

+ (NSArray *)allBranchesForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)currentHeadBranchForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)branchForRefName:(NSString *)refName repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Creating New Branches in a Repository

+ (id)createBranchWithRefName:(NSString *)refName fromRevision:(NSString *)revision inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)createTrackingBranchWithRefName:(NSString *)refName trackedRefName:(NSString *)trackedRefName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Renaming a Branch in a Repository

+ (BOOL)renameBranchWithRefName:(NSString *)refName toRefName:(NSString *)newBranchName inRepository:(FNGitRepository *)repository forcedRenaming:(BOOL)forcesRenaming error:(NSError * __autoreleasing *)error;

#pragma mark - Deleting a Branch in a Repository

+ (BOOL)deleteBranchWithRefName:(NSString *)refName inRepository:(FNGitRepository *)repository forcedDeletion:(BOOL)forcesDeletion error:(NSError * __autoreleasing *)error;

#pragma mark - Managing Branch Tracking

+ (BOOL)addTrackingForBranchWithRefName:(NSString *)refName trackedRefName:(NSString *)trackedRefName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)removeTrackingForBranchWithRefName:(NSString *)refName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Managing Branch Config Options

+ (BOOL)setRebaseOption:(BOOL)usesRebaseForMerge forBranchWithRefName:(NSString *)refName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetRebaseOptionForBranchWithRefName:(NSString *)refName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

+ (BOOL)setMergeOptions:(NSString *)mergeOptions forBranchWithRefName:(NSString *)refName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetMergeOptionsForBranchWithRefName:(NSString *)refName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)branchWithRepository:(FNGitRepository *)repository ref:(FNGitRef *)ref isHead:(BOOL)isHead commitsAhead:(NSUInteger)commitsAhead commitsBehind:(NSUInteger)commitsBehind;

+ (id)detachedBranchWithRepository:(FNGitRepository *)repository commitHash:(NSString *)commitHash;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository
					 ref:(FNGitRef *)ref;

#pragma mark - Retrieving Tracking Information

- (FNGitRemote *)trackedRemote:(NSError * __autoreleasing *)error;
- (NSArray *)trackedRefs:(NSError * __autoreleasing *)error;
- (FNGitRemote *)trackedSVNRemote:(NSError * __autoreleasing *)error;
- (FNGitRef *)trackedSVNRef:(NSError * __autoreleasing *)error;
- (FNGitCommit *)lastSVNCommit:(NSError * __autoreleasing *)error;

@end
