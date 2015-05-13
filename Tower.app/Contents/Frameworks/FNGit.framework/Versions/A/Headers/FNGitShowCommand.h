//
//  FNGitShowCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@interface FNGitShowCommand : FNGitCommand
@property (nonatomic, readonly) NSString *objectReference;

#pragma mark - Factory Methods

+ (id)gitShowCommandWithRepository:(FNGitRepository *)repository objectHash:(NSString *)objectHash;
+ (id)gitShowCommandWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePath:(NSString *)filePath;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository objectReference:(NSString *)objectReference;


@end
