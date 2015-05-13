//
//  BeanstalkUpdateUserAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkUser;

typedef void (^BeanstalkUpdateUserErrorHandler)(NSError *error);
typedef void (^BeanstalkUpdateUserCompletionHandler)(BeanstalkUser *user);

@interface BeanstalkUpdateUserAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, strong, readonly) BeanstalkUser *user;
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;
@property (nonatomic, copy) BeanstalkUpdateUserErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkUpdateUserCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth user:(BeanstalkUser *)user;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth user:(BeanstalkUser *)user;

#pragma mark - Synchronously Sending the Request

- (BeanstalkUser *)send:(NSError * __autoreleasing *)error;

@end
