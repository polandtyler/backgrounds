//
//  GitHubRepository.h
//  Tower
//
//  Created by Alexander Rinass on 12.04.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@class GitHubAccount;
@interface GitHubRepository : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger repositoryID;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong, readonly) NSString *fullName;
@property (nonatomic, strong) NSString *descr;
@property (nonatomic, strong) NSString *homepage;
@property (nonatomic, strong, readonly) NSString *language;
@property (nonatomic, strong, readonly) NSString *masterBranch;
@property (nonatomic, strong, readonly) NSString *URL;
@property (nonatomic, strong, readonly) NSString *HTMLURL;
@property (nonatomic, strong, readonly) NSString *cloneURL;
@property (nonatomic, strong, readonly) NSString *forkURL;
@property (nonatomic, strong, readonly) NSString *gitURL;
@property (nonatomic, strong, readonly) NSString *SSHURL;
@property (nonatomic, strong, readonly) NSString *SVNURL;
@property (nonatomic, strong, readonly) NSString *mirrorURL;
@property (nonatomic, getter = isPrivate) BOOL private;
@property (nonatomic, readonly, getter = isForked) BOOL forked;
@property (nonatomic, readonly) NSInteger forks;
@property (nonatomic, readonly) NSInteger watchers;
@property (nonatomic, readonly) NSInteger openIssues;
@property (nonatomic, readonly) NSInteger size;
@property (nonatomic, getter = hasIssues) BOOL issues;
@property (nonatomic, getter = hasWiki) BOOL wiki;
@property (nonatomic, getter = hasDownloads) BOOL downloads;
@property (nonatomic, strong, readonly) NSDate *pushedAt;
@property (nonatomic, strong, readonly) NSDate *createdAt;
@property (nonatomic, strong, readonly) NSDate *updatedAt;
@property (nonatomic, strong, readonly) GitHubAccount *owner;
@property (nonatomic, strong, readonly) GitHubAccount *organization;

#pragma mark - Factory Methods

+ (id)repositoryFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Retrieving Writable Properties as JSON

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToGitHubRepository:(GitHubRepository *)otherObject;

@end
