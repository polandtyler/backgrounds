//
//  BeanstalkFetchUserAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkUser;

typedef void (^BeanstalkFetchUserErrorHandler)(NSError *error);
typedef void (^BeanstalkFetchUserCompletionHandler)(BeanstalkUser *user);

@interface BeanstalkFetchUserAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, readonly) NSInteger userID;
@property (nonatomic, strong, readonly) BeanstalkUser *user;
@property (nonatomic, copy) BeanstalkFetchUserErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkFetchUserCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth;
+ (id)requestWithAuth:(BeanstalkAuth *)auth userID:(NSInteger)userID;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth userID:(NSInteger)userID;

#pragma mark - Synchronously Sending the Request

- (BeanstalkUser *)send:(NSError * __autoreleasing *)error;

@end
