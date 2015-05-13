//
//  GitHubAccount.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 19.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@class GitHubPlan;
@interface GitHubAccount : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger accountID;
@property (nonatomic, strong, readonly) NSString *login;
@property (nonatomic, strong) NSString *name;    
@property (nonatomic, strong, readonly) NSString *avatarURL;
@property (nonatomic, strong, readonly) NSString *gravatarID;
@property (nonatomic, strong, readonly) NSString *URL;
@property (nonatomic, strong) NSString *company;
@property (nonatomic, strong) NSString *blog;
@property (nonatomic, strong) NSString *location;
@property (nonatomic, strong) NSString *email;
@property (nonatomic, strong) NSString *billingEmail;
@property (nonatomic, getter = isHirable) BOOL hirable;
@property (nonatomic, strong) NSString *bio;
@property (nonatomic, readonly) NSInteger publicRepositories;
@property (nonatomic, readonly) NSInteger publicGists;
@property (nonatomic, readonly) NSInteger followers;
@property (nonatomic, readonly) NSInteger following;
@property (nonatomic, strong, readonly) NSString *HTMLURL;
@property (nonatomic, strong, readonly) NSDate *createdAt;
@property (nonatomic, strong, readonly) NSString *type;
@property (nonatomic, readonly) NSInteger totalPrivateRepos;
@property (nonatomic, readonly) NSInteger ownedPrivateRepos;
@property (nonatomic, readonly) NSInteger privateGists;
@property (nonatomic, readonly) NSInteger diskUsage;
@property (nonatomic, strong, readonly) GitHubPlan *plan;

#pragma mark - Factory Methods

+ (id)accountFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Retrieving Writable Properties as JSON

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToGitHubAccount:(GitHubAccount *)otherObject;

#pragma mark - Querying the Account Type

- (BOOL)isUserAccount;
- (BOOL)isOrganizationAccount;

@end
