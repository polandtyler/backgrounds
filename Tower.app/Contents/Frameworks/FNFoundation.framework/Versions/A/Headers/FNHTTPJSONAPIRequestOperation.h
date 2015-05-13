//
//  FNHTTPJSONAPIRequestOperation.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 18.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNHTTPAPIRequestOperation.h"

@interface FNHTTPJSONAPIRequestOperation : FNHTTPAPIRequestOperation

- (id)initWithBaseURL:(NSURL *)baseURL path:(NSString *)path method:(NSString *)method params:(NSDictionary *)params headers:(NSDictionary *)headers;
@end
