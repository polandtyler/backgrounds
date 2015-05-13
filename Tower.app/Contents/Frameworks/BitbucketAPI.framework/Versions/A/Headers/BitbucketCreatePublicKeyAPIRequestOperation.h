//
//  BitbucketCreatePublicKEyAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 07.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BitbucketAPIRequestOperation.h"

@class BitbucketPublicKey;

typedef void (^BitbucketCreatePublicKeyErrorHandler)(NSError *error);
typedef void (^BitbucketCreatePublicKeyCompletionHandler)(BitbucketPublicKey *publicKey);

@interface BitbucketCreatePublicKeyAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, strong, readonly) BitbucketPublicKey *publicKey;
@property (nonatomic, readonly, getter = isCreated) BOOL created;
@property (nonatomic, copy) BitbucketCreatePublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketCreatePublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth publicKey:(BitbucketPublicKey *)publicKey;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth publicKey:(BitbucketPublicKey *)publicKey;
#pragma mark - Sending the Request

#pragma mark - Sending the Request

- (BitbucketPublicKey *)send:(NSError * __autoreleasing *)error;

@end
