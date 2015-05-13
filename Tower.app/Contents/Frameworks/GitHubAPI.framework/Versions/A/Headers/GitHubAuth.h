//
//  GitHubAuth.h
//  Tower
//
//  Created by Alexander Rinass on 12.04.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@interface GitHubAuth : NSObject <NSCopying>
@property (nonatomic, strong, readonly) NSString *username;
@property (nonatomic, strong, readonly) NSString *password;

#pragma mark - Factory Methods

+ (id)authWithUsername:(NSString *)username password:(NSString *)password;

#pragma mark - Initialization

- (id)initWithUsername:(NSString *)username password:(NSString *)password;

@end
