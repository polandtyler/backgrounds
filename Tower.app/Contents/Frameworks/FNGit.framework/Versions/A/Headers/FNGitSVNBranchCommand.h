//
//  FNGitSVNBranchCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 31.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitSVNCommand.h"

@class FNGitRemote;
@interface FNGitSVNBranchCommand : FNGitSVNCommand
@property (nonatomic) NSString *refName;
@property (nonatomic) NSString *startingPoint;
@property (nonatomic) NSString *message;
@property (nonatomic) NSString *destination;
@property (nonatomic) BOOL createsParentDirectories;

/** @name Creating Instances */

+ (id)gitSVNBranchCommandWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote refName:(NSString *)refName startingPoint:(NSString *)startingPoint;
- (id)initWithRepository:(FNGitRepository *)repository remote:(FNGitRemote *)remote refName:(NSString *)refName startingPoint:(NSString *)startingPoint;

@end
