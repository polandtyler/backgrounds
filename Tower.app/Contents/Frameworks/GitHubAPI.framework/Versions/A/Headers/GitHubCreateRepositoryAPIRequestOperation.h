//
//  GitHubCreateRepositoryAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 20.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

@class GitHubRepository;

typedef void (^GitHubCreateRepositoryErrorHandler)(NSError *error);
typedef void (^GitHubCreateRepositoryCompletionHandler)(GitHubRepository *repository);

@interface GitHubCreateRepositoryAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) GitHubRepository *repository;
@property (nonatomic, strong, readonly) NSString *organizationName;
@property (nonatomic, readonly, getter = isCreated) BOOL created;
@property (nonatomic, copy) GitHubCreateRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) GitHubCreateRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth repository:(GitHubRepository *)repository;
+ (id)requestWithAuth:(GitHubAuth *)auth repository:(GitHubRepository *)repository organizationName:(NSString *)organizationName;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth repository:(GitHubRepository *)repository organizationName:(NSString *)organizationName;

#pragma mark - Synchronously Sending the Request

- (GitHubRepository *)send:(NSError * __autoreleasing *)error;

@end
