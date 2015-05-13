//
//  FNHTTPResponse.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 31.05.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNHTTPResponse : NSObject
@property (nonatomic, readonly) NSInteger status;
@property (nonatomic, strong, readonly) NSDictionary *headers;
@property (nonatomic, strong, readonly) NSData *body;
@property (nonatomic, strong, readonly) NSString *content;
@property (nonatomic, readonly) BOOL isErrorResponse;

#pragma mark - Factory Methods

+ (id)responseFromURLResponse:(NSHTTPURLResponse *)URLResponse withBody:(NSData *)body;
+ (id)responseWithStatus:(NSInteger)status headers:(NSDictionary *)headers body:(NSData *)body;

#pragma mark - Initialization

- (id)initWithStatus:(NSInteger)status headers:(NSDictionary *)headers body:(NSData *)body;

@end
