//
//  FNGitBlameCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 24.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@class FNGitRepository;
@interface FNGitBlameCommand : FNGitCommand
@property (nonatomic, readonly) NSString *revision;
@property (nonatomic, readonly) NSString *filePath;
@property (nonatomic, readonly) NSArray *annotatedLines;

#pragma mark - Factory Methods

+ (id)gitBlameCommandWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePath:(NSString *)filePath;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePath:(NSString *)filePath;

@end
