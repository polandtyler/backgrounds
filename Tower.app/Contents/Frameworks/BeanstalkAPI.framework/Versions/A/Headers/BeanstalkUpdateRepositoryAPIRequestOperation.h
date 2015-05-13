//
//  BeanstalkUpdateRepositoryAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkRepository;

typedef void (^BeanstalkUpdateRepositoryErrorHandler)(NSError *error);
typedef void (^BeanstalkUpdateRepositoryCompletionHandler)(BeanstalkRepository *repository);

@interface BeanstalkUpdateRepositoryAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, strong, readonly) BeanstalkRepository *repository;
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;
@property (nonatomic, copy) BeanstalkUpdateRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkUpdateRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth repository:(BeanstalkRepository *)repository;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth repository:(BeanstalkRepository *)repository;

#pragma mark - Synchronously Sending the Request

- (BeanstalkRepository *)send:(NSError * __autoreleasing *)error;

@end
