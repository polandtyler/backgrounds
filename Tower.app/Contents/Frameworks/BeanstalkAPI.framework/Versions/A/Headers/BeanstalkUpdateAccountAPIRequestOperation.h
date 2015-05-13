//
//  BeanstalkUpdateAccountAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinass on 28.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkAccount;

typedef void (^BeanstalkUpdateAccountErrorHandler)(NSError *error);
typedef void (^BeanstalkUpdateAccountCompletionHandler)(BeanstalkAccount *account);

@interface BeanstalkUpdateAccountAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, strong, readonly) BeanstalkAccount *account;
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;
@property (nonatomic, copy) BeanstalkUpdateAccountErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkUpdateAccountCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth account:(BeanstalkAccount *)account;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth account:(BeanstalkAccount *)account;

#pragma mark - Synchronously Sending the Request

- (BeanstalkAccount *)send:(NSError * __autoreleasing *)error;

@end
