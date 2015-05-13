//
//  FNGitCheckAttrCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 28.09.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

@interface FNGitCheckAttrCommand : FNGitCommand
@property (nonatomic) NSArray *filePaths;
@property (nonatomic, readonly) NSArray *attributes;

#pragma mark - Factory Methods

+ (id)gitCheckAttrCommandWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths;

@end
