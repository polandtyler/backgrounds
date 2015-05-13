//
//  GitHubUpdatePublicKeyAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 20.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

@class GitHubPublicKey;

typedef void (^GitHubUpdatePublicKeyErrorHandler)(NSError *error);
typedef void (^GitHubUpdatePublicKeyCompletionHandler)(GitHubPublicKey *publicKey);

@interface GitHubUpdatePublicKeyAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) GitHubPublicKey *publicKey;
@property (nonatomic, readonly, getter = isUpdated) BOOL updated;
@property (nonatomic, copy) GitHubUpdatePublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) GitHubUpdatePublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth publicKey:(GitHubPublicKey *)publicKey;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth publicKey:(GitHubPublicKey *)publicKey;

#pragma mark - Synchronously Sending the Request

- (GitHubPublicKey *)send:(NSError * __autoreleasing *)error;

@end
