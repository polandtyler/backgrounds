//
//  BeanstalkFetchPublicKeyAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkPublicKey;

typedef void (^BeanstalkFetchPublicKeyErrorHandler)(NSError *error);
typedef void (^BeanstalkFetchPublicKeyCompletionHandler)(BeanstalkPublicKey *publicKey);

@interface BeanstalkFetchPublicKeyAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, readonly) NSInteger publicKeyID;
@property (nonatomic, strong, readonly) BeanstalkPublicKey *publicKey;
@property (nonatomic, copy) BeanstalkFetchPublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkFetchPublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth publicKeyID:(NSInteger)publicKeyID;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth publicKeyID:(NSInteger)publicKeyID;

#pragma mark - Synchronously Sending the Request

- (BeanstalkPublicKey *)send:(NSError * __autoreleasing *)error;

@end
