//
//  BeanstalkCreateRepositoryAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkRepository;

typedef void (^BeanstalkCreateRepositoryErrorHandler)(NSError *error);
typedef void (^BeanstalkCreateRepositoryCompletionHandler)(BeanstalkRepository *repository);

@interface BeanstalkCreateRepositoryAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, strong, readonly) BeanstalkRepository *repository;
@property (nonatomic, readonly, getter = isCreated) BOOL created;
@property (nonatomic, copy) BeanstalkCreateRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkCreateRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth repository:(BeanstalkRepository *)repository;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth repository:(BeanstalkRepository *)repository;
#pragma mark - Sending the Request

#pragma mark - Sending the Request

- (BeanstalkRepository *)send:(NSError * __autoreleasing *)error;

@end
