//
//  GitHubFetchPublicKeysAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 20.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

typedef void (^GitHubFetchPublicKeysErrorHandler)(NSError *error);
typedef void (^GitHubFetchPublicKeysCompletionHandler)(NSArray *publicKeys);

@interface GitHubFetchPublicKeysAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) NSArray *publicKeys;
@property (nonatomic, copy) GitHubFetchPublicKeysErrorHandler errorHandler;
@property (nonatomic, copy) GitHubFetchPublicKeysCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth;

#pragma mark - Synchronously Sending the Request

- (NSArray *)send:(NSError * __autoreleasing *)error;

@end
