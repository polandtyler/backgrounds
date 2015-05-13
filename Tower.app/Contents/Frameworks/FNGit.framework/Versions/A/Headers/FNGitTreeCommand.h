//
//  FNGitTreeCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@interface FNGitTreeCommand : FNGitCommand
@property (nonatomic) NSString *objectReference;
@property (nonatomic) NSString *revision;
@property (nonatomic) NSString *filePath;
@property (nonatomic) BOOL includesFileSize;
@property (nonatomic) BOOL recursesDirectories;
@property (nonatomic, readonly) NSArray *treeEntries;

#pragma mark - Factory Methods

+ (id)gitTreeCommandWithRepository:(FNGitRepository *)repository treeHash:(NSString *)treeHash;
+ (id)gitTreeCommandWithRepository:(FNGitRepository *)repository revision:(NSString *)revision directoryPath:(NSString *)directoryPath;
+ (id)gitTreeCommandWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePath:(NSString *)filePath;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository options:(FNGitTreeOptions)options;

@end
