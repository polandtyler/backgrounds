//
//  GitHubSearchUsersAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 19.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "GitHubAPIRequestOperation.h"

typedef void (^GitHubFetchUsersErrorHandler)(NSError *error);
typedef void (^GitHubFetchUsersCompletionHandler)(NSArray *users);

@interface GitHubFetchUsersAPIRequestOperation : GitHubAPIRequestOperation
@property (nonatomic, strong, readonly) NSString *keyword;
@property (nonatomic, strong, readonly) NSArray *users;
@property (nonatomic, copy) GitHubFetchUsersErrorHandler errorHandler;
@property (nonatomic, copy) GitHubFetchUsersCompletionHandler completionHandler;

#pragma mark - Factory Methods

+ (id)requestWithAuth:(GitHubAuth *)auth keyword:(NSString *)keyword;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth keyword:(NSString *)keyword;

#pragma mark - Synchronously Sending the Request

- (NSArray *)send:(NSError * __autoreleasing *)error;

@end
