//
//  FNGitLsFilesCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 06.08.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

typedef NS_OPTIONS(NSUInteger, FNGitLsFilesOptions) {
    FNGitLsFilesOptionDefaults = 0,
    FNGitLsFilesOptionShowIndexInfo = 1UL << 0,
    FNGitLsFilesOptionUseStandardExcludes = 1UL << 1,
    FNGitLsFilesOptionShowIgnoredFiles = 1UL << 2,
    FNGitLsFilesOptionShowOtherFiles = 1UL << 3,
    FNGitLsFilesOptionShowAssumeUnchangedFiles = 1UL << 4,
    FNGitLsFilesOptionShowSubmodules = 1UL << 5,
};

@interface FNGitLsFilesCommand : FNGitCommand
@property (nonatomic) NSArray *filePaths;
@property (nonatomic) BOOL showsIndexInfo;
@property (nonatomic) BOOL usesStandardExcludes;
@property (nonatomic) BOOL showsIgnoredFiles;
@property (nonatomic) BOOL showsOtherFiles;
@property (nonatomic) BOOL showsAssumeUnchangedFiles;
@property (nonatomic) BOOL showsSubmodules;
@property (nonatomic, readonly) NSArray *entries;

#pragma mark - Factory Methods

+ (id)gitLsFilesCommandWithRepository:(FNGitRepository *)repository;
+ (id)gitLsFilesCommandWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths options:(FNGitLsFilesOptions)options;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths options:(FNGitLsFilesOptions)options;

@end
