//
//  GitHubAPIHelpers.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 08.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GitHubAPIHelpers : NSObject

+ (NSURL *)userWebURLForAccount:(NSString *)accountName;
+ (NSURL *)repositoryWebURLForAccount:(NSString *)accountName repository:(NSString *)repositoryName;

@end
