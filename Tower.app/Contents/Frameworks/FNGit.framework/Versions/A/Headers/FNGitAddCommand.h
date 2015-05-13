//
//  FNGitAddCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 02.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@class FNGitRepository;
@interface FNGitAddCommand : FNGitCommand
@property (nonatomic) NSArray *filePaths;
@property (nonatomic) BOOL updatesAllFiles;
@property (nonatomic) BOOL ignoresErrors;
@property (nonatomic) BOOL ignoresMissingFiles;
@property (nonatomic) BOOL forcesAdd;

#pragma mark - Factory Methods

+ (id)gitAddCommandWithRepository:(FNGitRepository *)repository;
+ (id)gitAddCommandWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;

@end
