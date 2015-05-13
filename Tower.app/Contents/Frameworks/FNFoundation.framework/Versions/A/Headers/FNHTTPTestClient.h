//
//  FNHTTPTestClient.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 14.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNHTTPClient.h"

@interface FNHTTPTestClient : NSObject <FNHTTPClient>
@property (nonatomic, weak) id<FNHTTPClientDelegate> delegate;
@property (nonatomic, strong) id<FNHTTPAuth> auth;
@property (nonatomic, strong) FNHTTPRequest *request;
@property (nonatomic, strong) FNHTTPResponse *response;
@property (nonatomic, readonly, getter = isSending) BOOL sending;
@property (nonatomic, strong) NSError *error;

#pragma mark - Factory Methods

+ (id)client;
+ (id)clientWithResponse:(FNHTTPResponse *)response;
+ (id)clientWithRequest:(FNHTTPRequest *)request response:(FNHTTPResponse *)response;

#pragma mark - Initialization

- (id)initWithRequest:(FNHTTPRequest *)request response:(FNHTTPResponse *)response auth:(id<FNHTTPAuth>)auth error:(NSError *)error;

#pragma mark - Sending Requests Asynchronously

- (void)send;
- (void)waitUntilFinished;
- (void)cancel;

#pragma mark - Sending Requests Synchronously

- (FNHTTPResponse *)send:(NSError * __autoreleasing *)error;

@end
