//
//  BeanstalkFetchRepositoryAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkRepository;

typedef void (^BeanstalkFetchRepositoryErrorHandler)(NSError *error);
typedef void (^BeanstalkFetchRepositoryCompletionHandler)(BeanstalkRepository *repository);

@interface BeanstalkFetchRepositoryAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, readonly) NSInteger repositoryID;
@property (nonatomic, strong, readonly) BeanstalkRepository *repository;
@property (nonatomic, copy) BeanstalkFetchRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkFetchRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth repositoryID:(NSInteger)repositoryID;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth repositoryID:(NSInteger)repositoryID;

#pragma mark - Synchronously Sending the Request

- (BeanstalkRepository *)send:(NSError * __autoreleasing *)error;

@end
