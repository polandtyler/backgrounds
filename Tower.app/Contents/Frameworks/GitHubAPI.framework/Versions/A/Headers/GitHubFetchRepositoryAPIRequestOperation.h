//
//  GitHubFetchRepositoryAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 20.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

@class GitHubRepository;

typedef void (^GitHubFetchRepositoryErrorHandler)(NSError *error);
typedef void (^GitHubFetchRepositoryCompletionHandler)(GitHubRepository *repository);

@interface GitHubFetchRepositoryAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) NSString *accountName;
@property (nonatomic, strong, readonly) NSString *repositoryName;
@property (nonatomic, strong, readonly) GitHubRepository *repository;
@property (nonatomic, copy) GitHubFetchRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) GitHubFetchRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth fullRepositoryName:(NSString *)fullRepositoryName;
+ (id)requestWithAuth:(GitHubAuth *)auth accountName:(NSString *)accountName repositoryName:(NSString *)repositoryName;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth accountName:(NSString *)accountName repositoryName:(NSString *)repositoryName;

#pragma mark - Synchronously Sending the Request

- (GitHubRepository *)send:(NSError * __autoreleasing *)error;

@end
