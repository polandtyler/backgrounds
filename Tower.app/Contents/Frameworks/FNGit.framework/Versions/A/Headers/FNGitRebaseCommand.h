//
//  FNGitRebaseCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"
#import "FNGitRebaseOptions.h"

@interface FNGitRebaseCommand : FNGitCommand
@property (nonatomic, copy) NSString *revision;
@property (nonatomic) BOOL continuesRebase;
@property (nonatomic) BOOL abortsRebase;
@property (nonatomic) BOOL skipsRebase;
@property (nonatomic) BOOL keepsEmptyCommits;
@property (nonatomic) BOOL preservesMergeCommits;
@property (nonatomic) BOOL interactiveRebase;

/** @name Creating Rebase Command Objects */

+ (id)gitRebaseCommandWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;
- (id)initWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

@end
