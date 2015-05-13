//
//  BitbucketFetchRepositoryAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 11.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

@class BitbucketRepository;

typedef void (^BitbucketFetchRepositoryErrorHandler)(NSError *error);
typedef void (^BitbucketFetchRepositoryCompletionHandler)(BitbucketRepository *repository);

@interface BitbucketFetchRepositoryAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, readonly, copy) NSString *slug;
@property (nonatomic, readonly, copy) NSString *account;
@property (nonatomic, strong, readonly) BitbucketRepository *repository;
@property (nonatomic, copy) BitbucketFetchRepositoryErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketFetchRepositoryCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth account:(NSString *)account slug:(NSString *)slug;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth account:(NSString *)account slug:(NSString *)slug;

#pragma mark - Synchronously Sending the Request

- (BitbucketRepository *)send:(NSError * __autoreleasing *)error;


@end
