//
//  FNGitPullCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 02.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

extern NSString *const FNGitPullOptionRebase;
extern NSString *const FNGitPullOptionPreserveMergeCommits;

@class FNGitRefSpec;
@class FNGitRemote;
@interface FNGitPullCommand : FNGitCommand
@property (nonatomic, readonly) FNGitRemote *remote;
@property (nonatomic) FNGitRefSpec *refSpec;
@property (nonatomic) BOOL usesRebase;
@property (nonatomic) BOOL preservesMergeCommits;

#pragma mark - Factory Methods

+ (id)gitPullCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote refSpec:(FNGitRefSpec *)refSpec options:(NSDictionary *)options;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote refSpec:(FNGitRefSpec *)refSpec options:(NSDictionary *)options;

@end
