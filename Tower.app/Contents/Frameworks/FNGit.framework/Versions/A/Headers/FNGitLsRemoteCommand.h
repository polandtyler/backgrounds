//
//  FNLsRemoteGitCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 12.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

extern NSString *const FNGitLsRemoteOptionHeads;
extern NSString *const FNGitLsRemoteOptionTags;

@interface FNGitLsRemoteCommand : FNGitCommand
@property (nonatomic, readonly) NSString *remoteURL;
@property (nonatomic) BOOL showsHeads;
@property (nonatomic) BOOL showsTags;
@property (nonatomic) NSArray *refs;

#pragma mark - Verifying a Remote Connection

+ (BOOL)canConnectToRemoteAtURL:(NSString *)remoteURL error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)gitLsRemoteCommandWithRemoteURL:(NSString *)remoteURL options:(NSDictionary *)options;

#pragma mark - Initialization

- (id)initWithRemoteURL:(NSString *)remoteURL options:(NSDictionary *)options;

@end
