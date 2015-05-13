//
//  FNGitCommitCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 27.09.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

@interface FNGitCommitCommand : FNGitCommand
@property (nonatomic) NSString *message;
@property (nonatomic) BOOL amendsChanges;
@property (nonatomic) BOOL signsOff;

#pragma mark - Factory Methods

+ (id)gitCommitCommandWithRepository:(FNGitRepository *)repository message:(NSString *)message;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository message:(NSString *)message;

@end
