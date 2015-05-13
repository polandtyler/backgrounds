//
//  FNGitRmCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@interface FNGitRmCommand : FNGitCommand
@property (nonatomic) NSArray *filePaths;
@property (nonatomic) BOOL removesFilesRecursively;
@property (nonatomic) BOOL removesFilesFromIndex;
@property (nonatomic) BOOL ignoresUnmatched;

#pragma mark - Factory Methods

+ (id)gitRmCommandWithRepository:(FNGitRepository *)repository;
+ (id)gitRmCommandWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;

@end
