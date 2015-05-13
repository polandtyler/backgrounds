//
//  BitbucketCreateRepositoryAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 11.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

@class BitbucketRepository;

typedef void (^BitbucketCreateRepositoryErrorHandler)(NSError *error);
typedef void (^BitbucketCreateRepositoryCompletionHandler)(BitbucketRepository *repository);

@interface BitbucketCreateRepositoryAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, strong, readonly) BitbucketRepository *repository;
@property (nonatomic, readonly, getter = isCreated) BOOL created;
@property (nonatomic, copy) BitbucketCreateRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketCreateRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth repository:(BitbucketRepository *)repository;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth repository:(BitbucketRepository *)repository;
#pragma mark - Sending the Request

#pragma mark - Sending the Request

- (BitbucketRepository *)send:(NSError * __autoreleasing *)error;


@end
