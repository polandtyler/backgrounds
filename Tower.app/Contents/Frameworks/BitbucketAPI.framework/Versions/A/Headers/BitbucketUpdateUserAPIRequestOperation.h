//
//  BitbucketUpdateUserAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 12.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <BitbucketAPI/BitbucketAPI.h>

@class BitbucketUser;

typedef void (^BitbucketUpdateUserErrorHandler)(NSError *error);
typedef void (^BitbucketUpdateUserCompletionHandler)(BitbucketUser *user);

@interface BitbucketUpdateUserAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, strong, readonly) BitbucketUser *user;
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;
@property (nonatomic, copy) BitbucketUpdateUserErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketUpdateUserCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth user:(BitbucketUser *)user;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth user:(BitbucketUser *)user;

#pragma mark - Synchronously Sending the Request

- (BitbucketUser *)send:(NSError * __autoreleasing *)error;

@end
