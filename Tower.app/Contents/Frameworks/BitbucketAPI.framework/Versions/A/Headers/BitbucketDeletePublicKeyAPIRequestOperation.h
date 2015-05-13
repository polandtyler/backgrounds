//
//  BitbucketDeletePublicKeyAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 07.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

typedef void (^BitbucketDeletePublicKeyErrorHandler)(NSError *error);
typedef void (^BitbucketDeletePublicKeyCompletionHandler)(void);

@interface BitbucketDeletePublicKeyAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, readonly) NSInteger publicKeyID;
@property (nonatomic, readonly, getter = isDeleted) BOOL deleted;
@property (nonatomic, copy) BitbucketDeletePublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketDeletePublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth publicKeyID:(NSInteger)publicKeyID;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth publicKeyID:(NSInteger)publicKeyID;

#pragma mark - Sending the Request

- (BOOL)send:(NSError * __autoreleasing *)error;

@end
