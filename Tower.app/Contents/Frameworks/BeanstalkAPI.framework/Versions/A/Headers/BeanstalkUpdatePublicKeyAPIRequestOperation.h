//
//  BeanstalkUpdatePublicKeyAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkPublicKey;

typedef void (^BeanstalkUpdatePublicKeyErrorHandler)(NSError *error);
typedef void (^BeanstalkUpdatePublicKeyCompletionHandler)(BeanstalkPublicKey *publicKey);

@interface BeanstalkUpdatePublicKeyAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, strong, readonly) BeanstalkPublicKey *publicKey;
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;
@property (nonatomic, copy) BeanstalkUpdatePublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkUpdatePublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth publicKey:(BeanstalkPublicKey *)publicKey;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth publicKey:(BeanstalkPublicKey *)publicKey;

#pragma mark - Synchronously Sending the Request

- (BeanstalkPublicKey *)send:(NSError * __autoreleasing *)error;

@end
