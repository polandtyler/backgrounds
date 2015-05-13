//
//  FNHTTPClient.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 13.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNHTTPRequest;
@class FNHTTPResponse;
@protocol FNHTTPClientDelegate;
@protocol FNHTTPClient <NSURLConnectionDelegate, NSObject>
@property (nonatomic, weak) id<FNHTTPClientDelegate> delegate;
@property (nonatomic, strong) FNHTTPRequest *request;
@property (nonatomic, strong, readonly) FNHTTPResponse *response;
@property (nonatomic, readonly, getter = isSending) BOOL sending;

- (void)send;
- (void)waitUntilFinished;
- (void)cancel;

- (FNHTTPResponse *)send:(NSError * __autoreleasing *)error;

@end

@class FNHTTPClient;
@protocol FNHTTPClientDelegate <NSObject>
@optional

- (void)HTTPClient:(id<FNHTTPClient>)client didReceiveResponse:(FNHTTPResponse *)response;
- (void)HTTPClient:(id<FNHTTPClient>)client didFailWithError:(NSError *)error;

@end
#pragma mark -

@protocol FNHTTPAuth;
@class FNHTTPRequest;
@interface FNHTTPClient : NSObject <FNHTTPClient>
@property (nonatomic, weak) id<FNHTTPClientDelegate> delegate;
@property (nonatomic, strong) id<FNHTTPAuth> auth;
@property (nonatomic, strong) FNHTTPRequest *request;
@property (nonatomic, strong, readonly) FNHTTPResponse *response;
@property (nonatomic, readonly, getter = isSending) BOOL sending;
@property (nonatomic, strong, readonly) NSError *error;

#pragma mark - Factory Methods

+ (id)client;
+ (id)clientWithRequest:(FNHTTPRequest *)request;
+ (id)clientWithRequest:(FNHTTPRequest *)request auth:(id<FNHTTPAuth>)auth;

#pragma mark - Initialization

- (id)initWithRequest:(FNHTTPRequest *)request auth:(id<FNHTTPAuth>)auth;

#pragma mark - Sending Requests Asynchronously

- (void)send;
- (void)waitUntilFinished;
- (void)cancel;

#pragma mark - Sending Requests Synchronously

- (FNHTTPResponse *)send:(NSError * __autoreleasing *)error;

@end
