//
//  NSError+BitbucketAPI.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 07.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const BitbucketAPIErrorDomain;

extern NSString *const BitbucketURLErrorKey;
extern NSString *const BitbucketStatusCodeErrorKey;
extern NSString *const BitbucketResponseBodyErrorKey;
extern NSString *const BitbucketErrorsErrorKey;

typedef NS_ENUM(NSInteger, BitBucketError) {
    BitbucketConnectionError = 1,
    BitbucketServerError,
    BitbucketAuthenticationError,
    BitbucketResourceNotFoundError,
    BitbucketResponseParserError,
    BitbucketAPIError
};

@interface NSError (BitbucketAPI)

#pragma mark - Factory Methods

+ (id)bitbucketConnectionErrorWithNSURLError:(NSError *)NSURLError userInfo:(NSDictionary *)userInfo;
+ (id)bitbucketServerErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)bitbucketAuthenticationErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)bitbucketResourceNotFoundErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)bitbucketResponseParserErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)bitbucketAPIErrorWithUserInfo:(NSDictionary *)userInfo;

+ (id)bitbucketErrorWithCode:(NSInteger)code userInfo:(NSDictionary *)userInfo;

#pragma mark - Checking for Concrete Errors

- (BOOL)isBitbucketConnectionError;
- (BOOL)isBitbucketServerError;
- (BOOL)isBitbucketAuthenticationError;
- (BOOL)isBitbucketResourceNotFoundError;
- (BOOL)isBitbucketResponseParserError;
- (BOOL)isBitbucketAPIError;


@end
