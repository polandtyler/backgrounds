//
//  BitbucketAPIRequestOperation.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 07.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BitbucketAuth;

@interface BitbucketAPIRequestOperation : FNHTTPAPIRequestOperation

@property (nonatomic, strong, readonly) BitbucketAuth *auth;
@property (nonatomic) dispatch_queue_t dispatchQueue;

#pragma mark - Initialization

- (id)initWithAuth:(BitbucketAuth *)auth method:(NSString *)method path:(NSString *)path params:(NSDictionary *)params headers:(NSDictionary *)headers;


@end
