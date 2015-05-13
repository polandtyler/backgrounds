//
//  FNGitCloneCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 02.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

extern NSString *const FNGitCloneOptionBare;
extern NSString *const FNGitCloneOptionInitializeSubmodules;

@interface FNGitCloneCommand : FNGitCommand
@property (nonatomic) NSString *remoteURL;
@property (nonatomic) NSString *localPath;
@property (nonatomic, getter = isBare) BOOL bare;
@property (nonatomic) BOOL initializesSubmodules;

#pragma mark - Factory Methods

+ (id)gitCloneCommandWithRemoteURL:(NSString *)remoteURL localPath:(NSString *)localPath options:(NSDictionary *)options;

#pragma mark - Initialization

- (id)initWithRemoteURL:(NSString *)remoteURL localPath:(NSString *)localPath options:(NSDictionary *)options;

@end
