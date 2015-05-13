//
//  FNGitSVNRebaseCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 26.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitSVNCommand.h"

@class FNGitRemote;
@interface FNGitSVNRebaseCommand : FNGitSVNCommand

/** @name Creating Instances */

+ (id)gitSVNRebaseCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote;

@end
