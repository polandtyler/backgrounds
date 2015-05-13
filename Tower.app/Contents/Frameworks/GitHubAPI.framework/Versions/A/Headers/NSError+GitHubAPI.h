//
//  NSError+GitHubAPI.h
//  Tower
//
//  Created by Alexander Rinass on 12.04.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const GitHubAPIErrorDomain;

extern NSString *const GitHubRequestURLErrorKey;
extern NSString *const GitHubRequestPathErrorKey;
extern NSString *const GitHubRequestParametersErrorKey;
extern NSString *const GitHubRequestHeadersErrorKey;

extern NSString *const GitHubResponseStatusCodeErrorKey;
extern NSString *const GitHubResponseBodyErrorKey;

extern NSString *const GitHubErrorInfoErrorKey;

enum {
    GitHubConnectionError = 1,
    GitHubServerError,
    GitHubAuthenticationError,
    GitHubResourceNotFoundError,
    GitHubBadRequestError,
    GitHubUnprocessableEntityError,
    GitHubResponseParserError,
    GitHubAPIError,
    GitHubAuthenticationMethodError,
    GitHubLoginAttemptRateLimitExceedError,
    GitHubAPICallRateLimitExceedError
};

@interface NSError (GitHubAPI)

#pragma mark - Factory Methods

+ (id)gitHubConnectionErrorWithNSURLError:(NSError *)NSURLError userInfo:(NSDictionary *)userInfo;
+ (id)gitHubServerErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)gitHubAuthenticationErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)gitHubResourceNotFoundErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)gitHubBadRequestErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)gitHubUnprocessableEntityErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)gitHubResponseParserErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)gitHubAuthenticationMethodErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)gitHubErrorWithCode:(NSInteger)code userInfo:(NSDictionary *)userInfo;

#pragma mark - Checking for Concrete Errors

- (BOOL)isGitHubConnectionError;
- (BOOL)isGitHubServerError;
- (BOOL)isGitHubAuthenticationError;
- (BOOL)isGitHubResourceNotFoundError;
- (BOOL)isGitHubBadRequestError;
- (BOOL)isGitHubUnprocessableEntityError;
- (BOOL)isGitHubResponseParserError;
- (BOOL)isGitHubAPIError;
- (BOOL)isGitHubAuthenticationMethodError;

@end
