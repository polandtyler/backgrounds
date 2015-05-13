//
//  FNGitSVNCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 31.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@class FNGitRemote;
@interface FNGitSVNCommand : FNGitCommand
@property (nonatomic, readonly) FNGitRemote *remote;

/** @name Creating Instances */

- (id)initWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote;

@end
