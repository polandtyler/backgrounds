//
//  FNGitDiffToolCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 09.09.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

@interface FNGitDiffToolCommand : FNGitCommand
@property (nonatomic, copy) NSArray *filePaths;
@property (nonatomic, copy) NSArray *revisions;
@property (nonatomic, copy) NSString *diffToolName;
@property (nonatomic) BOOL performsDirectoryDiff;
@property (nonatomic) BOOL comparesIndex;

/** @name Creating DiffTool Command Objects */

+ (id)gitDiffToolCommandWithRepository:(FNGitRepository *)repository;
- (id)initWithRepository:(FNGitRepository *)repository;

@end
