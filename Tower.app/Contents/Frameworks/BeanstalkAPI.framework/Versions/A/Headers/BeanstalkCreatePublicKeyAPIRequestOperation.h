//
//  BeanstalkCreatePublicKeyAPIRequestOperation
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "BeanstalkAPIRequestOperation.h"

@class BeanstalkPublicKey;

typedef void (^BeanstalkCreatePublicKeyErrorHandler)(NSError *error);
typedef void (^BeanstalkCreatePublicKeyCompletionHandler)(BeanstalkPublicKey *publicKey);

@interface BeanstalkCreatePublicKeyAPIRequestOperation : BeanstalkAPIRequestOperation
@property (nonatomic, strong, readonly) BeanstalkPublicKey *publicKey;
@property (nonatomic, readonly, getter = isCreated) BOOL created;
@property (nonatomic, copy) BeanstalkCreatePublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) BeanstalkCreatePublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BeanstalkAuth *)auth publicKey:(BeanstalkPublicKey *)publicKey;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth publicKey:(BeanstalkPublicKey *)publicKey;
#pragma mark - Sending the Request

#pragma mark - Sending the Request

- (BeanstalkPublicKey *)send:(NSError * __autoreleasing *)error;

@end
