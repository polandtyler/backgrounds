//
//  FNGitFetchCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 02.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

extern NSString *const FNGitFetchOptionPruneObsoleteRemoteBranches;
extern NSString *const FNGitFetchOptionForceTagsDownload;
extern NSString *const FNGitFetchOptionRecurseSubmodules;

@class FNGitRefSpec;
@class FNGitRemote;
@interface FNGitFetchCommand : FNGitCommand
@property (nonatomic, readonly) FNGitRemote *remote;
@property (nonatomic) FNGitRefSpec *refSpec;
@property (nonatomic) BOOL prunesObsoleteRemoteBranches;
@property (nonatomic) BOOL forcesTagsDownload;
@property (nonatomic) BOOL recursesSubmodules;

#pragma mark - Factory Methods

+ (id)gitFetchCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote refSpec:(FNGitRefSpec *)refSpec options:(NSDictionary *)options;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote refSpec:(FNGitRefSpec *)refSpec options:(NSDictionary *)options;

@end
