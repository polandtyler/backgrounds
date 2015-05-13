//
//  GitHubFetchPublicKeyAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 20.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

@class GitHubPublicKey;

typedef void (^GitHubFetchPublicKeyErrorHandler)(NSError *error);
typedef void (^GitHubFetchPublicKeyCompletionHandler)(GitHubPublicKey *publicKey);

@interface GitHubFetchPublicKeyAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, readonly) NSInteger publicKeyID;
@property (nonatomic, strong, readonly) GitHubPublicKey *publicKey;
@property (nonatomic, copy) GitHubFetchPublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) GitHubFetchPublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth publicKeyID:(NSInteger)publicKeyID;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth publicKeyID:(NSInteger)publicKeyID;

#pragma mark - Synchronously Sending the Request

- (GitHubPublicKey *)send:(NSError * __autoreleasing *)error;

@end
