//
//  FNGitSVNDCommitCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 26.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitSVNCommand.h"

@class FNGitRemote;
@interface FNGitSVNDCommitCommand : FNGitSVNCommand
@property (nonatomic) NSString *revision;

/** @name Creating Instances */

+ (id)gitSVNDCommitCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote;
+ (id)gitSVNDCommitCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote revision:(NSString *)revision;
- (id)initWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote;

@end
