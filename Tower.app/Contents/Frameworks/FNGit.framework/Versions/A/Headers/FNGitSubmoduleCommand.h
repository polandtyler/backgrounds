//
//  FNGitSubmoduleCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@interface FNGitSubmoduleCommand : FNGitCommand
@property (nonatomic) NSString *remoteURL;
@property (nonatomic) NSArray *filePaths;
@property (nonatomic) BOOL initializesSubmodules;
@property (nonatomic) BOOL recursesSubmodules;
@property (nonatomic, readonly) NSArray *submodules;

/** @name Creating Submodule Commands */

+ (id)gitSubmoduleAddCommandWithRepository:(FNGitRepository *)repository path:(NSString *)path remoteURL:(NSString *)remoteURL options:(FNGitAddSubmoduleOptions)options;
+ (id)gitSubmoduleStatusCommandWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;
+ (id)gitSubmoduleUpdateCommandWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths options:(FNGitUpdateSubmoduleOptions)options;
+ (id)gitSubmoduleSyncCommandWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;

@end
