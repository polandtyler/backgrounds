//
//  NSError+BeanstalkAPI.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const BeanstalkAPIErrorDomain;

extern NSString *const BeanstalkURLErrorKey;
extern NSString *const BeanstalkStatusCodeErrorKey;
extern NSString *const BeanstalkResponseBodyErrorKey;
extern NSString *const BeanstalkErrorsErrorKey;

typedef NS_ENUM(NSInteger, BeanstalkError) {
    BeanstalkConnectionError = 1,
    BeanstalkServerError,
    BeanstalkAccountNotFoundError,
    BeanstalkAuthenticationError,
    BeanstalkResourceNotFoundError,
    BeanstalkResponseParserError,
    BeanstalkAPIError
};

@interface NSError (BeanstalkAPI)

#pragma mark - Factory Methods

+ (id)beanstalkConnectionErrorWithNSURLError:(NSError *)NSURLError userInfo:(NSDictionary *)userInfo;
+ (id)beanstalkServerErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)beanstalkAccountNotFoundErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)beanstalkAuthenticationErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)beanstalkResourceNotFoundErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)beanstalkResponseParserErrorWithUserInfo:(NSDictionary *)userInfo;
+ (id)beanstalkAPIErrorWithUserInfo:(NSDictionary *)userInfo;

+ (id)beanstalkErrorWithCode:(NSInteger)code userInfo:(NSDictionary *)userInfo;

#pragma mark - Checking for Concrete Errors

- (BOOL)isBeanstalkConnectionError;
- (BOOL)isBeanstalkServerError;
- (BOOL)isBeanstalkAuthenticationError;
- (BOOL)isBeanstalkResourceNotFoundError;
- (BOOL)isBeanstalkResponseParserError;
- (BOOL)isBeanstalkAPIError;

@end
