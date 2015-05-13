//
//  BitbucketUpdateRepositoryAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 11.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

@class BitbucketRepository;

typedef void (^BitbucketUpdateRepositoryErrorHandler)(NSError *error);
typedef void (^BitbucketUpdateRepositoryCompletionHandler)(BitbucketRepository *repository);

@interface BitbucketUpdateRepositoryAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, strong, readonly) BitbucketRepository *repository;
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;
@property (nonatomic, copy) BitbucketUpdateRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketUpdateRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth repository:(BitbucketRepository *)repository;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth repository:(BitbucketRepository *)repository;

#pragma mark - Synchronously Sending the Request

- (BitbucketRepository *)send:(NSError * __autoreleasing *)error;


@end
