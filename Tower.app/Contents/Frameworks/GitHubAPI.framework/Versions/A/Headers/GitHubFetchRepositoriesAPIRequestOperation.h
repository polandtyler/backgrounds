//
//  GitHubFetchRepositoriesAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 20.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

typedef void (^GitHubFetchRepositoriesErrorHandler)(NSError *error);
typedef void (^GitHubFetchRepositoriesCompletionHandler)(NSArray *repositories);

@interface GitHubFetchRepositoriesAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) NSString *accountName;
@property (nonatomic, strong, readonly) NSArray *repositories;
@property (nonatomic, strong, readonly) NSString *organizationName;
@property (nonatomic, copy) GitHubFetchRepositoriesErrorHandler errorHandler;
@property (nonatomic, copy) GitHubFetchRepositoriesCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth;
+ (id)requestWithAuth:(GitHubAuth *)auth accountName:(NSString *)accountName;
+ (id)requestWithAuth:(GitHubAuth *)auth organizationName:(NSString *)organizationName;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth accountName:(NSString *)accountName organizationName:(NSString *)organizationName;

#pragma mark - Synchronously Sending the Request

- (NSArray *)send:(NSError * __autoreleasing *)error;

@end
