//
//  BeanstalkFetchPlansAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinass on 28.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

typedef void (^BeanstalkFetchPlansErrorHandler)(NSError *error);
typedef void (^BeanstalkFetchPlansCompletionHandler)(NSArray *plans);

@interface BeanstalkFetchPlansAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, strong, readonly) NSArray *plans;
@property (nonatomic, copy) BeanstalkFetchPlansErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkFetchPlansCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth;

#pragma mark - Synchronously Sending the Request

- (NSArray *)send:(NSError * __autoreleasing *)error;

@end
