//
//  FNGitStatusCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 28.09.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@interface FNGitStatusCommand : FNGitCommand
@property (nonatomic) NSArray *filePaths;
@property (nonatomic) BOOL showsIgnoredFiles;
@property (nonatomic) FNGitStatusUntrackedFilesMode untrackedFilesMode;
@property (nonatomic) FNGitStatusIgnoreSubmodulesMode ignoreSubmodulesMode;
@property (nonatomic, readonly) NSArray *changedFiles;

#pragma mark - Factory Methods

+ (id)gitStatusCommandWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;

@end
