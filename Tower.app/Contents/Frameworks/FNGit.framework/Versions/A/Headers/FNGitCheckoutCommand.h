//
//  FNGitCheckoutCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 02.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@class FNGitRepository;
@interface FNGitCheckoutCommand : FNGitCommand
@property (nonatomic, readonly) NSString *revision;
@property (nonatomic) NSArray *filePaths;

#pragma mark - Factory Methods

+ (id)gitCheckoutCommandWithRepository:(FNGitRepository *)repository revision:(NSString *)revision;
+ (id)gitCheckoutCommandWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePaths:(NSArray *)filePaths;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePaths:(NSArray *)filePaths;

@end
