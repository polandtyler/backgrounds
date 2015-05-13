//
//  FNHTTPAPIRequestOperation.h
//  FNFoundation
//
//  Created by Alexander Rinass on 17.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNHTTPClient.h"

@class FNHTTPAuth;
@interface FNHTTPAPIRequestOperation : NSOperation <FNHTTPClientDelegate>
@property (nonatomic, strong) id<FNHTTPClient> client;
@property (nonatomic, strong) id <FNHTTPAuth> basicAuth;
@property (nonatomic, strong) NSURL *baseURL;
@property (nonatomic, strong) NSString *path;
@property (nonatomic, strong) NSString *method;
@property (nonatomic, strong) NSDictionary *params;
@property (nonatomic, strong) NSDictionary *headers;
@property (nonatomic, strong) NSData *body;
@property (nonatomic, strong, readonly) NSError *error;

- (id)initWithBaseURL:(NSURL *)baseURL path:(NSString *)path method:(NSString *)method params:(NSDictionary *)params headers:(NSDictionary *)headers body:(NSData *)body;

- (NSError *)handleConnectionError:(NSError *)error;
- (NSError *)handleAPIErrorResponse:(FNHTTPResponse *)response;
- (BOOL)parseResponse:(FNHTTPResponse *)response error:(NSError * __autoreleasing *)error;
- (void)didFinish;

@end
