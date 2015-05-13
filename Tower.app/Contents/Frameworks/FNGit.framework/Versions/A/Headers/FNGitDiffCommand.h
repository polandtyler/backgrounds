//
//  FNGitDiffCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"
#import "FNGitDiffCommandOptions.h"

@interface FNGitDiffCommand : FNGitCommand
@property (nonatomic) BOOL generatesRawFormat;
@property (nonatomic) BOOL generatesDiffs;
@property (nonatomic) BOOL generatesDiffStats;
@property (nonatomic) BOOL comparesToIndex;
@property (nonatomic, readonly) NSArray *loadedDiffs;
@property (nonatomic, readonly) NSArray *loadedDiffStats;

/** @name Creating GitDiffCommand Objects */

+ (id)gitDiffCommandWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;
- (id)initWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

@end
