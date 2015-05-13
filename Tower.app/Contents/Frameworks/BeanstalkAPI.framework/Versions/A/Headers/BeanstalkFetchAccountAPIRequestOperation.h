//
//  BeanstalkFetchAccountAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinass on 28.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkAccount;

typedef void (^BeanstalkFetchAccountErrorHandler)(NSError *error);
typedef void (^BeanstalkFetchAccountCompletionHandler)(BeanstalkAccount *account);

@interface BeanstalkFetchAccountAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, strong, readonly) BeanstalkAccount *account;
@property (nonatomic, copy) BeanstalkFetchAccountErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkFetchAccountCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth;

#pragma mark - Synchronously Sending the Request

- (BeanstalkAccount *)send:(NSError * __autoreleasing *)error;

@end
