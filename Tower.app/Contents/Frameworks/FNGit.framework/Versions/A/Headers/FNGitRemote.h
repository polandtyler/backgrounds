//
//  FNGitRemote.h
//  FNGit
//
//  Created by Alexander Rinass on 14.01.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitRepository;
@class FNGitRef;
@class FNGitRemoteBranch;
@class FNGitRemoteConfig;
@interface FNGitRemote : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *name;

/**
 The “resolved“ (without Git remote aliases) URL used for downstream remote operations (e.g. fetch,
 pull).
 
 The value can differ from the `URL` property and should always be used for remote operations 
 instead of `URL` (since it can contain aliases).
 */
@property (nonatomic, readonly) NSString *downstreamURL;

/**
 The “resolved“ (without Git remote aliases and using the downstream URL if no push URL is set) URL
 used for upstream remote operations (e.g. push).
 
 The value can differ from the `pushURL` property and should always be used for remote operations
 instead of `pushURL` (since it could be empty).
 */
@property (nonatomic, readonly) NSString *upstreamURL;
@property (nonatomic, readonly) NSArray *branches;
@property (nonatomic, readonly) NSString *URL;
@property (nonatomic, readonly) NSString *pushURL;
@property (nonatomic, readonly) NSString *proxy;
@property (nonatomic, readonly) NSArray *fetchRefSpecs;
@property (nonatomic, readonly) NSArray *pushRefSpecs;
@property (nonatomic, readonly) BOOL skipsDefaultUpdate;
@property (nonatomic, readonly) BOOL skipsFetchAll;
@property (nonatomic, readonly) BOOL isSVNRemote;
@property (nonatomic, readonly) NSString *SVNUUID;
@property (nonatomic, readonly) NSString *SVNPrefix;
@property (nonatomic, readonly) NSArray *SVNTrunkRefSpecs;
@property (nonatomic, readonly) NSArray *SVNBranchRefSpecs;
@property (nonatomic, readonly) NSArray *SVNTagRefSpecs;
@property (nonatomic, readonly) FNGitRemoteConfig *config;

#pragma mark - Validating a Remote Name

+ (BOOL)isValidRemoteName:(NSString *)remoteName;

#pragma mark - Checking Existence of a Remote

+ (BOOL)existsRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository;

#pragma mark - Retrieving Remotes for a Repository

+ (NSArray *)allRemoteNamesForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (NSArray *)allRemotesForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)originRemoteForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)remoteForName:(NSString *)remoteName repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)SVNRemoteForUUID:(NSString *)anSVNRemoteUUID repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Creating a New Remote in a Repository

+ (id)createRemoteWithName:(NSString *)remoteName URL:(NSString *)remoteURL inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)createSVNRemoteWithName:(NSString *)remoteName URL:(NSString *)remoteURL inRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

#pragma mark - Deleting the Remote

+ (BOOL)deleteRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Renaming the Remote

+ (BOOL)renameRemoteWithName:(NSString *)remoteName toNewRemoteName:(NSString *)newRemoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Setting and Unsetting Remote URLs

+ (BOOL)setURL:(NSString *)URL forRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

+ (BOOL)setPushURL:(NSString *)pushURL forRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetPushURLForRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Setting and Unsetting Remote Options

+ (BOOL)setFetchRefSpecs:(NSArray *)refSpecs forRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetFetchRefSpecsForRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

+ (BOOL)setPushRefSpecs:(NSArray *)refSpecs forRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetPushRefSpecsForRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

+ (BOOL)setProxy:(NSString *)proxy forRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetProxyForRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

+ (BOOL)setSkipsDefaultUpdate:(BOOL)skipsDefaultUpdate forRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetSkipsDefaultUpdateForRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

+ (BOOL)setSkipsFetchAll:(BOOL)skipsFetchAll forRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetSkipsFetchAllForRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Setting and Unsetting SVN Remote Options

+ (BOOL)setSVNTrunkRefSpecs:(NSArray *)trunkRefSpecs forRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetSVNTrunkRefSpecsForRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

+ (BOOL)setSVNBranchRefSpecs:(NSArray *)branchRefSpecs forRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetSVNBranchRefSpecsForRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

+ (BOOL)setSVNTagRefSpecs:(NSArray *)tagRefSpecs forRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (BOOL)unsetSVNTagRefSpecsForRemoteWithName:(NSString *)remoteName inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)remoteWithRepository:(FNGitRepository *)repository name:(NSString *)remoteName downstreamURL:(NSString *)downstreamURL upstreamURL:(NSString *)upstreamURL branches:(NSArray *)remoteBranches;

+ (id)SVNRemoteWithRepository:(FNGitRepository *)repository name:(NSString *)remoteName downstreamURL:(NSString *)downstreamURL upstreamURL:(NSString *)upstreamURL branches:(NSArray *)remoteBranches;

+ (id)localRemoteWithRepository:(FNGitRepository *)repository;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository name:(NSString *)remoteName downstreamURL:(NSString *)downstreamURL upstreamURL:(NSString *)upstreamURL branches:(NSArray *)remoteBranches isSVNRemote:(BOOL)isSVNRemote;

#pragma mark - Retrieving a Remote Branch

- (FNGitRemoteBranch *)remoteBranchForRefName:(NSString *)refName;

@end
