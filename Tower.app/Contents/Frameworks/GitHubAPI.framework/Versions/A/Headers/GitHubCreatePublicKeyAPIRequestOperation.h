//
//  GitHubCreatePublicKeyAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 20.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

@class GitHubPublicKey;

typedef void (^GitHubCreatePublicKeyErrorHandler)(NSError *error);
typedef void (^GitHubCreatePublicKeyCompletionHandler)(GitHubPublicKey *publicKey);

@interface GitHubCreatePublicKeyAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) GitHubPublicKey *publicKey;
@property (nonatomic, readonly, getter = isCreated) BOOL created;
@property (nonatomic, copy) GitHubCreatePublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) GitHubCreatePublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth publicKey:(GitHubPublicKey *)publicKey;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth publicKey:(GitHubPublicKey *)publicKey;

#pragma mark - Synchronously Sending the Request

- (GitHubPublicKey *)send:(NSError * __autoreleasing *)error;

@end
