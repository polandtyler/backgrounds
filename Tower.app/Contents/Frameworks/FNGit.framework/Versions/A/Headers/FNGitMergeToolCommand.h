//
//  FNGitMergeToolCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 09.09.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

@interface FNGitMergeToolCommand : FNGitCommand
@property (nonatomic, copy) NSString *filePath;
@property (nonatomic, copy) NSString *mergeToolName;
@property (nonatomic) BOOL keepsBackupFiles;

/** @name Creating MergeTool Command Objects */

+ (id)gitMergeToolCommandWithRepository:(FNGitRepository *)repository filePath:(NSString *)filePath;
- (id)initWithRepository:(FNGitRepository *)repository filePath:(NSString *)filePath;

@end
