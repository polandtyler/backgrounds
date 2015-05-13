//
//  FNGitRemoteCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@interface FNGitRemoteCommand : FNGitCommand
@property (nonatomic) NSArray *remoteNames;
@property (nonatomic) NSString *URL;
@property (nonatomic) BOOL createsRemote;
@property (nonatomic) BOOL renamesRemote;
@property (nonatomic) BOOL deletesRemote;
@property (nonatomic, readonly) NSArray *remotes;

#pragma mark - Factory Methods

+ (id)gitCreateRemoteCommandWithRepository:(FNGitRepository *)repository remoteName:(NSString *)remoteName URL:(NSString *)URL;
+ (id)gitRenameRemoteCommandWithRepository:(FNGitRepository *)repository remoteName:(NSString *)remoteName newRemoteName:(NSString *)newRemoteName;
+ (id)gitDeleteRemoteCommandWithRepository:(FNGitRepository *)repository remoteName:(NSString *)remoteName;

@end
