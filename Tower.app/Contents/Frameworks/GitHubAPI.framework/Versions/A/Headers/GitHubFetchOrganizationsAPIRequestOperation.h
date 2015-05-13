//
//  GitHubFetchOrganizationsAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 19.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

typedef void (^GitHubFetchOrganizationsErrorHandler)(NSError *error);
typedef void (^GitHubFetchOrganizationsCompletionHandler)(NSArray *organizations);

@interface GitHubFetchOrganizationsAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) NSString *username;
@property (nonatomic, strong, readonly) NSArray *organizations;
@property (nonatomic, copy) GitHubFetchOrganizationsErrorHandler errorHandler;
@property (nonatomic, copy) GitHubFetchOrganizationsCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth;
+ (id)requestWithAuth:(GitHubAuth *)auth username:(NSString *)username;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth username:(NSString *)username;

#pragma mark - Synchronously Sending the Request

- (NSArray *)send:(NSError * __autoreleasing *)error;

@end
