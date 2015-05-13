//
//  FNHTTPRequest.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 31.05.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNHTTPRequest : NSObject
@property (nonatomic, strong) NSURL *URL;
@property (nonatomic, strong) NSString *method;
@property (nonatomic, strong) NSDictionary *params;
@property (nonatomic, strong) NSData *data;
@property (nonatomic, copy) NSDictionary *headers;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, readonly) BOOL isGETRequest;
@property (nonatomic, readonly) BOOL isPOSTRequest;
@property (nonatomic, readonly) BOOL isPUTRequest;
@property (nonatomic, readonly) BOOL isDELETERequest;

#pragma mark - Factory Methods 

+ (id)requestWithURL:(NSURL *)URL;
+ (id)requestWithURL:(NSURL *)URL method:(NSString *)method params:(NSDictionary *)params;
+ (id)requestWithURL:(NSURL *)URL method:(NSString *)method params:(NSDictionary *)params data:(NSData *)data headers:(NSDictionary *)headers;

#pragma mark - Initialization

- (id)initWithURL:(NSURL *)URL method:(NSString *)method params:(NSDictionary *)params data:(NSData *)data headers:(NSDictionary *)headers;

@end
