//
//  GitHubUpdateUserAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 19.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

@class GitHubAccount;

typedef void (^GitHubUpdateUserErrorHandler)(NSError *error);
typedef void (^GitHubUpdateUserCompletionHandler)(GitHubAccount *user);

@interface GitHubUpdateUserAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) GitHubAccount *user;
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;
@property (nonatomic, copy) GitHubUpdateUserErrorHandler errorHandler;
@property (nonatomic, copy) GitHubUpdateUserCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth user:(GitHubAccount *)user;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth user:(GitHubAccount *)user;

#pragma mark - Synchronously Sending the Request

- (GitHubAccount *)send:(NSError * __autoreleasing *)error;

@end
