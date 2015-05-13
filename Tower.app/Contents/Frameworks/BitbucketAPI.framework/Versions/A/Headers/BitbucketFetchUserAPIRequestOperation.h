//
//  BitbucketFetchUserAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 12.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

@class BitbucketUser;

typedef void (^BitbucketFetchUserErrorHandler)(NSError *error);
typedef void (^BitbucketFetchUserCompletionHandler)(BitbucketUser *user);

@interface BitbucketFetchUserAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, readonly) NSString *username;
@property (nonatomic, strong, readonly) BitbucketUser *user;
@property (nonatomic, copy) BitbucketFetchUserErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketFetchUserCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth username:(NSString *)username;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth username:(NSString *)username;

#pragma mark - Synchronously Sending the Request

- (BitbucketUser *)send:(NSError * __autoreleasing *)error;


@end
