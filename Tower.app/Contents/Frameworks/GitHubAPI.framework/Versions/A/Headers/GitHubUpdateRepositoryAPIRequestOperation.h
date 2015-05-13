//
//  GitHubUpdateRepositoryAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 20.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

@class GitHubRepository;

typedef void (^GitHubUpdateRepositoryErrorHandler)(NSError *error);
typedef void (^GitHubUpdateRepositoryCompletionHandler)(GitHubRepository *repository);

@interface GitHubUpdateRepositoryAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) GitHubRepository *repository;
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;
@property (nonatomic, copy) GitHubUpdateRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) GitHubUpdateRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth repository:(GitHubRepository *)repository;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth repository:(GitHubRepository *)repository;

#pragma mark - Synchronously Sending the Request

- (GitHubRepository *)send:(NSError * __autoreleasing *)error;

@end
