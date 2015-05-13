//
//  BitbucketFetchPublicKeysAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 11.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

typedef void (^BitbucketFetchPublicKeysErrorHandler)(NSError *error);
typedef void (^BitbucketFetchPublicKeysCompletionHandler)(NSArray *publicKeys);

@interface BitbucketFetchPublicKeysAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, strong, readonly) NSArray *publicKeys;
@property (nonatomic, copy) BitbucketFetchPublicKeysErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketFetchPublicKeysCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth;

#pragma mark - Synchronously Sending the Request

- (NSArray *)send:(NSError * __autoreleasing *)error;


@end
