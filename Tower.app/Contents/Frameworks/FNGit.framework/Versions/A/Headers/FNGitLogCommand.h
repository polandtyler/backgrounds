//
//  FNGitLogCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"
#import "FNGitLogCommandOptions.h"

@interface FNGitLogCommand : FNGitCommand
@property (nonatomic) NSArray *revisions;
@property (nonatomic) NSArray *filePaths;
@property (nonatomic) BOOL countsCommits;
@property (nonatomic) BOOL generatesDiffs;
@property (nonatomic) BOOL generatesDiffStats;
@property (nonatomic) BOOL loadsFullCommitInfo;
@property (nonatomic) BOOL decoratesCommits;
@property (nonatomic) BOOL firstParent;
@property (nonatomic) NSUInteger limit;
@property (nonatomic) NSUInteger offset;
@property (nonatomic) NSString *searchPattern;
@property (nonatomic) NSString *searchAuthorPattern;
@property (nonatomic) NSString *searchCommitterPattern;
@property (nonatomic, readonly) NSArray *commits;
//@property (nonatomic, readonly) NSArray *diffs;
@property (nonatomic, readonly) NSArray *diffStats;
@property (nonatomic, readonly) NSUInteger commitCount;
@property (nonatomic, readonly) NSArray *loadedDiffs;
@property (nonatomic, readonly) NSArray *loadedDiffStats;

#pragma mark - Factory Methods

+ (id)gitLogCommandWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

@end
