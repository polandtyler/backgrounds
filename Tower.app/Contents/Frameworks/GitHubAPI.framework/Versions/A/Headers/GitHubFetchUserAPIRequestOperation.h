//
//  GitHubFetchUserAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 19.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

@class GitHubAccount;

typedef void (^GitHubFetchUserErrorHandler)(NSError *error);
typedef void (^GitHubFetchUserCompletionHandler)(GitHubAccount *user);

@interface GitHubFetchUserAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) NSString *username;
@property (nonatomic, strong, readonly) GitHubAccount *user;
@property (nonatomic, copy) GitHubFetchUserErrorHandler errorHandler;
@property (nonatomic, copy) GitHubFetchUserCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth;
+ (id)requestWithAuth:(GitHubAuth *)auth username:(NSString *)username;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth username:(NSString *)username;

#pragma mark - Synchronously Sending the Request

- (GitHubAccount *)send:(NSError * __autoreleasing *)error;

@end
