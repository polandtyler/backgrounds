//
//  FNGitCloneCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 02.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitSVNCommand.h"

@interface FNGitSVNCloneCommand : FNGitSVNCommand
@property (nonatomic, readonly) NSString *remoteURL;
@property (nonatomic, readonly) NSString *localPath;
@property (nonatomic) BOOL usesStandardDirectoryLayout;
@property (nonatomic) NSArray *trunkDirectories;
@property (nonatomic) NSArray *branchDirectories;
@property (nonatomic) NSArray *tagDirectories;

/** @name Creating Instances */

+ (id)gitSVNCloneCommandWithRemoteURL:(NSString *)remoteURL localPath:(NSString *)localPath options:(NSDictionary *)options;
- (id)initWithRemoteURL:(NSString *)remoteURL localPath:(NSString *)localPath options:(NSDictionary *)options;

@end
