//
//  BeanstalkDeleteUserAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

typedef void (^BeanstalkDeleteUserErrorHandler)(NSError *error);
typedef void (^BeanstalkDeleteUserCompletionHandler)(void);

@interface BeanstalkDeleteUserAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, readonly) NSInteger userID;
@property (nonatomic, readonly, getter = isDeleted) BOOL deleted;
@property (nonatomic, copy) BeanstalkDeleteUserErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkDeleteUserCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth userID:(NSInteger)userID;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth userID:(NSInteger)userID;

#pragma mark - Sending the Request

- (BOOL)send:(NSError * __autoreleasing *)error;

@end
