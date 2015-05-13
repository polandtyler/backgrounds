//
//  GitHubDeletePublicKeyAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 20.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

typedef void (^GitHubDeletePublicKeyErrorHandler)(NSError *error);
typedef void (^GitHubDeletePublicKeyCompletionHandler)(void);

@interface GitHubDeletePublicKeyAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, readonly) NSInteger publicKeyID;
@property (nonatomic, readonly, getter = isDeleted) BOOL deleted;
@property (nonatomic, copy) GitHubDeletePublicKeyErrorHandler errorHandler;
@property (nonatomic, copy) GitHubDeletePublicKeyCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth publicKeyID:(NSInteger)publicKeyID;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth publicKeyID:(NSInteger)publicKeyID;

#pragma mark - Synchronously Sending the Request

- (BOOL)send:(NSError * __autoreleasing *)error;

@end
