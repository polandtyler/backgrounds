//
//  BeanstalkJSONAPIRequestOperation.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 18.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@class BeanstalkAuth;
@interface BeanstalkAPIRequestOperation : FNHTTPJSONAPIRequestOperation
@property (nonatomic, strong, readonly) BeanstalkAuth *auth;
@property (nonatomic) dispatch_queue_t dispatchQueue;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth method:(NSString *)method path:(NSString *)path params:(NSDictionary *)params headers:(NSDictionary *)headers;

@end
