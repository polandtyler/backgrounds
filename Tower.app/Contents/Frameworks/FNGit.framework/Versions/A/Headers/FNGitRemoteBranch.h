//
//  FNGitRemoteBranch.h
//  FNGit
//
//  Created by Alexander Rinass on 06.12.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitRef.h"

@class FNGitRepository;
@class FNGitRemote;
@interface FNGitRemoteBranch : NSObject <FNGitRef>
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) FNGitRef *ref;
@property (nonatomic, readonly) NSString *fullRefName;
@property (nonatomic, readonly) NSString *refName;
@property (nonatomic, readonly) NSString *commitHash;
@property (nonatomic, readonly) FNGitCommit *commit;
@property (nonatomic, readonly) BOOL isHead;
@property (nonatomic, readonly) NSString *remoteName;

#pragma mark - Retrieving Remote Branches for a Repository

+ (NSArray *)allRemoteBranchesForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)remoteBranchForRefName:(NSString *)refName repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)remoteBranchWithRepository:(FNGitRepository *)repository ref:(FNGitRef *)ref remoteName:(NSString *)remoteName isHead:(BOOL)isHead;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository ref:(FNGitRef *)ref remoteName:(NSString *)remoteName isHead:(BOOL)isHead;

#pragma mark - Retrieving the Remote for this Remote Branch

- (FNGitRemote *)remote:(NSError * __autoreleasing *)error;

@end
