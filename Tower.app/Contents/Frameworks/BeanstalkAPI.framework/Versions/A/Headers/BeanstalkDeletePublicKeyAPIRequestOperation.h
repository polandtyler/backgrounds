//
//  BeanstalkDeletePublicKeyAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

typedef void (^BeanstalkDeletePublicKeyErrorHandler)(NSError *error);
typedef void (^BeanstalkDeletePublicKeyCompletionHandler)(void);

@interface BeanstalkDeletePublicKeyAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, readonly) NSInteger publicKeyID;
@property (nonatomic, readonly, getter = isDeleted) BOOL deleted;
@property (nonatomic, copy) BeanstalkDeletePublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkDeletePublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth publicKeyID:(NSInteger)publicKeyID;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth publicKeyID:(NSInteger)publicKeyID;

#pragma mark - Sending the Request

- (BOOL)send:(NSError * __autoreleasing *)error;

@end
