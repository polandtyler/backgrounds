//
//  BitbucketFetchRepositoryAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 11.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

typedef void (^BitbucketFetchRepositoriesErrorHandler)(NSError *error);
typedef void (^BitbucketFetchRepositoriesCompletionHandler)(NSArray *repositories);

@interface BitbucketFetchRepositoriesOfUserAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, strong, readonly) NSArray *repositories;
@property (nonatomic, readonly, copy) NSString *account;
@property (nonatomic, copy) BitbucketFetchRepositoriesErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketFetchRepositoriesCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth account:(NSString *)account;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth account:(NSString *)account;

#pragma mark - Synchronously Sending the Request

- (NSArray *)send:(NSError * __autoreleasing *)error;

@end
