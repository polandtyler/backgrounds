//
//  BitbucketDeleteRepositoryAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 11.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

typedef void (^BitbucketDeleteRepositoryErrorHandler)(NSError *error);
typedef void (^BitbucketDeleteRepositoryCompletionHandler)(void);

@interface BitbucketDeleteRepositoryAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, strong, readonly) BitbucketRepository *repository;
@property (nonatomic, readonly, getter = isDeleted) BOOL deleted;
@property (nonatomic, copy) BitbucketDeleteRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketDeleteRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth repository:(BitbucketRepository *)repository;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth repository:(BitbucketRepository *)repository;

#pragma mark - Synchronously Sending the Request

- (BOOL)send:(NSError * __autoreleasing *)error;

@end
