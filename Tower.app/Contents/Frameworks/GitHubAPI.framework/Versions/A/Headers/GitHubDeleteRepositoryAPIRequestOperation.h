//
//  GitHubDeleteRepositoryAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 20.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

typedef void (^GitHubDeleteRepositoryErrorHandler)(NSError *error);
typedef void (^GitHubDeleteRepositoryCompletionHandler)(void);

@interface GitHubDeleteRepositoryAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) NSString *accountName;
@property (nonatomic, strong, readonly) NSString *repositoryName;
@property (nonatomic, readonly, getter = isDeleted) BOOL deleted;
@property (nonatomic, copy) GitHubDeleteRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) GitHubDeleteRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth fullRepositoryName:(NSString *)fullRepositoryName;
+ (id)requestWithAuth:(GitHubAuth *)auth accountName:(NSString *)accountName repositoryName:(NSString *)repositoryName;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth accountName:(NSString *)accountName repositoryName:(NSString *)repositoryName;

#pragma mark - Synchronously Sending the Request

- (BOOL)send:(NSError * __autoreleasing *)error;

@end
