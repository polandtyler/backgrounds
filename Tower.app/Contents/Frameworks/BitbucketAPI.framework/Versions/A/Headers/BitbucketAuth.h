//
//  BitbucketAuth.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 07.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BitbucketAuth : NSObject
@property (nonatomic, strong, readonly) NSString *username;
@property (nonatomic, strong, readonly) NSString *password;


/** @name Creating BitbucketAuth */

+ (id)authWithUsername:(NSString *)username password:(NSString *)password;
- (id)initWithUsername:(NSString *)username password:(NSString *)password;

@end
