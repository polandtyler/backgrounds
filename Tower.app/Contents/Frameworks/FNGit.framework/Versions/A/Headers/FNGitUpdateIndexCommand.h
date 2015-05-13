//
//  FNGitUpdateIndexCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 27.09.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@interface FNGitUpdateIndexCommand : FNGitCommand
@property (nonatomic) NSArray *filePaths;
@property (nonatomic) BOOL ignoresMissingFiles;
@property (nonatomic) BOOL setsAssumeUnchangedBit;
@property (nonatomic) BOOL unsetsAssumeUnchangedBit;

/** @name Creating Objects */

+ (id)gitUpdateIndexCommandWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;
- (id)initWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;

@end
