//
//  FNGitBranchCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

extern NSString *const FNGitBranchOptionShowRemoteBranches;
extern NSString *const FNGitBranchOptionRename;
extern NSString *const FNGitBranchOptionForceRenaming;
extern NSString *const FNGitBranchOptionDelete;
extern NSString *const FNGitBranchOptionForceDeletion;
extern NSString *const FNGitBranchOptionCreateTracking;
extern NSString *const FNGitBranchOptionAddTracking;
extern NSString *const FNGitBranchOptionRemoveTracking;

@interface FNGitBranchCommand : FNGitCommand
@property (nonatomic) NSArray *refNames;
@property (nonatomic) NSString *trackedRefName;
@property (nonatomic) NSString *startingPoint;
@property (nonatomic) NSString *renameToRefName;
@property (nonatomic) BOOL showsRemoteBranches;
@property (nonatomic) BOOL renamesBranch;
@property (nonatomic) BOOL forcesRenaming;
@property (nonatomic) BOOL deletesBranch;
@property (nonatomic) BOOL forcesDeletion;
@property (nonatomic) BOOL createsTracking;
@property (nonatomic) BOOL addsTracking;
@property (nonatomic) BOOL removesTracking;
@property (nonatomic, readonly) NSArray *branches;

#pragma mark - Factory Methods

+ (instancetype)gitBranchCommandWithRepository:(FNGitRepository *)repository;
+ (instancetype)gitCreateBranchCommandWithRepository:(FNGitRepository *)repository refName:(NSString *)refName startingPoint:(NSString *)revision;
+ (instancetype)gitCreateTrackingBranchCommandWithRepository:(FNGitRepository *)repository refName:(NSString *)refName trackedRefName:(NSString *)trackedRefName;
+ (instancetype)gitAddTrackingBranchCommandWithRepository:(FNGitRepository *)repository refName:(NSString *)refName trackedRefName:(NSString *)trackedRefName;
+ (instancetype)gitRemoveTrackingBranchCommandWithRepository:(FNGitRepository *)repository refName:(NSString *)refName;
+ (instancetype)gitDeleteBranchCommandWithRepository:(FNGitRepository *)repository refNames:(NSArray *)refNames forcedDeletion:(BOOL)forcesDeletion;
+ (instancetype)gitRenameBranchCommandWithRepository:(FNGitRepository *)repository refName:(NSString *)refName newRefName:(NSString *)newRefName forcedRenaming:(BOOL)forcesRenaming;

#pragma mark - Initialization

- (instancetype)initWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

@end
