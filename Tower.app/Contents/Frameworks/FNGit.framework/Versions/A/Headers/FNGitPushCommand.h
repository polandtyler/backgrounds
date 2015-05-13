//
//  FNGitPushCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 02.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

extern NSString *const FNGitPushOptionPushTags;
extern NSString *const FNGitPushOptionForcePush;
extern NSString *const FNGitPushOptionDeleteRef;

@class FNGitRefSpec;
@class FNGitRemote;
@interface FNGitPushCommand : FNGitCommand
@property (nonatomic, readonly) FNGitRemote *remote;
@property (nonatomic) NSArray *refSpecs;
@property (nonatomic) BOOL pushesTags;
@property (nonatomic) BOOL forcesPush;
@property (nonatomic) BOOL deletesRef;

#pragma mark - Factory Methods

+ (id)gitPushCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote deletingBranch:(NSString *)remoteBranchRef;
+ (id)gitPushCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote deletingTag:(NSString *)remoteTagRef;
+ (id)gitPushCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote refSpec:(FNGitRefSpec *)refSpec options:(NSDictionary *)options;
+ (id)gitPushCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote refSpecs:(NSArray *)refSpecs options:(NSDictionary *)options;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote refSpecs:(NSArray *)refSpecs options:(NSDictionary *)options;

@end
