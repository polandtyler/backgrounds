//
//  BitbucketAPIHelpers.h
//  BitbucketAPI
//
//  Created by Marc Beyerlin on 04.07.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BitbucketAPIHelpers : NSObject

+ (NSURL *)userWebURLForAccount:(NSString *)accountName;
+ (NSURL *)repositoryWebURLForAccount:(NSString *)accountName repository:(NSString *)repositoryName;

@end
