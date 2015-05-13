//
//  BitbucketUpdatePublicKeyAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 07.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

@class BitbucketPublicKey;
typedef void (^BitbucketUpdatePublicKeyErrorHandler)(NSError *error);
typedef void (^BitbucketUpdatePublicKeyCompletionHandler)(BitbucketPublicKey *publicKey);

@interface BitbucketUpdatePublicKeyAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, strong, readonly) BitbucketPublicKey *publicKey;
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;
@property (nonatomic, copy) BitbucketUpdatePublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketUpdatePublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth publicKey:(BitbucketPublicKey *)publicKey;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth publicKey:(BitbucketPublicKey *)publicKey;

#pragma mark - Synchronously Sending the Request

- (BitbucketPublicKey *)send:(NSError * __autoreleasing *)error;


@end
