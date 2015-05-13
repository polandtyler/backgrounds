//
//  GitHubAPIRequestOperation.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 19.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <FNFoundation/FNFoundation.h>

@class GitHubAuth;
@interface GitHubAPIRequestOperation : FNHTTPJSONAPIRequestOperation
@property (nonatomic, strong, readonly) GitHubAuth *auth;
@property (nonatomic) dispatch_queue_t dispatchQueue;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth method:(NSString *)method path:(NSString *)path params:(NSDictionary *)params headers:(NSDictionary *)headers;

@end
