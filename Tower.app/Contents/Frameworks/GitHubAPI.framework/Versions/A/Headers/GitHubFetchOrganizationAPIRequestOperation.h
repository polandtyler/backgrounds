//
//  GitHubFetchOrganizationAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 19.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

@class GitHubAccount;

typedef void (^GitHubFetchOrganizationErrorHandler)(NSError *error);
typedef void (^GitHubFetchOrganizationCompletionHandler)(GitHubAccount *organization);

@interface GitHubFetchOrganizationAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) NSString *organizationName;
@property (nonatomic, strong, readonly) GitHubAccount *organization;
@property (nonatomic, copy) GitHubFetchOrganizationErrorHandler errorHandler;
@property (nonatomic, copy) GitHubFetchOrganizationCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth organizationName:(NSString *)organizationName;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth organizationName:(NSString *)organizationName;

#pragma mark - Synchronously Sending the Request

- (GitHubAccount *)send:(NSError * __autoreleasing *)error;

@end
