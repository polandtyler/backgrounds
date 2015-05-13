//
//  BitbucketFetchUserEmailAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Marc Beyerlin on 13.05.14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BitbucketAPIRequestOperation.h"

@class BitbucketUserEmail;

typedef void (^BitbucketFetchUserEmailErrorHandler)(NSError *error);
typedef void (^BitbucketFetchUserEmailCompletionHandler)(BitbucketUserEmail *userEmail);


@interface BitbucketFetchUserEmailAPIRequestOperation : BitbucketAPIRequestOperation

@property (nonatomic, readonly) NSString *username;
@property (nonatomic, strong, readonly) BitbucketUserEmail *userEmail;
@property (nonatomic, copy) BitbucketFetchUserEmailErrorHandler errorHandler;
@property (nonatomic, copy) BitbucketFetchUserEmailCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(BitbucketAuth *)auth username:(NSString *)username;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth username:(NSString *)username;

#pragma mark - Synchronously Sending the Request

- (BitbucketUserEmail *)send:(NSError * __autoreleasing *)error;

@end
