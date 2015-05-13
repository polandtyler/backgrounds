//
//  BitbucketCreateUserAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 12.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

@class BitbucketUser;

typedef void (^BitbucketCreateUserErrorHandler)(NSError *error);
typedef void (^BitbucketCreateUserCompletionHandler)(BitbucketUser *user);

@interface BitbucketCreateUserAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, strong, readonly) BitbucketUser *user;
@property (nonatomic, readonly, getter = isCreated) BOOL created;
@property (nonatomic, copy) BitbucketCreateUserErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketCreateUserCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth user:(BitbucketUser *)user;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth user:(BitbucketUser *)user;
#pragma mark - Sending the Request

#pragma mark - Sending the Request

- (BitbucketUser *)send:(NSError * __autoreleasing *)error;

@end
