//
//  FNGitSVNFetchCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 26.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitSVNCommand.h"

@interface FNGitSVNFetchCommand : FNGitSVNCommand

/** @name Creating Instances */

+ (id)gitSVNFetchCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote;

@end
